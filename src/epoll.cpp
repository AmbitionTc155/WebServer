#include "../inc/epoll.h"

#include <assert.h>

#include <iostream>
using namespace std;

namespace ambitiontc_webserver {
const int EVENTSNUM = 4096;
const int EPOLLWAIT_TIME = 10000;

// EPOLL_CLOEXEC标志与open 时的O_CLOEXEC
// 标志类似，即进程被替换时会关闭打开的文件描述符
// 防止fd描述符一直被被创建
Epoll::Epoll() : epoll_fd_(epoll_create1(EPOLL_CLOEXEC)), events_(EVENTSNUM) {
  assert(epoll_fd_);
}

Epoll::~Epoll() {}

//注册新描述符
void Epoll::EpollAdd(SP_Channel request, int timeout) {
  int fd = request->GetFd();
  if (timeout > 0) {
    AddTimer(request, timeout);
    fd2http_[fd] = request->GetHolder();
  }
  struct epoll_event event;
  event.data.fd = fd;
  event.events = request->GetEvents();
  request->EqualAndUpdateLastEvents();
  fd2chan_[fd] = request;
  if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event) < 0) {
    perror("epoll_add error");
    fd2chan_[fd].reset();
  }
}

//修改描述符状态
void Epoll::EpollMod(SP_Channel request, int timeout) {
  if (timeout > 0) AddTimer(request, timeout);
  int fd = request->GetFd();
  if (!request->EqualAndUpdateLastEvents()) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->GetEvents();
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event) < 0) {
      perror("epoll_mod error");
      fd2chan_[fd].reset();
    }
  }
}

// 从epoll中删除描述符
void Epoll::EpollDel(SP_Channel request) {
  int fd = request->GetFd();
  struct epoll_event event;
  event.data.fd = fd;
  event.events = request->GetLastEvents();
  if (epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &event) < 0) {
    perror("epoll_del error");
  }
  fd2chan_[fd].reset();
  fd2http_[fd].reset();
}
// 返回活跃事件数
std::vector<std::shared_ptr<Channel>> Epoll::Poll() {
  while (true) {
    int event_count = epoll_wait(epoll_fd_, &*events_.begin(), events_.size(),
                                 EPOLLWAIT_TIME);
    if (event_count < 0) perror("epoll wait error");
    std::vector<SP_Channel> req_data = GetEventsRequest(event_count);
    if (req_data.size() > 0) return req_data;
  }
}

void Epoll::HandleExpired() { timer_manager_.HandleExpiredEvent(); }

// 分发处理函数
std::vector<std::shared_ptr<Channel>> Epoll::GetEventsRequest(int events_num) {
  std::vector<SP_Channel> req_data;
  for (int i = 0; i < events_num; ++i) {
    //获取有事件产生的描述符
    int fd = events_[i].data.fd;
    SP_Channel cur_req = fd2chan_[fd];
    if (cur_req) {
      cur_req->SetRevents(events_[i].events);
      cur_req->SetEvents(0);
      req_data.push_back(cur_req);
    } else {
      // LOG << "SP cur_req is invalid";
    }
  }
  return req_data;
}

void Epoll::AddTimer(SP_Channel request_data, int timeout) {
  shared_ptr<HttpData> t = request_data->GetHolder();
  if (t)
    timer_manager_.AddTimer(t, timeout);
  else{}
  // LOG << "timer add fall";
}

}  // namespace ambitiontc_webserver