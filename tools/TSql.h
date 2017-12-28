
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
