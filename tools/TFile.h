/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TFile.h
/// @brief 文件处理
///
/// 主要有等
///
/// @version 1.0
/// @author liukang
/// @date 2018.01.31
//////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>

namespace WebTool{

class TFile
{
public:
    TFile() = default;
    ~TFile() = default;

    static std::vector<std::string> getFileListFromDir\
        (const std::string& dirPath);
    
    static bool isFile(const std::string& path);

    static bool isDir(const std::string& path);

    static bool createDir(const std::string& path);

    static bool copyFile(const std::string& srcFile,\
            const std::string& dstFile);

    static bool copyDir(const std::string& srcDir,\
            const std::string& dstDir, const bool& isCover);
};
}   //namespace WebTool
