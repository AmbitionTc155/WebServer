/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		main.cpp
 *	@brief		主函数
 *  @author     Tang Chao
 *  @link
 */

#include <unistd.h>

#include <iostream>
#include <string>

#include "inc/eventloop.h"
#include "inc/log_util/logger.h"
#include "inc/server.h"
using namespace std;
using namespace ambitiontc_webserver;
using namespace ambitiontc_webserver::log_utility;

int main(int argc, char *argv[]) {
  int thread_num = 4;
  int port = 80;
  std::string log_path = "./WebServer.log";

  // parse args
  int opt;
  const char *str = "t:l:p:";
  while ((opt = getopt(argc, argv, str)) != -1) {
    switch (opt) {
      case 't': {
        thread_num = atoi(optarg);
        break;
      }
      case 'l': {
        log_path = optarg;
        if (log_path.size() < 2 || optarg[0] != '/') {
          printf("logPath should start with \"/\"\n");
          abort();
        }
        break;
      }
      case 'p': {
        port = atoi(optarg);
        break;
      }
      default:
        break;
    }
  }
  Logger::SetLogFileName(log_path);

// STL库在多线程上应用
#ifndef _PTHREADS
  LOG << "_PTHREADS is not defined !";
#endif
  LOG << "Started!";
  // EventLoop main_loop;
  // Server my_http_server(&main_loop, thread_num, port);
  // my_http_server.Start();
  // main_loop.Loop();
  sleep(3);
  return 0;
}