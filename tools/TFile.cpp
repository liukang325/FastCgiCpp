#include "TFile.h"
#include<iostream>
#include<fstream>
#include <dirent.h>
#include "TLog.h"
namespace WebTool{
    
 std::vector<std::string> TFile::getFileListFromDir\
        (const std::string& dirPath)
{
    std::vector<std::string> vecString;
    return vecString;

}

 bool TFile::isFile(const std::string& path)
{
    if(path.length() == 0)
    {
        return false;
    }
    std::fstream fs;
    fs.open(path, std::ios::in);
    if(fs)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TFile::isDir(const std::string& path)
{
    if(path.length() == 0)
    {
        return false;
    }
    DIR* dir = opendir(path.c_str());
    if(dir)
    {
        return true;
    }
    else
    {
        return false;
    }
}

}

#ifdef TEST_MAIN
int main(int args, char* argv[])
{
    std::cout << "-------TFile test--------" << std::endl;
    bool isFile = false;
    isFile = WebTool::TFile::isFile("Makefile");
    std::cout << isFile << std::endl;

    bool isDir;
    isDir = WebTool::TFile::isDir("../toolTestBuild"); 
    std::cout << isDir << std::endl;

    return 0;
}
#endif
