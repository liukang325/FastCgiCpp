#include "TLog.h"

namespace WebTool {

#define MAX_MSG     10000

static char szLevelString[L_DEBUG + 1][8] =
{ "None", "Error", "Warn", "Info", "Debug"};


TLog::TLog():
    m_LogLevel(L_NONE),
    m_strType(""),
    m_strIP(""),
    m_iPort(0),
    m_fp(NULL)
{
    pthread_mutex_init(&m_fdMutex, NULL);
}

TLog::~TLog()
{
    if (NULL != m_fp)
    {
        fclose(m_fp);
    }
    pthread_mutex_destroy(&m_fdMutex);
}

void TLog::initConfig(LogLevel level, std::string type, std::string fileName, std::string ip, int port)
{
    m_LogLevel = level;
    m_strType = type;
    m_strIP = ip;
    m_iPort = port;
    if("file" == m_strType && fileName.length() > 0)
    {
        m_fp = fopen(fileName.c_str(), "a+");
    }
    else if("tcp" == m_strType && m_strIP.length() > 0 && m_iPort > 0)
    {
        int ret = m_tcpSocket.connectServer(m_strIP, m_iPort);
        std::cout << "connectTcpServer ret = " << ret << std::endl;
//        DBG(L_INFO, "connectTcpServer ret = %d", ret);
    }
    else if("udp" == m_strType  && m_strIP.length() > 0 && m_iPort > 0)
    {
        int ret = m_udpSocket.connectServer(m_strIP, m_iPort);
//        DBG(L_INFO, "connectUdpServer ret = %d", ret);
    }

}

void TLog::logOut(LogLevel level, const char *file, const char *func, const int line, const char *fmt, ...)
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
        if (NULL != m_fp)
        {
            pthread_mutex_lock(&m_fdMutex);
            fwrite(message, strlen(message), 1, m_fp);
            fflush(m_fp);
            pthread_mutex_unlock(&m_fdMutex);
        }
    }
    else if("console" == m_strType)
    {
        printf("%s", message);
    }
    else if("tcp" == m_strType)
    {
        m_tcpSocket.sendData(std::string(message));
    }
    else if("udp" == m_strType)
    {
        m_udpSocket.sendData(std::string(message));
    }
}

} //namespace WebTool

#ifdef TEST_MAIN
int main(int args, char* argv[])
{
    TLOG->initConfig(L_INFO, "file");
    DBG(L_INFO, "~~~~test ~~");
    DBG(L_WARN, "~~~~test ~~11");
    return 0;
}
#endif
