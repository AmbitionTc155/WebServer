/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    eventloop_thread_pool.h
 *	@brief      循环事件的线程池，每个线程池中含有一个事物循环处理函数
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___EVENTLOOP_THREAD_POOL_H
#define AMBITIONTC___WEBSERVER___EVENTLOOP_THREAD_POOL_H
#include <memory>
#include "eventloop_thread.h"
#include "noncopyable.h"
#include <vector>
namespace ambitiontc_webserver{
  class EventLoopThreadPool : noncopyable{
    public:
    EventLoopThreadPool(EventLoop * base_loop, int num_threads);
    ~EventLoopThreadPool(){}
    void Start();
    EventLoop* GetNextLoop();
    private:
    EventLoop* base_loop_;          //主线程中的事务循环器
    bool started_;                  //线程池是否开始运行
    int num_threads_;               //线程池的容量
    int next_;                      //线程池下一个存放东西的池子编号
    std::vector<std::shared_ptr<EventLoopThread>> threads_;   //存放线程池中具体的线程
    std::vector<EventLoop*> loops_; //存放线程池中thread_里面对应的事物函数
  };
}

#endif