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
#include <vector>
#include <map>

//sudo apt-get install libmysqlclient-dev
//in /usr/include/mysql/mysql.h
#include <mysql.h>
#include <my_global.h>
#include <stdlib.h>

//sudo apt-get install libsqlite3-dev
//in /usr/include/sqlite3.h
#include <sqlite3.h>


namespace WebTool {

// 错误码  
enum  
{  
    MYSQL_SUCCESS       = 0,    // 成功  
    MYSQL_E_DBINIT      = 1,    // 数据库初始化失败  
    MYSQL_E_CONNECT     = 2,    // 数据库连接失败  
    MYSQL_E_QUERY       = 3,    // 执行查询语句失败  
    MYSQL_E_RESULT      = 4,    // 获取结果集出错  
    MYSQL_E_PARAM       = 5,    // 参数错误  
    MYSQL_E_MEMALLOC    = 6,    // 内存分配失败  
};  

class  TSql
{
public:
    TSql() = default;
    ~TSql() = default;


};

class  TMysql : public TSql
{
public:
    TMysql();
    ~TMysql();

    /*
    *  @brief   连接数据库服务器 
    *  @param   strHost      [in] - 主机地址 
    *           nPort        [in] - 端口号 
    *           strUsername  [in] - 用户名 
    *           strPassword  [in] - 密码 
    *           strDatabase  [in] - 数据库 
    *  @return  错误码 
    **/
int connectMySql(const std::string sIp,
                 unsigned short uiPort,
                 const std::string sUserName,
                 const std::string sPassword,
                 const std::string sDatabase);


private:
    MYSQL* m_pMySql = NULL; // mysql 句柄
};

class TSqlData{

    friend class TSqlite;

public:
    TSqlData();
    ~TSqlData();

    typedef std::map< std::string, std::string > KeyValue;
    typedef std::map< int, std::string> ColValue;

    void addRowData(TSqlData::KeyValue sigKeyValueData, TSqlData::ColValue sigColValueData);
    int getRow();

    int getCol();

    std::string getData(int row, std::string key);
    std::string getData(int row, int col);
private:

    /// 禁止调用拷贝构造函数
    TSqlData( TSqlData &copy );
    /// 禁止调用拷贝赋值操作
    TSqlData& operator = ( const TSqlData& copy );

    std::vector< KeyValue > m_vecKeyValueData;
    std::vector< ColValue > m_vecColValueData;

    int m_row = 0;
    int m_col = 0;

};

class TSqlite: public TSql
{
public:
    TSqlite(std::string dbFilePath);
    ~TSqlite();

    int openDB();
    int closeDB();

    int execSQL(std::string sql);
    int execSQL(std::string sql, TSqlData &retSqlData);

private:
    sqlite3* m_db;

    std::string m_filePath;
};

} //namespace WebTool
