/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    channel.h
 *	@brief      事务管理类，用于管理每个客户端的请求状态和过程，每个客户端的描述符号对应一个channel
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___CHANNEL_H
#define AMBITIONTC___WEBSERVER___CHANNEL_H

#include <sys/epoll.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "timer_manager.h"

namespace ambitiontc_webserver {
class EventLoop;
class HttpData;
}  // namespace ambitiontc_webserver


namespace ambitiontc_webserver {
class Channel{
  private:
   typedef std::function<void()> CallBack;

  public:
   Channel(EventLoop* loop);
   Channel(EventLoop* loop, int fd);
   ~Channel();
   int GetFd();
   void SetFd(int fd);
   void SetHolder(std::shared_ptr<HttpData> holder) { holder_ = holder; }
   std::shared_ptr<HttpData> GetHolder() {
     std::shared_ptr<HttpData> ret(holder_.lock());
     return ret;
  }
  void SetReadHandler(CallBack&& readhandler) { ReadHandler_ = readhandler; }
  void SetWriteHandler(CallBack&& writehandler) { WriteHandle_ = writehandler; }
  void SetErrorHandler(CallBack&& errorhandler) { ErrorHandle_ = errorhandler; }
  void SetConnHandler(CallBack&& connhandler) { ConnHandle_ = connhandler; }

  void HandleEvents(){
    events_ = 0;
    //触发挂起事件，并且没有触发可读事件
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
      events_ = 0;
      return;
    }
    //触发错误事件
    if(revents_ & EPOLLERR){
      if(ErrorHandle_)ErrorHandle_();
      events_ = 0;
      return;
    }
    // 触发可读事件 | 高优先级可读事件 | 对端(客户端)关闭链接
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
      HandleRead();
    }
    // 触发可写事件
    if (revents_ & EPOLLOUT) {
      HandleWrite();
    }
    // 处理更新监听事件
    HandleConn();
  }
  void HandleRead();
  void HandleWrite();
  void HandleError(int fd, int err_num, std::string short_msg);
  void HandleConn();
  void SetRevents(__uint32_t ev){revents_ = ev;}
  void SetEvents(__uint32_t ev){events_ = ev;}
  __uint32_t& GetEvents(){ return events_;}
  bool EqualAndUpdateLastEvents(){
    bool ret = (last_events_ == events_);
    last_events_ = events_;
    return ret;
  }
  __uint32_t GetLastEvents(){return last_events_;}
 private:
  
  // int ParseURI();
  // int ParseHeaders();
  // int AnalysisRequest();

  CallBack ReadHandler_;
  CallBack WriteHandle_;
  CallBack ErrorHandle_;
  CallBack ConnHandle_;
private:
  
  EventLoop* loop_;
  int fd_;
  __uint32_t events_;
  __uint32_t revents_;
  __uint32_t last_events_;

  //方便找到上层持有该Channel的对象
  std::weak_ptr<HttpData> holder_;
};

}  // namespace ambitiontc_webserver

#endif