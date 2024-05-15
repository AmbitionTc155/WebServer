/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		condition.h
 *	@brief      条件锁，这个是条件锁线程，用于一些时间等待，或者其他指令的等待
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___CONDITION_H
#define AMBITIONTC___WEBSERVER___CONDITION_H

#include <errno.h>
#include <pthread.h>
#include <time.h>

#include <cstdint>

#include "mutex_lock.h"
#include "noncopyable.h"

namespace ambitiontc_webserver {
class Condition : noncopyable {
 public:
  explicit Condition(MutexLock &mutex) : mutex_(mutex) {
    //条件锁线程的初始化
    pthread_cond_init(&cond_, NULL);
  }
  //条件锁线程的摧毁
  ~Condition() { pthread_cond_destroy(&cond_); }
  // pthread_cond_wait用于阻塞当前线程，等待别的线程使用notify来唤醒
  void Wait() { pthread_cond_wait(&cond_, mutex_.get()); }
  // pthread_cond_signal函数的作用是发送一个信号给另外一个正在处于阻塞等待状态的线程,
  // 使其脱离阻塞状态, 继续执行.如果没有线程处在阻塞等待状态,
  // pthread_cond_signal也会成功返回。
  void Notify() { pthread_cond_signal(&cond_); }
  // pthread_cond_broadcast唤醒全部线程
  void NotifyAll() { pthread_cond_broadcast(&cond_); }

  // pthread_cond_timedwait()用于等待一个条件变量，等待条件变量的同时可以设置等待超时。
  // 这是一个非常有用的功能，如果不想一直等待某一条件变量，就可以使用这个函数。
  bool WaitForSeconds(int seconds) {
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += static_cast<time_t>(seconds);
    return ETIMEDOUT == pthread_cond_timedwait(&cond_, mutex_.get(), &abstime);
  }

 private:
  MutexLock &mutex_;
  pthread_cond_t cond_;
};
}  // namespace ambitiontc_webserver

#endif