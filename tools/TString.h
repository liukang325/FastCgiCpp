/*
 * =====================================================================================
 *
 *       Filename:  TString.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时24分24秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

#pragma once

#include <string>
#include <vector>

namespace WebTool {

class  TString : public std::string
{
public:
    /// 默认构造函数
    TString();
    /// 参数为char*的构造函数
    TString(const char *s);
    /// 参数为string的构造函数
    TString(const std::string &s);

    virtual ~TString();

    /// 从左边截取指定长度子串
    TString left(const std::string::size_type n) const;
    /// 从中间截取指定长度子串
    TString mid(const std::string::size_type pos,
        const std::string::size_type n = npos) const;
    /// 从右边截取指定长度子串
    TString right(const std::string::size_type n) const;

    /// 根据分割符分割字符串
    std::vector<TString> split( const std::string &tag) const;

    int toInt() const;

    bool sprintf( const char *format, ... );

    /// 替换
    int replace(const std::string &oldstr, const std::string &newstr);
    /// 全文替换
    int replaceAll(const std::string &oldstr, const std::string &newstr);

    /// 转换为大写字母
    void toUpper();
    /// 转换为小写字母
    void toLower();

    /// 读取文件到字符串
    bool loadFile( const std::string &filename );

};

} //namespace WebTool
