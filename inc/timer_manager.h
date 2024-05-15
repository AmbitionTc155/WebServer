/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    timer_manager.h
 *	@brief      时间管理器，管理一些超时的请求
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___TIMER_MANAGER_H
#define AMBITIONTC___WEBSERVER___TIMER_MANAGER_H
#include <unistd.h>

#include <deque>
#include <memory>
#include <queue>

#include "httpdata.h"
#include "mutex_lock.h"
#include "noncopyable.h"

namespace ambitiontc_webserver {
class HttpData;

//时间节点类
class TimerNode {
 public:
  TimerNode(std::shared_ptr<HttpData> request_data, int timeout);
  ~TimerNode();
  TimerNode(TimerNode &tn);
  void Updata(int timeout);
  bool IsValid();
  void ClearReq();
  void SetDeleted() { deleted_ = true; }
  bool IsDeleted() const { return deleted_; }
  size_t GetExpTime() const { return expired_time_; }

 private:
  //是否已经删除了
  bool deleted_;
  //超时的时间点，大于此值表示超时了
  size_t expired_time_;
  std::shared_ptr<HttpData> sp_httpdata_;
};

struct TimerCmp {
  bool operator()(std::shared_ptr<TimerNode> &a,
                  std::shared_ptr<TimerNode> &b) const {
    return a->GetExpTime() > b->GetExpTime();
  }
};

class TimerManager {
 public:
  TimerManager();
  ~TimerManager();
  void AddTimer(std::shared_ptr<HttpData> sp_http_data, int timeout);
  void HandleExpiredEvent();

 private:
  typedef std::shared_ptr<TimerNode> SPTimerNode;

  //时间管理的堆
  std::priority_queue<SPTimerNode, std::deque<SPTimerNode>, TimerCmp>
      timer_node_queue_;
};
}  // namespace ambitiontc_webserver

#endif