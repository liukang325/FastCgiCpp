/*
 * =====================================================================================
 *
 *       Filename:  TDateTime.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018年01月14日 21时55分58秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

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

} //namespace WebTool
