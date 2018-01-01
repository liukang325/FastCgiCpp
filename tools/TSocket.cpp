#include "TSocket.h"
#include "TLog.h"

namespace WebTool {

TSocket::TSocket():
    m_fd(0)
{

}

TSocket::~TSocket()
{
    if(m_fd > 0)
        close(m_fd);
    m_fd = 0;
}

TTcpSocket::TTcpSocket()
{

}

TTcpSocket::~TTcpSocket()
{

}

int TTcpSocket::connectServer(std::string ip, int port)
{
    struct sockaddr_in serv_addr;
    struct hostent *host;
    if(0 == ip.length() || 1 > port)
    {
//        DBG(L_ERROR, "can't connect server,IP or Port error!!");
        return -1;
    }
    if (NULL == (host = gethostbyname(ip.c_str())))
    {
//        DBG(L_ERROR, "gethostbyname error!");
        return -2;
    }
    if (-1 == (m_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
//        DBG(L_ERROR, "socket create failed!");
        return -3;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr = *((struct in_addr *) host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);
    if (-1 == connect(m_fd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)))
    {
        if(m_fd > 0)
            close(m_fd);
//        DBG(L_ERROR, "connect [%s, %d ] error!", ip.c_str(), port);
        return -4;
    }
    return 0;
}

int TTcpSocket::sendData(std::string data)
{
    int sendLen = -1;
    if (1 > m_fd || 1 > data.length())
        return -1;
    sendLen = send(m_fd, data.c_str(), data.length(), 0);
    if (-1 == sendLen)
    {
//        DBG(L_ERROR, "send error!");
        return -2;
    }
    return sendLen;
}

int TTcpSocket::recvData(std::string data)
{

}

TUdpSocket::TUdpSocket()
{

}

TUdpSocket::~TUdpSocket()
{

}

int TUdpSocket::connectServer(std::string ip, int port)
{
    if(0 == ip.length() || 1 > port)
    {
//        DBG(L_DEBUG,"can't connect server!");
        return -1;
    }
    if (-1 == (m_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        return -2;
    }
    m_udpAddr.sin_family=AF_INET;
    m_udpAddr.sin_port=htons(port);
    m_udpAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    bzero(&(m_udpAddr.sin_zero),8);
    bool bBroadcast = true;
    setsockopt(m_fd, SOL_SOCKET, SO_BROADCAST, (const char *)&bBroadcast, sizeof(bool));
    bool loop = false;
    setsockopt(m_fd, IPPROTO_IP, IP_MULTICAST_LOOP, (const char *)&loop, sizeof(bool));
}

int TUdpSocket::sendData(std::string data)
{
    int len,sendLen;
    len = sizeof(struct sockaddr_in);
    sendLen = sendto(m_fd, data.c_str(), data.length(), 0, (struct sockaddr *) &(m_udpAddr), len);
    if (sendLen < 0)
    {
//        DBG(L_ERROR,"UDP send error:");
        return -1;
    }
    else
    {
//        DBG(L_DEBUG,"UDP send sucessful:%s\n", data.c_str());
    }
    return sendLen;
}

int TUdpSocket::recvData(std::string data)
{

}


} //namespace WebTool

