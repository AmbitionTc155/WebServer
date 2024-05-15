#include "../inc/eventloop.h"

#include <sys/epoll.h>
#include <sys/eventfd.h>

#include <iostream>

using namespace std;

namespace ambitiontc_webserver {
__thread EventLoop* t_loop_in_this_thread = nullptr;
// 创建eventfd类似管道的  进程间通讯方式
int CreateEventfd() {
  int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0) {
    // LOG << "Failed in eventfd";
    abort();
  }
  return evtfd;
}

EventLoop::EventLoop()
    : looping_(false),
      poller_(new Epoll()),
      wakeup_fd_(CreateEventfd()),
      stop_(false),
      event_handling_(false),
      calling_pending_functors_(false),
      thread_id_(CurrentThreadHandle::GetCacheTid()),
      pwakeup_channel_(new Channel(this, wakeup_fd_)) {
  if (t_loop_in_this_thread) {
  } else
    t_loop_in_this_thread = this;
  pwakeup_channel_->SetEvents(EPOLLIN | EPOLLET);
  pwakeup_channel_->SetReadHandler(bind(&EventLoop::HandleRead, this));
  pwakeup_channel_->SetConnHandler(bind(&EventLoop::HandleConn, this));
  poller_->EpollAdd(pwakeup_channel_, 0);
}

void EventLoop::HandleConn() { UpdatePoller(pwakeup_channel_, 0); }

void EventLoop::HandleRead(){
  uint64_t one = 1;
  ssize_t n = Utility::Readn(wakeup_fd_, &one, sizeof one);
  if (n != sizeof one) {
    //LOG << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
  }
  // EPOLLIN: 连接到达；有数据来临
  // EPOLLET: 边缘触发
  pwakeup_channel_->SetEvents(EPOLLIN | EPOLLET);
}


EventLoop::~EventLoop() {
  close(wakeup_fd_);
  t_loop_in_this_thread = nullptr;
}

void EventLoop::Wakeup() {
  uint64_t one = 1;
  ssize_t n = Utility::Readn(wakeup_fd_, &one, sizeof one);
  if (n != sizeof one) {
    // LOG << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
  }
  // EPOLLIN: 连接到达；有数据来临
  // EPOLLET: 边缘触发
  pwakeup_channel_->SetEvents(EPOLLIN | EPOLLET);
}

void EventLoop::RunInLoop(EventLoopFunc&& cb) {
  if (IsInLoopThread())
    cb();
  else
    QueueInLoop(std::move(cb));
}

void EventLoop::QueueInLoop(EventLoopFunc&& cb) {
  {
    MutexLockGuard lock(mutex_);
    pending_func_.emplace_back(std::move(cb));
  }

  if (!IsInLoopThread() || calling_pending_functors_) Wakeup();
}

void EventLoop::Loop() {
  assert(!looping_);
  assert(IsInLoopThread());
  looping_ = true;
  stop_ = false;
  // LOG_TRACE << "EventLoop " << this << " start looping";
  std::vector<shared_ptr<Channel>> ret;
  while (!stop_) {
    // cout << "doing" << endl;
    ret.clear();
    ret = poller_->Poll();
    event_handling_ = true;
    for (auto& it : ret) it->HandleEvents();
    event_handling_ = false;
    DoPendingFunction();
    //每执行完一次将超时的清除
    poller_->HandleExpired();
  }
  looping_ = false;
}

void EventLoop::DoPendingFunction() {
  std::vector<EventLoopFunc> functors;
  calling_pending_functors_ = true;

  {
    MutexLockGuard lock(mutex_);
    functors.swap(pending_func_);
  }

  for (size_t i = 0; i < functors.size(); ++i) functors[i]();
  calling_pending_functors_ = false;
}

void EventLoop::Stop() {
  stop_ = true;
  if (!IsInLoopThread()) {
    Wakeup();
  }
}

}  // namespace ambitiontc_webserver