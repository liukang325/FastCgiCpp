/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file main.h
/// @brief 一些全局包含的头文件及配置宏
///
/// @version 1.0
/// @author liukang
/// @date 2017.12.15
//////////////////////////////////////////////
#pragma once

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "route/Route.h"
#include "route/Cookie.h"
#include "route/Params.h"

#include "apps/CIndex.h"
#include "apps/CLogin.h"
#include "apps/CArticle.h"

#include "TEncode.h"
#include "TConf.h"
static TConf gConf("fcgi.conf");

#define HTML_PATH   "/home/liukang/workspace/FastCgiCpp/html/example/"

#define SESSION_PWD "abcdefgliukanghahatest"
#define TEST_USER   "liukang"
#define TEST_PWD    "325"


