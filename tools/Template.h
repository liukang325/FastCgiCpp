/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file Template.h
/// @brief
///
/// @version 1.0
/// @author liukang
/// @date 2017.12.15
//////////////////////////////////////////////
#pragma once

#include "TString.h"
#include <map>

namespace WebTool {

/// 本类的功能：封装易用的字符串操作类
class  Template
{
public:

    /// @param s std::string类型字符串
    /// @note 参数为string的构造函数
    Template(const TString &filePath);

    virtual ~Template();

    void set(const TString &name, TString value);

    TString toStr();

private:
    TString m_strText;

    std::map<TString,TString> m_mapNameValue;
};

} //namespace WebTool
