#include "TFile.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "TLog.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "TString.h"
#include <stdlib.h>

#define BUFFER_SIZE 102400
namespace WebTool{
    
 std::vector<std::string> TFile::getFileListFromDir\
        (const std::string& dirPath)
{
    std::vector<std::string> vecString;
    DIR*dir = NULL;  
    dirent *ptr = NULL;
    if(!isDir(dirPath))
    {
        std::cout << "dirPath is not dir" << std::endl;
        return vecString;
    }
    dir = opendir(dirPath.c_str());
    if(!dir)
    {
        closedir(dir);
        std::cout << "open dir failed!" << std::endl;
        return vecString;
    }
    for(ptr = readdir(dir);ptr != NULL;ptr = readdir(dir))
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir  
        {
            continue;  
        }
        else
        {
            vecString.push_back(ptr->d_name);
        }
    }
    closedir(dir);
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


bool TFile::createDir(const std::string& path)
{
    if(path.length() == 0)
    {
        return false;
    }
    if(isDir(path))
    {
        std::cout << "This directory already exists!" <<std::endl;
        return false;
    }
    //S_IRWXU 00700权限，代表该文件所有者拥有读，写和执行操作的权限 
    //S_IRUSR(S_IREAD) 00400权限，代表该文件所有者拥有可读的权限 
    //S_IWUSR(S_IWRITE) 00200权限，代表该文件所有者拥有可写的权限 
    //S_IXUSR(S_IEXEC) 00100权限，代表该文件所有者拥有执行的权限 
    //S_IRWXG 00070权限，代表该文件用户组拥有读，写和执行操作的权限 
    //S_IRGRP 00040权限，代表该文件用户组拥有可读的权限 
    //S_IWGRP 00020权限，代表该文件用户组拥有可写的权限 
    //S_IXGRP 00010权限，代表该文件用户组拥有执行的权限 
    //S_IRWXO 00007权限，代表其他用户拥有读，写和执行操作的权限 
    //S_IROTH 00004权限，代表其他用户拥有可读的权限 
    //S_IWOTH 00002权限，代表其他用户拥有可写的权限 
    //S_IXOTH 00001权限，代表其他用户拥有执行的权限
    int isCreate = mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    if(!isCreate)
    {
        std::cout << "createDir succeed:" << path << std::endl;
        return true;
    }
    else
    {
        std::cout << "createDir faiiled!" << std::endl;
        return false;
    }
}

bool TFile::copyFile(const std::string& srcFile,\
            const std::string& dstFile)
{
    if(!isFile(srcFile))
    {
        std::cout << "source file is null!" << std::endl;
        return false;
    }
    FILE *fpR, *fpW;  
    char buffer[BUFFER_SIZE];  
    int lenR, lenW;  
    if ((fpR = fopen(srcFile.c_str(), "r")) == NULL)  
    {  
        std::cout << "src file cannot open!" << std::endl;  
        return false;  
    }  
    if ((fpW = fopen(dstFile.c_str(), "w")) == NULL)  
    {
        std::cout << "dsr file cannot open!" << std::endl;  
        fclose(fpR);  
        return false;  
    }  

    memset(buffer, 0, BUFFER_SIZE);  
    while ((lenR = fread(buffer, 1, BUFFER_SIZE, fpR)) > 0)  
    {  
        if ((lenW = fwrite(buffer, 1, lenR, fpW)) != lenR)  
        {  
            fclose(fpR);  
            fclose(fpW);
            return false;  
        }  
        memset(buffer, 0, BUFFER_SIZE);  
    }  
        
    fclose(fpR);  
    fclose(fpW); 
    return true; 
}

bool TFile::copyDir(const std::string& srcDir,\
            const std::string& dstDir, const bool& isCover)
{
    if(!isDir(srcDir))
    {
        std::cout << "src dir is not a dir!" << std::endl;
        return false;
    }
    if(!isDir(dstDir))
    {
        std::cout << "dst dir is not a dir!" << std::endl;
        return false;
    }
    
    std::string sysStr = "cp " + srcDir + " " + dstDir + " -a";
    std::cout << sysStr << std::endl;
    return system(sysStr.c_str());
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

    std::vector<std::string> vecFile;
    vecFile = WebTool::TFile::getFileListFromDir("../toolTestBuild");
    for(auto fileName : vecFile)
    {
        std::cout << fileName << std::endl;
    }

    std::cout << WebTool::TFile::createDir("/home/tu/test") << std::endl;
   
    std::cout << WebTool::TFile::copyFile("/home/tu/test/srcTest", \
            "/home/tu/test/dstTest") << std::endl;

    std::cout << WebTool::TFile::copyDir("/home/tu/test", \
            "/home/tu/testDir", false) << std::endl; 
    return 0;
}
#endif
