/**
 *	@copyright	(C++) 2024 by AmbitionTc
 *	@file		    httpdata.h
 *	@brief      http接收发送以及解析，
 *对应的子线程中的读写函数都在httpdata类中
 *
 *  @author     Tang Chao
 *  @link
 */

#ifndef AMBITIONTC___WEBSERVER___HTTPDATA_H
#define AMBITIONTC___WEBSERVER___HTTPDATA_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>



namespace ambitiontc_webserver {

class EventLoop;
class TimerNode;
class Channel;

enum ProcessState {
  STATE_PARSE_URI = 1,
  STATE_PARSE_HEADERS,
  STATE_RECV_BODY,
  STATE_ANALYSIS,
  STATE_FINISH
};

enum URIState {
  PARSE_URI_AGAIN = 1,
  PARSE_URI_ERROR,
  PARSE_URI_SUCCESS,
};

enum HeaderState {
  PARSE_HEADER_SUCCESS = 1,
  PARSE_HEADER_AGAIN,
  PARSE_HEADER_ERROR
};

enum AnalysisState { ANALYSIS_SUCCESS = 1, ANALYSIS_ERROR };

enum ParseState {
  H_START = 0,
  H_KEY,
  H_COLON,
  H_SPACES_AFTER_COLON,
  H_VALUE,
  H_CR,
  H_LF,
  H_END_CR,
  H_END_LF
};

enum ConnectionState { H_CONNECTED = 0, H_DISCONNECTING, H_DISCONNECTED };

enum HttpMethod { METHOD_POST = 1, METHOD_GET, METHOD_HEAD };

enum HttpVersion { HTTP_10 = 1, HTTP_11 };

class MimeType {
 private:
  static void Init();
  static std::unordered_map<std::string, std::string> mime;
  MimeType();
  MimeType(const MimeType& m);

 public:
  static std::string GetMime(const std::string& suffix);

 private:
  static pthread_once_t once_control;
};

// enable_shared_from_this在把当前类指针传给外部时，不用this，
//改为用shared_from_this()，即可防止多次析构同一地址带来的异常退出
class HttpData : public std::enable_shared_from_this<HttpData> {
 public:
  HttpData(EventLoop* loop, int connfd);
  ~HttpData();
  void Reset();
  void SeperateTimer();
  void LinkTimer(std::shared_ptr<TimerNode> mtimer) { timer_ = mtimer; }
  std::shared_ptr<Channel> GetChannel() { return channel_; }
  EventLoop* GetLoop() { return loop_; }
  void HandleClose();
  void NewEvent();

 private:
  EventLoop* loop_;                             //对应的事件循环类
  std::shared_ptr<Channel> channel_;            //对应的事件
  int fd_;                                      //事件的内部编号
  std::string in_buffer_;                       //读取缓冲区
  std::string out_buffer_;                      //写入缓冲区
  bool error_;                                  //是否出错
  ConnectionState connection_state_;            //连接状态
  HttpMethod method_;                           // http连接状态
  HttpVersion http_version_;                    // http连接版本
  std::string file_name_;                       //文件名字
  std::string path_;                            //文件地址
  int now_read_pos_;                            //当前读取的位置
  ProcessState state_;                          //处理状态
  ParseState h_state_;                          //转义状态
  bool keep_alive_;                             //是否保持活跃
  std::map<std::string, std::string> headers_;  //处理头
  std::weak_ptr<TimerNode> timer_;              //事件节点

  void HandleRead();   //处理读事物
  void HandleWrite();  //处理写事物
  void HandleConn();   //处理更新事物
  void HandleError(int fd, int err_num, std::string short_msg);  //处理错误事物

  URIState ParseURI();              //转义URI
  HeaderState ParseHeaders();       //处理头文件
  AnalysisState AnalysisRequest();  //分析请求内容
};

}  // namespace ambitiontc_webserver
#endif