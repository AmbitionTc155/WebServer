/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    log_stream.h
 *	@brief      数据的输入输出流，用于log输出
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___LOG_STREAM_H
#define AMBITIONTC___WEBSERVER___LOG_STREAM_H

#include <assert.h>
#include <string.h>

#include <string>

#include "../noncopyable.h"

namespace ambitiontc_webserver {
namespace log_utility {
const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000 * 1000;

template <int SIZE>
class FixedBuffer : noncopyable {
 public:
  FixedBuffer() : cur_(data_) {}

  ~FixedBuffer() {}
  void Append(const char* buf, size_t len) {
    if (Avail() > static_cast<int>(len)) {
      memcpy(cur_, buf, len);
      cur_ += len;
    }
  }
  const char* GetData() const { return data_; }
  int GetLength() const { return static_cast<int>(cur_ - data_); }
  //获得当前储存到什么位置了
  char* GetCurrent() { return cur_; }
  //剩余空间大小
  int Avail() const { return static_cast<int>(End() - cur_); }
  //字符串长度增加，修改cur_为增加后的地址
  void Add(size_t len) { cur_ += len; }
  //重置指针位置，也就是重新装东西
  void Reset() { cur_ = data_; }
  //重置所有地址为0值
  void ResetZero() { memset(data_, 0, sizeof data_); }

 private:
  //获得当前缓存的尾部地址
  const char* End() const { return data_ + sizeof data_; }
  char data_[SIZE];
  char* cur_;
};

class LogStream : noncopyable {
 public:
  typedef FixedBuffer<kSmallBuffer> Buffer;
  LogStream& operator<<(bool v) {
    buffer_.Append(v ? "1" : "0", 1);
    return *this;
  }

  LogStream& operator<<(short);
  LogStream& operator<<(unsigned short);
  LogStream& operator<<(int);
  LogStream& operator<<(unsigned int);
  LogStream& operator<<(long);
  LogStream& operator<<(unsigned long);
  LogStream& operator<<(long long);
  LogStream& operator<<(unsigned long long);
  LogStream& operator<<(const void*);

  LogStream& operator<<(float v) {
    *this << static_cast<double>(v);
    return *this;
  }
  LogStream& operator<<(double);
  LogStream& operator<<(long double);

  LogStream& operator<<(char v) {
    buffer_.Append(&v, 1);
    return *this;
  }

  LogStream& operator<<(const char* str) {
    if (str)
      buffer_.Append(str, strlen(str));
    else
      buffer_.Append("(null)", 6);
    return *this;
  }

  LogStream& operator<<(const unsigned char* str) {
    return operator<<(reinterpret_cast<const char*>(str));
  }

  LogStream& operator<<(const std::string& v) {
    buffer_.Append(v.c_str(), v.size());
    return *this;
  }

  void Append(const char* data, int len) { buffer_.Append(data, len); }

  const Buffer& GetBuffer() const { return buffer_; }
  void ResetBuffer() { buffer_.ResetZero(); }

 private:
  Buffer buffer_;
  template <typename T>
  void FormatInteger(T);
  static const int kMaxNumericSize = 32;
};

}  // namespace log_utility
}  // namespace ambitiontc_webserver

#endif