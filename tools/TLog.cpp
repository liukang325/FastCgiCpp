#include "TLog.h"

Tool::TLog::TLog(std::string level, std::string type, std::string ip, int port)
{
    m_LogLevel = analyLogLevel(level);
    m_strType = type;
    m_strIP = ip;
    m_iPort = port;
}

void Tool::TLog::logOut(Tool::LogLevel level, const char *file, const char *func, const int line, const char *fmt, ...)
{
    return;
}

Tool::LogLevel Tool::TLog::analyLogLevel(std::string level)
{
    Tool::LogLevel tempLevel = L_NONE;
    if("none" == level)
    {
        tempLevel = L_NONE;
    }
    else if("error" == level)
    {
        tempLevel = L_ERROR;
    }
    else if("warn" == level)
    {
        tempLevel = L_WARN;
    }
    else if( "info" == level)
    {
        tempLevel = L_INFO;
    }
    else if("debug" == level)
    {
        tempLevel = L_DEBUG;
    }
    return tempLevel;
}



#ifdef TEST_MAIN
int main(int args, char* argv[])
{

    return 0;
}
#endif
