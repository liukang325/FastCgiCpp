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

class  TConf
{
public:
    TConf(std::string configName);
    ~TConf();

    std::string getConfStr(std::string group, std::string key);
    void setConfStr(std::string group, std::string key, std::string value);

private:
    std::string m_configName;
};

} //namespace WebTool


