#include "../../inc/log_util/async_logging.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "../../inc/log_util/logfile.h"

namespace ambitiontc_webserver {
namespace log_utility {

AsyncLogging::AsyncLogging(std::string log_file_name, int flush_interval)
    : flush_interval_(flush_interval),
      running_(false),
      basename_(log_file_name),
      thread_(std::bind(&AsyncLogging::ThreadFunc, this), "Logging"),
      mutex_(),
      cond_(mutex_),
      current_buffer_(new Buffer),
      next_buffer_(new Buffer),
      buffers_(),
      latch_(1) {
  assert(log_file_name.size() > 1);
  current_buffer_->ResetZero();
  next_buffer_->ResetZero();
  buffers_.reserve(16);
}

void AsyncLogging::Append(const char* logline, int len){
  MutexLockGuard lock(mutex_);
  if(current_buffer_->Avail() > len)
    current_buffer_->Append(logline, len);
  else{
    buffers_.push_back(current_buffer_);
    //释放当前内存
    current_buffer_.reset();
    if(next_buffer_)
      current_buffer_ = std::move(next_buffer_);
    else
      current_buffer_.reset(new Buffer);
    current_buffer_->Append(logline, len);
    cond_.Notify();
  }
}

void AsyncLogging::ThreadFunc(){
  assert(running_ == true);
  latch_.LatchThread();
  LogFile output(basename_);
  BufferPtr new_buffer1(new Buffer);
  BufferPtr new_buffer2(new Buffer);
  new_buffer1->ResetZero();
  new_buffer2->ResetZero();
  BufferVector buffers_to_write;
  buffers_to_write.reserve(16);
  while(running_){
    assert(new_buffer1 && new_buffer1->GetLength() == 0);
    assert(new_buffer2 && new_buffer2->GetLength() == 0);
    assert(buffers_to_write.empty());
    {
      MutexLockGuard lock(mutex_);
      if(buffers_.empty()){   //unusual usage!
        cond_.WaitForSeconds(flush_interval_);
      }
      buffers_.push_back(current_buffer_);
      current_buffer_.reset();
      current_buffer_ = std::move(new_buffer1);
      buffers_to_write.swap(buffers_);
      if(!next_buffer_){
        next_buffer_ = std::move(new_buffer2);
      }
    }
    assert(!buffers_to_write.empty());
    if(buffers_to_write.size() > 25){
      buffers_to_write.erase(buffers_to_write.begin() + 2, buffers_to_write.end());
    }
    for(size_t i = 0; i < buffers_to_write.size(); i++){
      output.Append(buffers_to_write[i]->GetData(), buffers_to_write[i]->GetLength());
    }
    if(buffers_to_write.size() > 2){
      buffers_to_write.resize(2);
    }

    if(!new_buffer1){
      assert(!buffers_to_write.empty());
      new_buffer1 = buffers_to_write.back();
      buffers_to_write.pop_back();
      new_buffer1->Reset();
    }
    if(!new_buffer2){
      assert(!buffers_to_write.empty());
      new_buffer2 = buffers_to_write.back();
      buffers_to_write.pop_back();
      new_buffer2->Reset();
    }
    buffers_to_write.clear();
    output.Flush();
  }
  output.Flush();
}

}  // namespace log_utility
}  // namespace ambitiontc_webserver