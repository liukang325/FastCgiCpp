/*
 * =====================================================================================
 *
 *       Filename:  TSql.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018年01月14日 21时30分28秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

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
