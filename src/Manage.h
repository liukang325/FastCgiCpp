/*
 * =====================================================================================
 *
 *       Filename:  Manage.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时50分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <string>

struct HttpInfo{
    std::string requestMethod;
    std::string requestURI;
    std::string queryStr;
};

class  Manage
{
public:
    Manage(HttpInfo httpInfo);
    ~Manage();

    std::string response();

private:

    HttpInfo m_httpInfo;

};
