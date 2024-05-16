#include "../../inc/log_util/logfile.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

namespace ambitiontc_webserver {
namespace log_utility {

AppendFile::AppendFile(const std::string filename) : fp_(fopen(filename.c_str(), "ae")) {
  // 用户提供缓冲区
  setbuffer(fp_, buffer_, sizeof buffer_);
}

AppendFile::~AppendFile() { fclose(fp_); }

void AppendFile::Append(const char* logline, const size_t len){
  size_t remain = len;
  size_t n = 0;
  while(remain > 0){
    size_t x = this -> Write(logline + n, remain);
    if(x == 0){
      int err = ferror(fp_);
      if(err) fprintf(stderr, "AppendFile::Append() failed! \n");
      break;
    }
    n += x;
    remain = len - n;
  }
}

void AppendFile::Flush() { fflush(fp_); }

size_t AppendFile::Write(const char* logline, size_t len) {
  return fwrite_unlocked(logline, 1, len, fp_);
}

LogFile::LogFile(const std::string basename, int flush_every_n)
    : basename_(basename),
      flush_every_n_(flush_every_n),
      count_(0),
      mutex_(new MutexLock) {
  //reset是智能指针unique_ptr的成员函数，用于重新初始化智能指针的地址
  file_.reset(new AppendFile(basename));
}

LogFile::~LogFile(){}

void LogFile::Append(const char* logline, int len){
  MutexLockGuard lock(*mutex_);
  AppendUnlocked(logline, len);
}

void LogFile::Flush(){
  MutexLockGuard lock(*mutex_);
  file_->Flush();
}

void LogFile::AppendUnlocked(const char* logline, int len){
  file_->Append(logline, len);
  ++count_;
  if(count_>= flush_every_n_){
    count_ = 0;
    file_->Flush();
  }
}

}  // namespace log_utility
}  // namespace ambitiontc_webserver