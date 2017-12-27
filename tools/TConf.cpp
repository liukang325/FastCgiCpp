/*
 * =====================================================================================
 *
 *       Filename:  TConf.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时24分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TConf.h"

namespace WebTool {

TConf::TConf(std::string configName):
    m_configName(configName)
{

}

TConf::~TConf()
{

}

std::string TConf::getConfStr(std::string group, std::string key)
{

}

void TConf::setConfStr(std::string group, std::string key, std::string value)
{

}

} //namespace WebTool

#ifdef TEST_MAIN
int main(int args, char* argv[])
{

    WebTool::TConf mConf("./test.conf");
    mConf.setConfStr("[LOG]", "level", "debug");
    mConf.getConfStr("[LOG]", "level");

    return 0;
}
#endif
