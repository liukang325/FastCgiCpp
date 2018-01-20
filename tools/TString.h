/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TString.h
/// @brief 封装易用的string类
///
/// 继承于std::string
///
/// @version 1.0
/// @author liukang
/// @date 2017.12.15
//////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>

namespace WebTool {

/// 本类的功能：封装易用的字符串操作类
class  TString : public std::string
{
public:
    /// @note 默认构造函数
    TString();

    /// @param s char*类型的字符串
    /// @note 参数为char*的构造函数
    TString(const char *s);

    /// @param s std::string类型字符串
    /// @note 参数为string的构造函数
    TString(const std::string &s);

    virtual ~TString();

    /// @brief  从左边截取指定长度子串
    /// @param  n 左边截取的长度
    /// @return 返回从左边截取后的字符串
    TString left(const std::string::size_type n) const;

    /// @brief  从中间截取指定长度子串
    /// @param  pos 截取的字符串起点位置
    /// @param  n 截取的字符串终点位置，默认为结尾位置
    /// @return 返回从中间截取后的字符串
    TString mid(const std::string::size_type pos,
        const std::string::size_type n = npos) const;

    /// 从右边截取指定长度子串
    /// @brief  从右边截取指定长度子串
    /// @param  n 右边截取的长度
    /// @return 返回从右边截取后的字符串
    TString right(const std::string::size_type n) const;

    /// @brief  根据分割符分割字符串
    /// @param  tag 分割符
    /// @return 返回分割后的字符串数组
    std::vector<TString> split( const std::string &tag) const;

    /// @brief  字符串变为int型
    /// @return 返回int型数字
    int toInt() const;

    /// @brief  格式化输出到字符串
    /// @return 返回处理后的字符串
    bool sprintf( const char *format, ... );

    /// @brief  替换指定字符串
    /// @param  oldstr 替换前的字符串
    /// @param  newstr 替换后的字符串
    /// @return 成功替换返回1，未替换返回0
    int replace(const std::string &oldstr, const std::string &newstr);

    /// @brief  全文替换指定字符串
    /// @param  oldstr 替换前的字符串
    /// @param  newstr 替换后的字符串
    /// @return 返回替换的个数
    int replaceAll(const std::string &oldstr, const std::string &newstr);

    /// @brief  转换为大写字母
    void toUpper();

    /// @brief  转换为小写字母
    void toLower();

    /// @brief  读取文件到字符串
    /// @param  filename 读取的文件名
    /// @return 返回是否成功
    bool loadFile( const std::string &filename );

};

} //namespace WebTool
