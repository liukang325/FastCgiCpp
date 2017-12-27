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

namespace WebTool {

class  TJson
{
public:
    TJson();
    ~TJson();

    std::string getStr(std::string sJson, std::string sKey);
    std::string getObj(std::string sJson, std::string sKey);
    int getInt(std::string sJson, std::string sKey);

    void setStr(std::string sJson, std::string sKey, std::string sValue);
    void setObj(std::string sJson, std::string sKey, std::string sValue);
    void setInt(std::string sJson, std::string sKey, int iValue);

private:

};

} //namespace WebTool


