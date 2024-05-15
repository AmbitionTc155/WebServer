#include "../inc/utility.h"

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/*
EINTR错误的产生：当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能返回一个EINTR错误。
例如：在socket服务器端，设置了信号捕获机制，有子进程，当在父进程阻塞于慢系统调用时由父进程捕获到了一个有效信号时，内核会致使accept返回一个EINTR错误(被中断的系统调用)。
EAGAIN错误的产生：非阻塞的系统调用，由于资源限制/不满足条件，导致返回值为EAGAIN
*/

namespace ambitiontc_webserver {
const int MAX_BUFF = 4096;
ssize_t Utility::Readn(int fd, void *buff, size_t n) {
  size_t nleft = n;
  ssize_t nread = 0;
  ssize_t read_sum = 0;
  char *ptr = (char *)buff;
  while (nleft > 0) {
    if ((nread = read(fd, ptr, nleft)) < 0) {
      if (errno == EINTR)
        nread = 0;
      else if (errno == EAGAIN)
        return read_sum;
      else
        return -1;
    } else if (nread == 0)
      break;
    read_sum += nread;
    nleft -= nread;
    ptr += nread;
  }
  return read_sum;
}

ssize_t Utility::Readn(int fd, std::string &in_buffer, bool &zero) {
  ssize_t nread = 0;
  ssize_t read_sum = 0;
  while (true) {
    char buff[MAX_BUFF];
    if ((nread = read(fd, buff, MAX_BUFF)) < 0) {
      if (errno == EINTR)
        continue;
      else if (errno == EAGAIN)
        return read_sum;
      else {
        perror("read error");
        return -1;
      }
    } else if (nread == 0) {
      zero = true;
      break;
    }
    read_sum += nread;
    in_buffer += std::string(buff, buff + nread);
  }
  return read_sum;
}

ssize_t Utility::Readn(int fd, std::string &in_buffer) {
  ssize_t nread = 0;
  ssize_t read_sum = 0;
  while (true) {
    char buff[MAX_BUFF];
    if ((nread = read(fd, buff, MAX_BUFF)) < 0) {
      if (errno == EINTR)
        continue;
      else if (errno == EAGAIN)
        return read_sum;
      else {
        perror("read error");
        return -1;
      }
    } else if (nread == 0) {
      break;
    }
    read_sum += nread;
    in_buffer += std::string(buff, buff + nread);
  }
  return read_sum;
}

ssize_t Utility::Writen(int fd, void *buff, size_t n) {
  size_t nleft = n;
  ssize_t nwritten = 0;
  ssize_t write_sum = 0;
  char *ptr = (char *)buff;
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) <= 0) {
      if (nwritten < 0) {
        if (errno == EINTR) {
          nwritten = 0;
          continue;
        } else if (errno == EAGAIN) {
          return write_sum;
        } else
          return -1;
      }
    }
    write_sum += nwritten;
    nleft -= nwritten;
    ptr += nwritten;
  }
  return write_sum;
}

ssize_t Utility::Writen(int fd, std::string &sbuff) {
  size_t nleft = sbuff.size();
  ssize_t nwritten = 0;
  ssize_t write_sum = 0;
  const char *ptr = sbuff.c_str();
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) <= 0) {
      if (nwritten < 0) {
        if (errno == EINTR) {
          nwritten = 0;
          continue;
        } else if (errno == EAGAIN)
          break;
        else
          return -1;
      }
    }
    write_sum += nwritten;
    nleft -= nwritten;
    ptr += nwritten;
  }
}

/*
SIGPIPE信号产生的原因：
简单来说，就是客户端程序向服务器端程序发送了消息，然后关闭客户端，服务器端返回消息的时候就会收到内核给的SIGPIPE信号。
*/
void Utility::HandleForSigpipe() {
  struct sigaction sa;
  memset(&sa, '\0', sizeof(sa));
  sa.sa_handler = SIG_IGN;
  sa.sa_flags = 0;
  // sigaciton函数结构
  // 参数1：要捕获的信号;参数2：接收到信号之后对信号进行处理的结构体;
  // 参数3：接收到信号之后，保存原来对此信号处理的各种方式与信号（可用来做备份）。如果不需要备份，此处可以填NULL
  if (sigaction(SIGPIPE, &sa, NULL)) return;
}

/*
如果设置了 O_NONBLOCK 标志，read 和 write的行为是不同的
，如果进程没有数据就绪时调用了read ， 或者在缓冲区没有空间时调用了 write
，系统只是简单的返回EAGAIN，而不会阻塞进程.
*/

//设置套接字为非阻塞模式
int Utility::SetSocketNonBlocking(int fd) {
  //读取目前fd对应的套接字的状态
  int flag = fcntl(fd, F_GETFL, 0);
  // 它在读取不到数据时会回传-1，并且设置errno为EAGAIN。
  if (flag == -1) return -1;
  // O_NONBLOCK使其设置为非阻塞模式
  flag |= O_NONBLOCK;
  if (fcntl(fd, F_SETFL, flag) == -1) return -1;
  return 0;
}

/*
TCP_NODELAY:
TCP/IP协议中针对TCP默认开启了Nagle算法。Nagle算法通过减少需要传输的数据包，来优化网络。在内核实现中，数据包的发送和接受会先做缓存，分别对应于写缓存和读缓存。
启动TCP_NODELAY，就意味着禁用了Nagle算法，允许小包的发送。对于延时敏感型，同时数据传输量比较小的应用，开启TCP_NODELAY选项无疑是一个正确的选择。
比如，对于SSH会话，用户在远程敲击键盘发出指令的速度相对于网络带宽能力来说，绝对不是在一个量级上的，所以数据传输非常少；
而又要求用户的输入能够及时获得返回，有较低的延时。如果开启了Nagle算法，就很可能出现频繁的延时，导致用户体验极差。
*/
void Utility::SetSocketNoDelay(int fd) { 
  int enable = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&enable, sizeof(enable));
}

//在客户端断开socket时起作用
void Utility::SetSocketNoLinger(int fd) {
  struct linger klinger;
  klinger.l_onoff = 1;          //表示开启此功能
  klinger.l_linger = 30;        //表示在指定时间能保持正常发送，超时立即放弃发送任何东西。如果设置为0,则立即放弃。单位为秒
  setsockopt(fd, SOL_SOCKET, SO_LINGER, (const char *)&klinger,
             sizeof(klinger));
}

//TCP半关闭
void Utility::ShutDownWR(int fd) {
  shutdown(fd, SHUT_WR);
  // printf("shutdown\n");
}

int Utility::SocketBindListen(int port){
  // 检查port值，取正确区间范围
  if (port < 0 || port > 65535) return -1;
  // 创建socket(IPv4 + TCP)，返回监听描述符
  int listen_fd = 0;
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) return -1;
  // 消除bind时"Address already in use"错误
  int optval = 1;
  if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval,
                 sizeof(optval)) == -1) {
    close(listen_fd);
    return -1;
  }

  // 设置服务器IP和Port，和监听描述副绑定
  struct sockaddr_in server_addr;
  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons((unsigned short)port);
  if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    close(listen_fd);
    return -1;
  }

  // 开始监听，最大等待队列长为LISTENQ
  if (listen(listen_fd, 2048) == -1) {
    close(listen_fd);
    return -1;
  }

  // 无效监听描述符
  if (listen_fd == -1) {
    close(listen_fd);
    return -1;
  }
  return listen_fd;
}



}  // namespace ambitiontc_webserver