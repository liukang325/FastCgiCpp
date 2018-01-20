/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file Params.h
/// @brief 封装http请求的参数类
///
/// 请求参数的两种，一种为json格式；另一种为key1=value1&key2=value2&key3=value3
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.15
//////////////////////////////////////////////
#pragma once

#include <TString.h>
#include <map>

using namespace WebTool;

typedef std::map<TString, TString> ParamsList;

class  Params
{
public:
    /// @paramsStr eg:"key=value&name=pwd" or json
    Params(const TString paramsStr);
    ~Params();

    /// 取得cookie内容
    TString getParams( const TString &name );

    /// 取得cookie内容
    inline TString operator[] ( const TString &name ) {
        return this->getParams( name );
    }

    TString toStr();
private:

    ParamsList m_mapParams;

    /// 是否为json
    bool m_bJson;
};

