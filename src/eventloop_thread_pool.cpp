#include "../inc/eventloop_thread_pool.h"

namespace ambitiontc_webserver{
  EventLoopThreadPool::EventLoopThreadPool(EventLoop* base_loop, int num_threads)
  : base_loop_(base_loop), started_(false), num_threads_(num_threads), next_(0){
    if(num_threads_ < 0){
      //LOG << "num_threads_ <= 0";
      abort();
    }
  }

  // 运行线程池，并且将对应的线程和线程中的循环函数储存
  void EventLoopThreadPool::Start(){
    base_loop_->AssertInLoopThread();
    started_ = true;
    for(int i = 0; i < num_threads_; ++i){
      std::shared_ptr<EventLoopThread> t(new EventLoopThread());
      threads_.push_back(t);
      loops_.push_back(t->StartLoop());
    }
  }

  EventLoop* EventLoopThreadPool::GetNextLoop(){
    base_loop_->AssertInLoopThread();
    assert(started_);
    EventLoop* loop = base_loop_;   //当线程池中没有线程时，就直接用主线程
    if(!loops_.empty()){
      loop = loops_[next_];
      next_ = (next_ + 1) % num_threads_;
    }
    return loop;
  }
}