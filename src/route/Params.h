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

/// 键值对类型
typedef std::map<TString, TString> ParamsList;

class  Params
{
public:
    /// @param paramsStr eg:"key=value&name=pwd" or json
    Params(const TString paramsStr);
    ~Params();

    /// @brief  获取cookie中的key对应的字符串类型value
    /// @param  name cookie中的key
    /// @return 返回key对应的字符串类型value
    TString getParams( const TString &name );

    /// @brief  获取cookie中的key对应的字符串类型value
    /// @see getParams
    inline TString operator[] ( const TString &name ) {
        return this->getParams( name );
    }

    /// @brief  将Params类型的转换为字符串
    /// @return 返回字符串eg:"key=value&name=pwd"
    TString toStr();
private:

    /// 用map保存的参数键值对
    ParamsList m_mapParams;

    /// 是否为json
    bool m_bJson;
};

