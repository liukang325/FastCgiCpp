/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file ToolGlobal.h
/// @brief 全局包含头文件
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.26
//////////////////////////////////////////////

#pragma once


/// 禁止调用拷贝构造函数
/// 禁止调用拷贝赋值操作
#define T_DISABLE_COPY(Class)\
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;


#include "Singleton.h"
#include "TConf.h"
#include "TSocket.h"
#include "TLog.h"
#include "TString.h"
#include "TJson.h"
#include "TEncode.h"
#include "TDateTime.h"
#include "TWebSocket.h"
#include "TSql.h"
