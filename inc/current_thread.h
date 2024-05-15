/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		current_thread.h
 *	@brief
 *当前线程中的信息，__thread修饰的变量，在每个线程中都有一个独一无二的
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___CURRENT_THREAD_H
#define AMBITIONTC___WEBSERVER___CURRENT_THREAD_H
#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
namespace ambitiontc_webserver {

//线程信息 定义在.cpp文件中 如果定义不放在cpp中，在编译的时候会出现多重编译报错
namespace current_thread {
extern __thread int t_cached_tid;
extern __thread char t_tid_string[32];
extern __thread int t_tid_string_length;
extern __thread const char* t_thread_name;
}  // namespace current_thread

class CurrentThreadHandle {
 public:
  static pid_t GetTid();
  //缓存Tid
  static void CacheTid();
  static int GetCacheTid() {
    if (__builtin_expect(current_thread::t_cached_tid == 0, 0)) CacheTid();
    return current_thread::t_cached_tid;
  }
  static const char* GetTidString() { return current_thread::t_tid_string; }
  static int GetTidStringLength() {
    return current_thread::t_tid_string_length;
  }
  static const char* GetThreadName() { return current_thread::t_thread_name; }
};
}  // namespace ambitiontc_webserver
#endif
