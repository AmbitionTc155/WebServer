#include "../../inc/log_util/log_stream.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <limits>

namespace ambitiontc_webserver {
namespace log_utility {

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;

const char digitsHex[] = "0123456789ABCDEF";

template <typename T>
size_t Convert(char buf[], T value) {
  T i = value;
  char* p = buf;

  do {
    int lsd = static_cast<int>(i % 10);
    i /= 10;
    *p++ = zero[lsd];
  } while (i != 0);

  if (value < 0) {
    *p++ = '-';
  }
  *p = '\0';
  std::reverse(buf, p);

  return p - buf;
}

// template class FixedBuffer<kSmallBuffer>;
// template class FixedBuffer<kLargeBuffer>;

template <typename T>
void LogStream::FormatInteger(T v) {
  if (buffer_.Avail() >= kMaxNumericSize) {
    size_t len = Convert(buffer_.GetCurrent(), v);
    buffer_.Add(len);
  }
}


LogStream& LogStream::operator<<(short v) {
  *this << static_cast<int>(v);
  return *this;
}

LogStream& LogStream::operator<<(unsigned short v) {
  *this << static_cast<unsigned int>(v);
  return *this;
}

LogStream& LogStream::operator<<(int v) {
  FormatInteger(v);
  return *this;
}

LogStream& LogStream::operator<<(unsigned int v) {
  FormatInteger(v);
  return *this;
}

LogStream& LogStream::operator<<(long v) {
  FormatInteger(v);
  return *this;
}

LogStream& LogStream::operator<<(unsigned long v) {
  FormatInteger(v);
  return *this;
}

LogStream& LogStream::operator<<(long long v) {
  FormatInteger(v);
  return *this;
}

LogStream& LogStream::operator<<(unsigned long long v) {
  FormatInteger(v);
  return *this;
}

// FIXME: replace this with Grisu3 by Florian Loitsch.
LogStream& LogStream::operator<<(double v) {
  if (buffer_.Avail() >= kMaxNumericSize) {
    int len = snprintf(buffer_.GetCurrent(), kMaxNumericSize, "%.12g", v);
    buffer_.Add(len);
  }
  return *this;
}

}  // namespace log_utility
}  // namespace ambitiontc_webserver