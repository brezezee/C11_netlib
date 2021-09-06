#pragma once

#include <string>
#include <sstream>
#include <map>
//#include "TcpConnection.h"

typedef struct _HttpRequestContext {
	std::string method;
	std::string url;
	std::string version;
	std::map<std::string, std::string> header;
	std::string body;
}HttpRequestContext;

typedef struct _HttpResponseContext {
    std::string version;
    std::string statecode;
    std::string statemsg;
	std::map<std::string, std::string> header;
	std::string body;
}HttpResponseContext;

class HttpSession
{
private:
    //解析报文相关成员
    HttpRequestContext httprequestcontext_;
    bool praseresult_;

    //Http响应报文相关成员
    std::string responsecontext_;
    std::string responsebody_;    
    std::string errormsg;
    std::string path_;
    std::string querystring_;

    //长连接标志
    bool keepalive_;
    std::string body_buff;
public:
    //HttpSession(TcpConnection *ptcpconn);
    HttpSession();
    ~HttpSession();

    //解析HTTP报文
    bool PraseHttpRequest(std::string &s, HttpRequestContext &httprequestcontext); 

    //处理报文
    void HttpProcess(const HttpRequestContext &httprequestcontext, std::string &responsecontext); 

    //错误消息报文组装，404等
    void HttpError(const int err_num, const std::string short_msg, const HttpRequestContext &httprequestcontext, std::string &responsecontext);
    
    //判断长连接
    bool KeepAlive() 
    { return keepalive_;}
};

