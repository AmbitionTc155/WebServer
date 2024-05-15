#include "../inc/current_thread.h"

#include <sys/syscall.h>

#include <iostream>
using namespace std;

namespace ambitiontc_webserver {

namespace current_thread {
__thread int t_cached_tid = 0;
__thread char t_tid_string[32];
__thread int t_tid_string_length = 6;
__thread const char* t_thread_name = "default";
}  // namespace current_thread

inline pid_t CurrentThreadHandle::GetTid() {
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void CurrentThreadHandle::CacheTid() {
  if (current_thread::t_cached_tid == 0) {
    current_thread::t_cached_tid = GetTid();
    current_thread::t_tid_string_length = snprintf(
        current_thread::t_tid_string, sizeof current_thread::t_tid_string,
        "%5d", current_thread::t_cached_tid);
  }
}

}  // namespace ambitiontc_webserver