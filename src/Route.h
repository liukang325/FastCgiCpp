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
#include <vector>
#include <iostream>
#include <functional>

typedef std::function<void(std::string, std::string, std::string)> FuncHttp;
class  Route
{
public:
    Route();
    ~Route();

    void addRoute(std::string requestUri, FuncHttp  func);
    void exec();

    static void reponse(const char*fmt, ...);

private:

    std::map<std::string, FuncHttp > m_routeMap;

};
