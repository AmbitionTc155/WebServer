/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    async_logging.h
 *	@brief      用于异步同步缓冲区的内容到文件中
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___ASYNC_LOGGING_H
#define AMBITIONTC___WEBSERVER___ASYNC_LOGGING_H

#include <functional>
#include <string>
#include <vector>

#include "../count_down_latch.h"
#include "../mutex_lock.h"
#include "../noncopyable.h"
#include "../thread.h"
#include "log_stream.h"

namespace ambitiontc_webserver {
namespace log_utility {

class AsyncLogging : noncopyable {
 public:
  AsyncLogging(const std::string basename, int flush_interval = 2);
  ~AsyncLogging() {
    if (running_) Stop();
  }
  void Append(const char* logline, int len);
  void Start() {
    running_ = true;
    thread_.Start();
    latch_.Wait();
  }
  void Stop() {
    running_ = false;
    cond_.Notify();
    thread_.Join();
  }

 private:
  void ThreadFunc();
  typedef FixedBuffer<kLargeBuffer> Buffer;
  typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
  typedef std::shared_ptr<Buffer> BufferPtr;
  const int flush_interval_;
  bool running_;
  std::string basename_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_;
  BufferPtr current_buffer_;
  BufferPtr next_buffer_;
  BufferVector buffers_;
  CountDownLatch latch_;
};

}  // namespace log_utility
}  // namespace ambitiontc_webserver

#endif