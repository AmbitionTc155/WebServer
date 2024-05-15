/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    utility.h
 *	@brief      项目的工具包，提供一些辅助函数
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___UTILITY_H
#define AMBITIONTC___WEBSERVER___UTILITY_H

#include <cstdlib>
#include <string>

namespace ambitiontc_webserver {
class Utility {
 public:
  static ssize_t Readn(int fd, void *buff, size_t n);
  static ssize_t Readn(int fd, std::string &inBuffer, bool &zero);
  static ssize_t Readn(int fd, std::string &inBuffer);
  static ssize_t Writen(int fd, void *buff, size_t n);
  static ssize_t Writen(int fd, std::string &sbuff);
  static void HandleForSigpipe();
  static int SetSocketNonBlocking(int fd);
  static void SetSocketNoDelay(int fd);
  static void SetSocketNoLinger(int fd);
  static void ShutDownWR(int fd);
  static int SocketBindListen(int port);
};
}  // namespace ambitiontc_webserver

#endif