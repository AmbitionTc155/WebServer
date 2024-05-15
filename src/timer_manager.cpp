#include "../inc/timer_manager.h"

#include <sys/time.h>

namespace ambitiontc_webserver {
TimerNode::TimerNode(std::shared_ptr<HttpData> request_data, int timeout)
    : deleted_(false), sp_httpdata_(request_data) {
  struct timeval now;
  gettimeofday(&now, NULL);
  // 以毫秒计
  expired_time_ =
      (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimerNode::~TimerNode(){
  if(sp_httpdata_) sp_httpdata_->HandleClose();
}

TimerNode::TimerNode(TimerNode & tn)
: sp_httpdata_(tn.sp_httpdata_), expired_time_(0){}

void TimerNode::Updata(int timeout){
  struct timeval now;
  gettimeofday(&now, NULL);
  // 以毫秒计
  expired_time_ =
      (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimerNode::IsValid(){
  struct timeval now;
  gettimeofday(&now, NULL);
  size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
  if(temp < expired_time_)return true;
  else{
    this->SetDeleted();
    return false;
  }
}

void TimerNode::ClearReq(){
  // sp_httpdata_释放了所有管理权，如果sp_httpdata_记数为0,在这里会执行析构
  sp_httpdata_.reset();
  this->SetDeleted();
}

TimerManager::TimerManager(){}

TimerManager::~TimerManager() {}

void TimerManager::AddTimer(std::shared_ptr<HttpData> sp_httpdata, int timeout){
  SPTimerNode new_node(new TimerNode(sp_httpdata, timeout));
  timer_node_queue_.push(new_node);
  sp_httpdata->LinkTimer(new_node);
}

/* 处理逻辑是这样的~
因为
(1) 优先队列不支持随机访问
(2) 即使支持，随机删除某节点后破坏了堆的结构，需要重新更新堆结构。
所以对于被置为deleted的时间节点，会延迟到它到超时或它前面的节点都被删除时，它才会被删除。
一个点被置为deleted,它最迟会在TIMER_TIME_OUT时间后被删除。
这样做有两个好处：
(1) 第一个好处是不需要遍历优先队列，省时。
(2) 第二个好处是给超时时间一个容忍的时间，就是设定的超时时间是删除的下限(并不是一到超时时间就立即删除)，如果监听的请求在超时后的下一次请求中又一次出现了，
就不用再重新申请RequestData节点了，这样可以继续重复利用前面的RequestData，减少了一次delete和一次new的时间。
*/
void TimerManager::HandleExpiredEvent(){
  while(!timer_node_queue_.empty()){
    SPTimerNode ptimer_now = timer_node_queue_.top();
    if(ptimer_now->IsDeleted())
      timer_node_queue_.pop();
    else if (ptimer_now->IsValid())
      timer_node_queue_.pop();
    else
      break;
  }
}


}  // namespace ambitiontc_webserver