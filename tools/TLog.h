/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TLog.h
/// @brief 打印调试类
///
/// log输出有console,file,tcp,udp 多种形式
///
/// @version 1.0
/// @author liukang
/// @date 2017.12.15
//////////////////////////////////////////////
#pragma once

#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>

#include "TSocket.h"

typedef enum
{
    L_NONE=0,
    L_ERROR=1,
    L_WARN=2,
    L_INFO=3,
    L_DEBUG=4
} LogLevel;


namespace WebTool {

class  TLog
{
public:

    TLog();
    ~TLog();

    ///////////////////////////////////////////////////////////////
    /// 初始化log
    /// @param level 设置整体log输出级别
    /// @param type 输出的方式：file/console/tcp/udp
    /// @param IP network输出目标IP地址
    /// @param port network输出目标的监听端口
    ///////////////////////////////////////////////////////////////
    void initConfig(LogLevel level, std::string type, std::string fileName = "tool.log", std::string ip = "", int port = 0);

    void logOut(LogLevel level, const char *file, const char *func, const int line, const char*fmt, ...);

private:
    int fileWrite(std::string message);

private:
    LogLevel m_LogLevel;
    std::string m_strType;
    std::string m_strIP;
    int m_iPort;

    pthread_mutex_t m_fdMutex;
    FILE *m_fp;
    TTcpSocket m_tcpSocket;
    TUdpSocket m_udpSocket;
};

} //namespace WebTool

#include "Singleton.h"
/// 定义单例类 ConfigDataSingle
typedef Singleton<WebTool::TLog> TLogSingle;
#define TLOG  TLogSingle::Instance()

#define DBG(level,fmt,...)   TLOG->logOut(level,__FILE__,__FUNCTION__,__LINE__,fmt"",##__VA_ARGS__)

#define CDBG    std::cout << "\n[CDBG] " << __FILE__ << " " << __FUNCTION__ << "():"<< __LINE__ << " "

