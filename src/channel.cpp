#include "../inc/channel.h"

#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <queue>

#include "../inc/epoll.h"
#include "../inc/eventloop.h"
#include "../inc/utility.h"

using namespace std;

namespace ambitiontc_webserver {
Channel::Channel(EventLoop* loop)
    : loop_(loop), events_(0), last_events_(0), fd_(0) {}
Channel::Channel(EventLoop* loop, int fd)
    : loop_(loop), fd_(fd), events_(0), last_events_(0) {}
Channel::~Channel() {}

int Channel::GetFd(){return fd_;}

void Channel::SetFd(int fd){fd_ = fd;}

void Channel::HandleRead(){
  if(ReadHandler_){
    ReadHandler_();
  }
}

void Channel::HandleWrite(){
  if(WriteHandle_){
    WriteHandle_();
  }
}

void Channel::HandleConn(){
  if(ConnHandle_){
    ConnHandle_();
  }
}


}  // namespace ambitiontc_webserver