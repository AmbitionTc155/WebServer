/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    logfile.h
 *	@brief      log文件管理类
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___LOGFILE_H
#define AMBITIONTC___WEBSERVER___LOGFILE_H

#include <memory>
#include <string>

#include "../mutex_lock.h"
#include "../noncopyable.h"

namespace ambitiontc_webserver {
namespace log_utility {

class AppendFile : noncopyable {
 public:
  explicit AppendFile(std::string filename);
  ~AppendFile();
  // Append会向文件写
  void Append(const char *logline, const size_t len);
  void Flush();

 private:
  size_t Write(const char *logline, size_t len);
  FILE *fp_;
  char buffer_[64 * 1024];
};

class LogFile : noncopyable {
 public:
  // 每被append flushEveryN次，flush一下，会往文件写，只不过，文件也是带缓冲区的
  LogFile(const std::string basename, int flush_every_n = 1024);
  ~LogFile();

  void Append(const char *logline, int len);
  void Flush();
  bool RollFile();

 private:
  void AppendUnlocked(const char *logline, int len);
  const std::string basename_;
  const int flush_every_n_;
  int count_;
  std::unique_ptr<MutexLock> mutex_;
  std::unique_ptr<AppendFile> file_;
};

}  // namespace log_utility
}  // namespace ambitiontc_webserver

#endif