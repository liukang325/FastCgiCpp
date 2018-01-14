/*
 * =====================================================================================
 *
 *       Filename:  TSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时24分24秒
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
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

namespace WebTool {

class TSocket
{
public:
    TSocket();
    virtual ~TSocket();

    virtual int connectServer(std::string ip, int port) = 0;
    virtual int sendData(std::string data) = 0;
    virtual int recvData(std::string data) = 0;

protected:
    int m_fd;
};

class TTcpSocket : public TSocket
{
public:
    TTcpSocket();
    ~TTcpSocket();

    int connectServer(std::string ip, int port);

    int sendData(std::string data);

    int recvData(std::string data);
};

class TUdpSocket : public TSocket
{
public:
    TUdpSocket();
    ~TUdpSocket();

    int connectServer(std::string ip, int port);

    int sendData(std::string data);

    int recvData(std::string data);

private:
    ///<使用UDP传输时的地址
    struct sockaddr_in m_udpAddr;
};

} //namespace WebTool
