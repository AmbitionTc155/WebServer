/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		thread.h
 *	@brief      这个是线程的封装函数
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___THREAD_H
#define AMBITIONTC___WEBSERVER___THREAD_H

#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <functional>
#include <memory>
#include <string>

#include "count_down_latch.h"
#include "noncopyable.h"

namespace ambitiontc_webserver {
class Thread : noncopyable {
 public:
  //线程运行的函数
  typedef std::function<void()> ThreadFunc;
  // explicit 表明要求不能隐形构造
  explicit Thread(const ThreadFunc&, const std::string& name = std::string());
  ~Thread();
  //线程开始函数
  void Start();
  //将线程加入到主线程，让主线程等待子线程结束
  int Join();
  bool GetStarted() const{return started_;}
  pid_t GetTid() const{return tid_;}
  const std::string& GetName() const {return name_;}
 private:
  void SetDefaultName();

 private:
  bool started_;  //线程是否开始标志位
  bool joined_;  //线程是否加入到主线程中标志位
  pthread_t pthread_id_;  //线程对应编号
  pid_t tid_;        //当前线程的id，系统给的
  ThreadFunc func_;  //线程运行函数
  std::string name_;    //线程的名字
  CountDownLatch latch_;    //用于确保线程正常运行的工具
};
}  // namespace ambitiontc_webserver

#endif