#include "../inc/server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <functional>
using namespace std;

namespace ambitiontc_webserver {
Server::Server(EventLoop *loop, int thread_num, int port)
    : loop_(loop),
      thread_num_(thread_num),
      event_loop_thread_pool_(new EventLoopThreadPool(loop_, thread_num)),
      started_(false),
      accept_channel_(new Channel(loop_)),
      port_(port),
      listen_fd_(Utility::SocketBindListen(port_)) {
  accept_channel_->SetFd(listen_fd_);
  Utility::HandleForSigpipe();
  if (Utility::SetSocketNonBlocking(listen_fd_) < 0) {
    perror("set socket non block failed");
    abort();
  }
}

void Server::Start() {
  event_loop_thread_pool_->Start();
  accept_channel_->SetEvents(EPOLLIN | EPOLLET);
  accept_channel_->SetReadHandler(bind(&Server::HandNewConn, this));
  accept_channel_->SetConnHandler(bind(&Server::HandThisConn, this));
  loop_->AddToPoller(accept_channel_, 0);
  started_ = true;
}

void Server::HandNewConn() {
  struct sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(struct sockaddr_in));
  socklen_t client_addr_len = sizeof(client_addr);
  int accept_fd = 0;
  while ((accept_fd = accept(listen_fd_, (struct sockaddr *)&client_addr,
                             &client_addr_len)) > 0) {
    EventLoop *loop = event_loop_thread_pool_->GetNextLoop();
    //LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":"
    //    << ntohs(client_addr.sin_port);
    //限制服务器的最大并发连接数
    if(accept_fd>= MAXFDS){
      close(accept_fd);
      continue;
    }
    //设为非阻塞模式
    if(Utility::SetSocketNonBlocking(accept_fd) < 0){
      //LOG << "Set non block failed!"
      return;
    }
    Utility::SetSocketNoDelay(accept_fd);
    shared_ptr<HttpData> req_info(new HttpData(loop, accept_fd));
    req_info->GetChannel()->SetHolder(req_info);
    loop->QueueInLoop(std::bind(&HttpData::NewEvent, req_info));
  }
  accept_channel_->SetEvents(EPOLLIN | EPOLLET);
}

}  // namespace ambitiontc_webserver