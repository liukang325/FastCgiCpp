/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TJson.h
/// @brief 封装易用的json数据处理类
///
/// 底层实现源码来自于jsoncpp
///
/// @version 1.0
/// @author liukang
/// @date 2017.12.15
//////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>

namespace WebTool {

class  TJson
{
public:

    /// @brief  获取传入的json是不是有效
    /// @param  obj 字符串json
    /// @return true 有效；false无效
    static bool isValid(const std::string &obj);

    /// @brief  获取json中的key对应的字符串类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @return 返回key对应的字符串类型
    static std::string getStr(const std::string &obj, const std::string &sKey);
    /// @brief  获取json中的key对应的json类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @return 返回key对应的json类型
    static std::string getObj(const std::string &obj, const std::string &sKey);
    /// @brief  获取json中的key对应的int类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @return 返回key对应的int类型
    static int getInt(const std::string &obj,  const std::string &sKey);
    /// @brief  获取json中的key对应的数组类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @return 返回key对应的数组类型，用vector保存返回
    static std::vector<std::string> getArray(const std::string &obj, const std::string &sKey);

    /// @brief  设置json中的key对应的字符串类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @param  sValue key对应的字符串类型
    static void setStr(std::string &obj, const std::string &sKey,const std::string &sValue);
    /// @brief  设置json中的key对应的json类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @param  sValue key对应的json类型
    static void setObj(std::string &obj, const std::string &sKey,const std::string &sValue);
    /// @brief  设置json中的key对应的int类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @param  iValue key对应的int类型
    static void setInt(std::string &obj, const std::string &sKey,const int &iValue);
    /// @brief  设置json中的key对应的数组类型value
    /// @param  obj 字符串json
    /// @param  sKey 字符串key
    /// @param  array key对应的数组类型
    static void setArray(std::string& obj, const std::string &sKey, const std::vector<std::string> &array);

};

} //namespace WebTool


