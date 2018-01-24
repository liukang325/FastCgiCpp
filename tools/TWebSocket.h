/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TWebSocket.h
/// @brief 封装易用的websocket服务
///
/// 底层实现源码来自于websocketpp
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.10
//////////////////////////////////////////////
#pragma once

#include <string>
#include <functional>

namespace WebTool {

class  TWebSocketServer
{
public:
    TWebSocketServer();
    ~TWebSocketServer();

    void runServer(int port);
    void stopServer();

    void sendMsg(std::string msg);
    void setRecvCB(std::function<void (std::string)> func);

    class TWebSocketServerImpl;
private:
    TWebSocketServerImpl *ptr;

};

class  TWebSocketClient
{
public:
    TWebSocketClient();
    ~TWebSocketClient();

    void connect(std::string uri);
    void disconnect();
    void sendMsg(std::string msg);
    void setRecvCB(std::function<void (std::string)> func);

    class TWebSocketClientImpl;
private:
    TWebSocketClientImpl *ptr;

};

} //namespace WebTool
