#include "../../inc/log_util/logger.h"
#include "../../inc/log_util/async_logging.h"


#include <assert.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#include <iostream>

namespace ambitiontc_webserver {
namespace log_utility {

static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static AsyncLogging* async_logger_;
std::string Logger::logfile_name_ = "./WebServer.log";

void OnceInit(){
  //async_logger_ = new AsyncLogging(Logger::GetLogFileName());
  async_logger_ = new AsyncLogging("./WebServer.log");
  async_logger_->Start();
}

void Output(const char* msg, int len){
  pthread_once(&once_control_, OnceInit);
  async_logger_->Append(msg, len);
}

Logger::Impl::Impl(const char* file_name, int line)
    : stream_(), line_(line), basename_(file_name) {
  FormatTime();
}

void Logger::Impl::FormatTime() {
  struct timeval tv;
  time_t time;
  char str_t[26] = {0};
  gettimeofday(&tv, NULL);
  time = tv.tv_sec;
  struct tm* p_time = localtime(&time);
  strftime(str_t, 26, "%Y-%m-%d %H:%M:%S\n", p_time);
  stream_ << str_t;
}

Logger::Logger(const char* file_name, int line) : impl_(file_name, line) {}

Logger::~Logger(){
  impl_.stream_ << "--" << impl_.basename_ << ":" << impl_.line_ << '\n';
  const LogStream::Buffer& buf(stream().GetBuffer());
  Output(buf.GetData(), buf.GetLength());
} 

}  // namespace log_utility
}  // namespace ambitiontc_webserver