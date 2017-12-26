#include "Route.h"

Route::Route()
{

}


Route::~Route()
{

}

void Route::addRoute(std::string requestUri, std::function<void (std::string, std::string)> func)
{
    m_routeMap.insert(std::map<std::string , std::function<void (std::string, std::string)>>::value_type(requestUri, func));
}


void Route::exec()
{
    while(FCGI_Accept() >= 0)
    {
        std::string requestMethod =  std::string(getenv("REQUEST_METHOD"));
        std::string requestUri = std::string(getenv("REQUEST_URI"));

        std::map<std::string , std::function<void (std::string, std::string)>>::iterator iterMap;;
        iterMap = m_routeMap.find(requestUri);
        if(iterMap == m_routeMap.end())
        {
            DBG(L_INFO, "not find %s ", requestUri.c_str());
        }
        else
        {
            std::function<void (std::string, std::string)> func = iterMap->second;
            func(requestMethod, requestUri);
        }
    }

}
