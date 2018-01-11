/*
 * =====================================================================================
 *
 *       Filename:  TEncode.h
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

class  TEncode
{
public:
    TEncode();
    ~TEncode();

    static std::string uriEncode(const std::string source);
    static std::string uriDecode(const std::string source);

    static std::string base64Encode(const std::string source);
    static std::string base64Decode(const std::string source);

    static std::string md5Decode(const std::string source);

private:
    /// HEX字符转换为ASC字符
    static char hexToAsc( const std::string src );
private:


};

} //namespace WebTool

