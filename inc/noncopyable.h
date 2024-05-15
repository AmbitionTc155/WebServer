/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		noncopyable.h
 *	@brief
 *禁止拷贝的基类(在后面的函数定义中直接继承该类，可以使对应的类禁止拷贝)
 *  @author     Tang Chao
 *  @link
 */
#ifndef AMBITIONTC___WEBSERVER___NONCOPYABLE_H
#define AMBITIONTC___WEBSERVER___NONCOPYABLE_H

namespace ambitiontc_webserver {
class noncopyable {
 protected:
  noncopyable() {}
  ~noncopyable() {}

 private:
  noncopyable(const noncopyable&);
  const noncopyable& operator=(const noncopyable&);
};
}  // namespace ambitiontc_webserver

#endif