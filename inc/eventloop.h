/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    eventloop.h
 *	@brief      处理事物的类，每个线程一个eventloop循环
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___EVENTLOOP_H
#define AMBITIONTC___WEBSERVER___EVENTLOOP_H

#include <assert.h>

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "channel.h"
#include "current_thread.h"
#include "epoll.h"
#include "thread.h"
#include "utility.h"

namespace ambitiontc_webserver {
class EventLoop {
 public:
  typedef std::function<void()> EventLoopFunc;

  EventLoop();
  ~EventLoop();
  // 开始事件循环调用该函数的线程必须是该EventLoop所在线程，也就是Loop函数不能跨线程调用
  void Loop();
  // 停止 Loop
  void Stop();
  // 如果当前线程就是创建此EventLoop的线程， 就调用callback(关闭连接 EpollDel)否则就放入等待执行函数区
  void RunInLoop(EventLoopFunc&& cb);
  // 把此函数放入等待执行函数区  如果当前是跨线程  或者正在调试等待的函数则唤醒
  void QueueInLoop(EventLoopFunc&& cb);
  bool IsInLoopThread() const {
    return thread_id_ == CurrentThreadHandle::GetCacheTid();
  }
  void AssertInLoopThread() { assert(IsInLoopThread()); }
  // 只关闭连接(此时事件表中删除fd及其绑定的事件)
  void Shutdown(std::shared_ptr<Channel> channel) {}
  // 从epoll内核事件表中删除fd及其绑定的事件
  void RemoveFromPoller(std::shared_ptr<Channel> channel) {
    poller_->EpollDel(channel);
  }
  // 在epoll内核事件表修改fd及其绑定的事件
  void UpdatePoller(std::shared_ptr<Channel> channel, int timeout = 0) {
    poller_->EpollMod(channel, timeout);
  }
  // 把fd和绑定的事件注册到epoll内核事件表
  void AddToPoller(std::shared_ptr<Channel> channel, int timeout = 0) {
    poller_->EpollAdd(channel, timeout);
  }

 private:
  // 异步唤醒SubLoop的epoll_wait(向event_fd中写入数据)
  void Wakeup();
  // eventfd的读回调函数(因为event_fd写了数据，所以触发可读事件，从eventfd读数据)
  void HandleRead();
  void HandleConn();
  // 执行正在等待的函数(SubLoop注册EpollAdd连接套接字以及绑定事件的函数)
  void DoPendingFunction();


 private:
  bool looping_;
  bool stop_;
  bool event_handling_;
  bool calling_pending_functors_;

  // 用于异步唤醒subLoop的Loop函数的
  int wakeup_fd_;
  const pid_t thread_id_;

  // io多路复用 分发器
  std::shared_ptr<Epoll> poller_;

  mutable MutexLock mutex_;
  // 正在等待处理的函数
  std::vector<EventLoopFunc> pending_func_;
  // 用于异步唤醒channel
  std::shared_ptr<Channel> pwakeup_channel_;
};

}  // namespace ambitiontc_webserver

#endif
