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

namespace WebTool {

class  TWebSocketServer
{
public:
    TWebSocketServer();
    ~TWebSocketServer();

    void runServer(int port);
private:

    class TWebSocketServerImpl;
    TWebSocketServerImpl *ptr;

};

} //namespace WebTool
