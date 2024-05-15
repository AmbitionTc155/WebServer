/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		mutex_lock.h
 *	@brief      线程锁的封装
 *
 *  @author     Tang Chao
 *  @link
 */
#ifndef AMBITIONTC___WEBSERVER___MUTEX_LOCK_H
#define AMBITIONTC___WEBSERVER___MUTEX_LOCK_H

#include <pthread.h>
#include <cstdio>
#include "./noncopyable.h"


namespace ambitiontc_webserver {
class MutexLock : noncopyable {
 public:
  MutexLock() { pthread_mutex_init(&mutex_, NULL); }
  ~MutexLock() {
    pthread_mutex_lock(&mutex_);
    pthread_mutex_destroy(&mutex_);
  }
  // 加锁
  void Lock() { pthread_mutex_lock(&mutex_); }
  // 解锁
  void Unlock() { pthread_mutex_unlock(&mutex_); }
  // 获取对应的线程锁
  pthread_mutex_t *get() { return &mutex_; }

 private:
  pthread_mutex_t mutex_;

  // 友元类不受访问权限影响
 private:
  friend class Condition;
};

// 保护锁，可以用智能指针装(一般使用的时候都是智能指针，这样子在智能指针的作用域可以一直锁住)
class MutexLockGuard : noncopyable {
 public:
  explicit MutexLockGuard(MutexLock &mutex) : mutex_(mutex) { mutex_.Lock(); }
  ~MutexLockGuard() { mutex_.Unlock(); }

 private:
  MutexLock &mutex_;
};
}  // namespace ambitiontc_webserver

#endif