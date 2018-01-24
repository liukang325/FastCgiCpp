/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file CLogin.h
/// @brief 登录页面
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.10
//////////////////////////////////////////////
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
