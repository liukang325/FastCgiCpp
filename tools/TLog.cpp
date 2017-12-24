#include "TLog.h"

#define MAX_MSG     1000

static char szLevelString[L_DEBUG + 1][8] =
{ "None", "Error", "Warn", "Info", "Debug"};


Tool::TLog::TLog()
{

}

Tool::TLog::~TLog()
{

}

void Tool::TLog::initConfig(LogLevel level, std::string type, std::string ip, int port)
{
    m_LogLevel = level;
    m_strType = type;
    m_strIP = ip;
    m_iPort = port;
}

void Tool::TLog::logOut(LogLevel level, const char *file, const char *func, const int line, const char *fmt, ...)
{
    if(level > m_LogLevel)
        return;

    char msg[MAX_MSG]={0};
    if(NULL != fmt)
    {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(msg, sizeof(msg), fmt, ap);
        va_end(ap);
    }
    time_t tnow;
    struct tm *tmnow;
    time(&tnow);
    tmnow = localtime(&tnow);

    //usec
    struct timeval tv;
    if(gettimeofday(&tv,NULL)<0)
        return;

    char message[MAX_MSG + 256]={0};
    sprintf(message, "%4d-%02d-%02d %02d:%02d:%02d.%06d [%-5s]%s:%s():%d  %s\n",
            (1900 + tmnow->tm_year),(1 + tmnow->tm_mon),
            tmnow->tm_mday,tmnow->tm_hour,tmnow->tm_min,tmnow->tm_sec,tv.tv_usec,
            szLevelString[level], file, func, line, msg);

    if("file" == m_strType)
    {
        fileWrite(std::string(message));
    }
    else if("console" == m_strType)
    {
        printf("%s", message);
    }
    else if("tcp" == m_strType)
    {
        tcpWrite(std::string(message));
    }
    else if("udp" == m_strType)
    {
        udpWrite(std::string(message));
    }
}

int Tool::TLog::fileWrite(std::string message)
{

}

int Tool::TLog::tcpWrite(std::string message)
{

}

int Tool::TLog::udpWrite(std::string message)
{

}


#ifdef TEST_MAIN
int main(int args, char* argv[])
{
    TLOG->initConfig(L_INFO, "console");
    DBG(L_INFO, "~~~~test ~~");
    DBG(L_WARN, "~~~~test ~~11");
    return 0;
}
#endif
