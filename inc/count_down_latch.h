/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		count_down_latch.h
 *	@brief
 *主要作用是确保Thread中传进去的func真的启动了以后，外层的start才返回
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___COUNT_DOWN_LATCH_H
#define AMBITIONTC___WEBSERVER___COUNT_DOWN_LATCH_H

#include "condition.h"
#include "mutex_lock.h"
#include "noncopyable.h"

namespace ambitiontc_webserver {
class CountDownLatch : noncopyable {
 public:
  explicit CountDownLatch(int count);
  //线程进入阻塞状态
  void Wait();
  //解锁所有的线程阻塞
  void LatchThread();

 private:
  // mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。
  mutable MutexLock mutex_;
  
  Condition condition_;
  //这个count_可以改成状态值，不易让人误解
  int count_;
};
}  // namespace ambitiontc_webserver

#endif