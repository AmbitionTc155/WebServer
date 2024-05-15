/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    server.h
 *	@brief      服务器函数，封装了所有的东西
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___SERVER_H
#define AMBITIONTC___WEBSERVER___SERVER_H

#include <memory>

#include "channel.h"
#include "eventloop.h"
#include "eventloop_thread_pool.h"

namespace ambitiontc_webserver {
class Server {
 public:
  Server(EventLoop *loop, int thread_num, int port);
  ~Server() {}
  EventLoop *GetLoop() const { return loop_; }
  void Start();
  void HandNewConn();
  void HandThisConn() { loop_->UpdatePoller(accept_channel_); }

 private:
  EventLoop *loop_;
  int thread_num_;
  std::unique_ptr<EventLoopThreadPool> event_loop_thread_pool_;
  bool started_;
  std::shared_ptr<Channel> accept_channel_;
  int port_;
  int listen_fd_;
  static const int MAXFDS =100000;
};
}  // namespace ambitiontc_webserver

#endif