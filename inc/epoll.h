/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    epoll.h
 *	@brief      epoll的封装函数
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___EPOLL_H
#define AMBITIONTC___WEBSERVER___EPOLL_H

#include <sys/epoll.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "channel.h"
#include "httpdata.h"
#include "timer_manager.h"

namespace ambitiontc_webserver {

class Epoll {
 private:
  typedef std::shared_ptr<Channel> SP_Channel;

 public:
  Epoll();
  ~Epoll();
  void EpollAdd(SP_Channel request, int timeout);
  void EpollMod(SP_Channel request, int timeout);
  void EpollDel(SP_Channel request);
  std::vector<std::shared_ptr<Channel>> Poll();
  std::vector<std::shared_ptr<Channel>> GetEventsRequest(int events_num);
  void AddTimer(std::shared_ptr<Channel> request_data, int timeout);
  int GetEpollFd() { return epoll_fd_; }
  void HandleExpired();

 private:
  static const int MAXFDS = 100000;
  int epoll_fd_;
  // epoll_wait()返回的活动事件都在这个数组
  std::vector<epoll_event> events_;
  std::shared_ptr<Channel> fd2chan_[MAXFDS];
  std::shared_ptr<HttpData> fd2http_[MAXFDS];
  TimerManager timer_manager_;
};
}  // namespace ambitiontc_webserver

#endif