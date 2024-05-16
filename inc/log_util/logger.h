/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    logger.h
 *	@brief      log的封装函数，LOG的入口头文件
 *  @author     Tang Chao
 *  @link
 */
#ifndef AMBITIONTC___WEBSERVER___LOGGER_H
#define AMBITIONTC___WEBSERVER___LOGGER_H
#include <iostream>
#include <string>

#include "log_stream.h"
namespace ambitiontc_webserver {
namespace log_utility {

//声明一下
class AsyncLogging;

class Logger {
 public:
  Logger(const char* file_name, int line);
  ~Logger();
  LogStream& stream() { return impl_.stream_; }
  static void SetLogFileName(std::string file_name) {
    logfile_name_ = file_name;
  }
  static std::string GetLogFileName() { return logfile_name_; }
  
 private:
  class Impl {
   public:
    Impl(const char* file_name, int line);
    void FormatTime();
    LogStream stream_;
    int line_;
    std::string basename_;
  };
  Impl impl_;
  static std::string logfile_name_;
};

#define LOG Logger(__FILE__, __LINE__).stream()

}  // namespace log_utility
}  // namespace ambitiontc_webserver

#endif