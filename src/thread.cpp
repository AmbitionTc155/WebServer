#include "../inc/thread.h"

#include <assert.h>
#include <errno.h>
#include <linux/unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <sys/types.h>

#include <iostream>

#include "../inc/current_thread.h"

using namespace std;

namespace ambitiontc_webserver {


typedef Thread::ThreadFunc ThreadFunc;
class ThreadData {
 public:
  ThreadData(const ThreadFunc& func, const string& name, pid_t* tid,
             CountDownLatch* latch)
      : func_(func), name_(name), tid_(tid), latch_(latch) {}
  void RunInThread() {
    *tid_ = CurrentThreadHandle::GetCacheTid();
    tid_ = nullptr;
    latch_
        ->LatchThread();  //告诉主线程，当前子线程已经成功运行起来了，可以继续主线程的任务了
    latch_ = nullptr;
    current_thread::t_thread_name = name_.empty() ? "Thread" : name_.c_str();
    //设计线程的名字
    prctl(PR_SET_NAME, current_thread::t_thread_name);

    func_();
    current_thread::t_thread_name = "finished";
  }

 private:
  ThreadFunc func_;
  string name_;
  pid_t* tid_;
  CountDownLatch* latch_;
};

void* StartThread(void* obj) {
  // static_cast函数用于转化数据类型
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->RunInThread();
  delete data;
  return nullptr;
}

// 线程类的构造函数
Thread::Thread(const ThreadFunc& func, const string& n)
    : started_(false),
      joined_(false),
      pthread_id_(0),
      tid_(0),
      func_(func),
      name_(n),
      latch_(1) {
  SetDefaultName();
}

Thread::~Thread() {
  if (started_ && !joined_) pthread_detach(pthread_id_);
}

void Thread::SetDefaultName() {
  if (name_.empty()) {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread");
    name_ = buf;
  }
}

void Thread::Start() {
  //已经启动再调用Start()会出问题
  assert(!started_);
  started_ = true;
  ThreadData* data = new ThreadData(func_, name_, &tid_, &latch_);
  // pthread_create成功返回0,失败返回错误码
  if (pthread_create(&pthread_id_, NULL, &StartThread, data)) {
    started_ = false;
    delete data;
  } else {  //成功
    latch_.Wait();  //主线程等待子线程成功运行起来，再进行下一步操作
    assert(tid_ > 0);
  }
}

int Thread::Join() {
  assert(started_);
  assert(!joined_);
  joined_ = true;
  return pthread_join(pthread_id_, NULL);
}

}  // namespace ambitiontc_webserver