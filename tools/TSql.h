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

#include "ToolGlobal.h"

#include <vector>
//sudo apt-get install libmysqlclient-dev
//in /usr/include/mysql/mysql.h
#include <mysql.h>
#include <my_global.h>
#include <stdlib.h>

//sudo apt-get install libsqlite3-dev
//in /usr/include/sqlite3.h
#include <sqlite3.h>

namespace WebTool {

/// 错误码
enum  
{  
    MYSQL_SUCCESS       = 0,    /// 成功
    MYSQL_E_DBINIT      = 1,    /// 数据库初始化失败
    MYSQL_E_CONNECT     = 2,    /// 数据库连接失败
    MYSQL_E_QUERY       = 3,    /// 执行查询语句失败
    MYSQL_E_RESULT      = 4,    /// 获取结果集出错
    MYSQL_E_PARAM       = 5,    /// 参数错误
    MYSQL_E_MEMALLOC    = 6,    /// 内存分配失败
};  


class TSqlData{

    friend class TSqlite;
    friend class TMySql;
    T_DISABLE_COPY(TSqlData)

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

    std::vector< KeyValue > m_vecKeyValueData;
    std::vector< ColValue > m_vecColValueData;

    int m_row = 0;
    int m_col = 0;

};

class  TMysql
{
    T_DISABLE_COPY(TMysql)
public:
    ///@param   sIp          [in] - 主机地址
    ///@param   uiPort       [in] - 端口号
    ///@param   strUsername  [in] - 用户名
    ///@param   strPassword  [in] - 密码
    ///@param   strDatabase  [in] - 数据库
    TMysql(const std::string sIp,
           unsigned short uiPort,
           const std::string sUserName,
           const std::string sPassword,
           const std::string sDatabase);
    ~TMysql();

    ///@brief   连接数据库服务器 
    ///@return  错误码 
    int openDB();

    /// @brief  关闭连接 
    void closeDB();

    /// @brief  执行SQL语句,取得查询结果
    /// @param  sSqlStr     执行的sql语句
    /// @return 是否成功 
    int execSQL(const std::string sSqlStr);

    /// @brief  执行SQL语句,取得查询结果
    /// @param  sSqlStr     执行的sql语句
    /// @param  sqlData     储存sql语句的结果
    /// @return 是否成功 
    int execSQL(const std::string sSqlStr,TSqlData &sqlData);

private:
    /// mysql 句柄
    MYSQL* m_pMySql = NULL;

    std::string m_sIp;
    unsigned short m_uiPort;
    std::string m_sUserName;
    std::string m_sPassword;
    std::string m_sDatabase;
};

class TSqlite
{
    T_DISABLE_COPY(TSqlite)
public:
    /// @param  dbFilePath     数据库文件路径
    TSqlite(std::string dbFilePath);
    ~TSqlite();

    ///@brief   打开数据库
    ///@return  错误码
    int openDB();

    /// @brief  关闭数据库
    /// @return  错误码
    int closeDB();

    /// @brief  执行SQL语句,取得查询结果
    /// @param  sSqlStr     执行的sql语句
    /// @return 是否成功
    int execSQL(std::string sql);

    /// @brief  执行SQL语句,取得查询结果
    /// @param  sSqlStr     执行的sql语句
    /// @param  sqlData     储存sql语句的结果
    /// @return 是否成功
    int execSQL(std::string sql, TSqlData &retSqlData);

private:
    sqlite3* m_db;

    std::string m_filePath;
};

} //namespace WebTool
