#include "Route.h"
#include "memory.h"

Route::Route()
{

}

Route::~Route()
{

}

void Route::addRoute(std::string requestUri, FuncHttp func)
{
    m_routeMap.insert(std::map<std::string , FuncHttp>::value_type(requestUri, func));
}

void Route::exec()
{
    while(FCGI_Accept() >= 0)
    {
        //"GET" or "POST"
        std::string requestMethod =  std::string(getenv("REQUEST_METHOD"));
        //"/login?key=value&name=pwd"
        std::string requestUri = std::string(getenv("REQUEST_URI"));
        size_t pos = requestUri.find_first_of("?");
        std::string requestRoute = requestUri.substr(0, pos);
        std::string requestParam;
        if("GET" == requestMethod)
        {
            requestParam = requestUri.substr(pos + 1);
        }
        else if("POST" == requestMethod)
        {
            int ilen = atoi(getenv("CONTENT_LENGTH")) + 1;
            char *bufpost = (char* )malloc(ilen);
            memset(bufpost, 0, ilen);
            FCGI_fread(bufpost, ilen, 1, FCGI_stdin);
            requestParam = std::string(bufpost);
            free(bufpost);
        }

        DBG(L_INFO, "requestRoute: %s, requestParam: %s ", requestRoute.c_str(), requestParam.c_str());

        std::map<std::string , FuncHttp>::iterator iterMap;;
        iterMap = m_routeMap.find(requestRoute);
        if(iterMap == m_routeMap.end())
        {
            DBG(L_ERROR, "not find route: %s ", requestUri.c_str());
        }
        else
        {
            FuncHttp func = iterMap->second;
            func(requestMethod, requestRoute, requestParam);
        }
    }

}

void Route::reponse(const char*fmt, ...)
{
    char msg[10240]={0};
    if(NULL != fmt)
    {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(msg, sizeof(msg), fmt, ap);
        va_end(ap);
    }
    FCGI_printf("Content-type: text/html\r\n\r\n%s", msg);
}
