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
#pragma once

#include "Request.h"
#include <map>
#include <vector>
#include <iostream>
#include <functional>

using namespace WebTool;

#define routeBind(funcName, appName) std::bind(&funcName, &appName, \
    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

#define FunParams   TString method, TString url, TString params

typedef std::function<void(TString, TString, TString)> FuncHttp;

class  Route
{
public:
    Route();
    ~Route();

    void addRoute(TString requestRoute, FuncHttp  func);
    void exec();

private:

    std::map<TString, FuncHttp > m_routeMap;

};
