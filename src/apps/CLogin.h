/*
 * =====================================================================================
 *
 *       Filename:  CLogin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018年01月14日 13时29分14秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  liukang,
 *        Company:
 *
 * =====================================================================================
 */
#pragma once

#include "../route/Route.h"

class  CLogin
{
public:
    CLogin();
    ~CLogin();

    Response login(Request req);

    Response regist(Request req);

private:

};
