/*
 * =====================================================================================
 *
 *       Filename:  TConf.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时24分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

#pragma once

#include <string>
#include "Json/include/json.h"

namespace WebTool {

class  TJson
{
public:
    TJson(std::string sJson);
    ~TJson();

    bool isValid();

    std::string getStr(const std::string sKey);
    std::string getObj(const std::string sKey);
    int getInt(const std::string sKey);

    void setStr(const std::string sKey, std::string sValue);
    void setObj(const std::string sKey, std::string sValue);
    void setInt(const std::string sKey, int iValue);

private:

    std::string m_sJson;

    Json::Reader m_reader;
    Json::Value m_root;
    bool m_bValid;

};

} //namespace WebTool


