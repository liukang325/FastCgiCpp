/*
 * =====================================================================================
 *
 *       Filename:  CLogin.h
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

#include "Route.h"

class  CLogin
{
public:
    CLogin();
    ~CLogin();

    void login(std::string method, std::string url, std::string params);

    void regist(std::string method, std::string url, std::string params);

private:

};
