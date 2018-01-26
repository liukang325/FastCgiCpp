/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TEncode.h
/// @brief 数据加密解密处理
///
/// 主要有uri, base64, md5等
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.08
//////////////////////////////////////////////
#pragma once

#include <string>

namespace WebTool {

class  TEncode
{
public:
    static std::string uriEncode(const std::string &source);
    static std::string uriDecode(const std::string &source);

    static std::string base64Encode(const std::string &source);
    static std::string base64Decode(const std::string &source);

    static std::string md5Decode(const std::string &source);

private:
    /// HEX字符转换为ASC字符
    static char hexToAsc(const std::string &src);

};

} //namespace WebTool

