#include "../inc/eventloop_thread.h"

#include <assert.h>

#include <functional>
#include <iostream>

namespace ambitiontc_webserver {
EventLoopThread::EventLoopThread()
    : loop_(nullptr),
      exiting_(false),
      thread_(std::bind(&EventLoopThread::ThreadFunc, this), "EventLoopThread"),
      mutex_(),
      cond_(mutex_) {}

EventLoopThread::~EventLoopThread() {
  exiting_ = true;
  thread_.Join();
}

EventLoop* EventLoopThread::StartLoop() {
  assert(!thread_.GetStarted());
  thread_.Start();
  {
    MutexLockGuard lock(mutex_);
    // 一直等到ThreadFun在Thread中真正跑起来
    while (loop_ == nullptr) cond_.Wait();
  }
  return loop_;
}


void EventLoopThread::ThreadFunc() {
  EventLoop loop;
  {
    MutexLockGuard lock(mutex_);
    loop_ = &loop;
    cond_.Notify();
  }
  loop.Loop();
  loop_ = nullptr;
}
}  // namespace ambitiontc_webserver