/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    eventloop_thread.h
 *	@brief      循环事件的线程封装，内部带有一个eventloop的动作
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___EVENTLOOP_THREAD_H
#define AMBITIONTC___WEBSERVER___EVENTLOOP_THREAD_H

#include "condition.h"
#include "mutex_lock.h"
#include "noncopyable.h"
#include "thread.h"
#include "eventloop.h"

namespace ambitiontc_webserver {
class EventLoopThread : noncopyable {
 public:
  EventLoopThread();
  ~EventLoopThread();

  //将对应的事物循环函数运行起来
  EventLoop* StartLoop();

 private:
  void ThreadFunc();
  //事物循环函数，每个线程一个事物循环函数
  EventLoop* loop_;
  //是否正在退出
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_;
};

}  // namespace ambitiontc_webserver

#endif