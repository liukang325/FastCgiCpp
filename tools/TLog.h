/*
 * =====================================================================================
 *
 *       Filename:  TLog.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时24分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

#pragma once

#include <string>
#include <stdarg.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <sys/time.h>
#include    <sys/types.h>

namespace Tool {

typedef enum
{
    L_NONE=0,
    L_ERROR=1,
    L_WARN=2,
    L_INFO=3,
    L_DEBUG=4
} LogLevel;

class  TLog
{
public:
    ///////////////////////////////////////////////////////////////
    /// 初始化log
    /// @param level 设置整体log输出级别
    /// @param type 输出的方式：file/console/tcp/udp
    /// @param IP network输出目标IP地址
    /// @param port network输出目标的监听端口
    ///////////////////////////////////////////////////////////////
    TLog(std::string level, std::string type, std::string ip = "", int port = 0);
    ~TLog();

    static void logOut(LogLevel level, const char *file, const char *func, const int line, const char*fmt, ...);

private:
    LogLevel analyLogLevel(std::string level);

private:
    LogLevel m_LogLevel;
    std::string m_strType;
    std::string m_strIP;
    int m_iPort;
};

} //namespace Tool

#define gseLog(level,fmt,...)   Tool::TLog::logOut(level,__FILE__,__FUNCTION__,__LINE__,fmt"",##__VA_ARGS__)

