# A C++ High Performance Web Server

[![Build Status](https://api.travis-ci.com/AmbitionTc155/WebServer.svg?branch=master)](https://github.com/AmbitionTc155/WebServer)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT)

  
## Introduction  

本项目为C++11编写的Web服务器，解析了get、head请求，可处理静态资源，支持HTTP长连接，支持管线化请求，并实现了异步日志，记录服务器运行状态。  

本项目修改于:https://github.com/linyacool/WebServer?tab=readme-ov-file

## Envoirment  
* OS: Ubuntu 20.04
* Complier: g++ 11.4

## Build
  cd build
  cmake ..
	make


## Usage

	./WebServer [-t thread_numbers] [-p port] [-l log_file_path(should begin with '/')]

## Technical points
* 使用Epoll边沿触发的IO多路复用技术，非阻塞IO，使用Reactor模式
* 使用多线程充分利用多核CPU，并使用线程池避免线程频繁创建销毁的开销
* 使用基于小根堆的定时器关闭超时请求
* 主线程只负责accept请求，并以Round Robin的方式分发给其它IO线程(兼计算线程)，锁的争用只会出现在主线程和某一特定线程中
* 使用eventfd实现了线程的异步唤醒
* 使用双缓冲区技术实现了简单的异步日志系统
* 为减少内存泄漏的可能，使用智能指针等RAII机制
* 使用状态机解析了HTTP请求,支持管线化
* 支持优雅关闭连接
 
## Model

并发模型为Reactor+非阻塞IO+线程池，新连接Round Robin分配，详细介绍请参考[并发模型](https://github.com/linyacool/WebServer/blob/master/并发模型.md)
![并发模型](https://github.com/linyacool/WebServer/blob/master/datum/model.png)
