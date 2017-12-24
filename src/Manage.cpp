/*
 * =====================================================================================
 *
 *       Filename:  Manage.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时50分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Manage.h"

Manage::Manage(HttpInfo httpInfo):
    m_httpInfo(httpInfo)
{

}


Manage::~Manage()
{

}

std::string Manage::response()
{
    if("GET" == m_httpInfo.requestMethod)
    {
        return "get haha";
    }
    else if("POST" == m_httpInfo.requestMethod)
    {
        return "post haha";
    }

}
