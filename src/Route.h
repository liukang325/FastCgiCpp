/*
 * =====================================================================================
 *
 *       Filename:  Route.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时50分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liukang,
 *        Company:
 *
 * =====================================================================================
 */

#include <fcgi_stdio.h>
#include "fcgi_config.h"
#include "TLog.h"
#include <string>
#include <map>
#include <iostream>
#include <functional>


class  Route
{
public:
    Route();
    ~Route();

    void addRoute(std::string requestUri, std::function<void(std::string, std::string)>  func);
    void exec();

private:

    std::map<std::string, std::function<void(std::string, std::string)> > m_routeMap;

};
