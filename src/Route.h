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
#include <pthread.h>

using namespace WebTool;

#define routeBind(funcName, appName) std::bind(&funcName, &appName, std::placeholders::_1)

typedef std::function<Response(Request)> FuncHttp;

class Route;

struct threadStruct{
    Route* pthis;
    int threadID;
};

class  Route
{
public:
    Route(int threadNum = 1);
    ~Route();

    void addRoute(TString requestRoute, FuncHttp  func);
    void exec();

private:

    //处理消息的线程函数
    static inline void *pthreadTask(void *p)
    {
        threadStruct* data = (threadStruct*)p;
        (static_cast<Route*>(data->pthis))->processMessage(data->threadID);
        return NULL;
    }
    void processMessage(int threadID);

private:

    std::map<TString, FuncHttp > m_routeMap;

    int m_iThreadNum;
};
