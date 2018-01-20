/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TSql.h
/// @brief 封装易用的SQL数据库处理类
///
/// 支持mysql和sqlite两种数据库
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.15
//////////////////////////////////////////////
#pragma once

#include <string>


//sudo apt-get install libmysqlclient-dev
//in /usr/include/mysql/mysql.h
#include <mysql.h>
#include <my_global.h>

//sudo apt-get install libsqlite3-dev
//in /usr/include/sqlite3.h
#include <sqlite3.h>

namespace WebTool {

class  TSql
{
public:
    TSql();
    ~TSql();


};

class  TMysql : public TSql
{
public:
    TMysql();
    ~TMysql();


};

class  TSqlite: public TSql
{
public:
    TSqlite();
    ~TSqlite();
};

} //namespace WebTool
