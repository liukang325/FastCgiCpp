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
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>

#define CDBG    std::cout << "\n[CDBG] " << __FUNCTION__ << "():"<< __LINE__ << " "

namespace WebTool {

TConf::TConf(const std::string &configName):
    m_configName(configName)
{

}

TConf::~TConf()
{

}

std::string TConf::getConfStr(const std::string &group, const std::string &key, const std::string &valueDefault)
{
    readConfig();

    if (0 == key.length())
        return valueDefault;
    GroupDef::iterator iterGroup = m_groupConfig.find(group);
    if(iterGroup == m_groupConfig.end())
    {
        //not find
        return valueDefault;
    }
    KeyValueDef valuelist = iterGroup->second;
    KeyValueDef::iterator iterValue = valuelist.find(key);
    if(iterValue == valuelist.end())
    {
        //not find
        return valueDefault;
    }
    return iterValue->second;
}

bool TConf::setConfStr(const std::string &group, const std::string &key, const std::string &value)
{
    readConfig();

    if (0 == key.length())
        return false;
    m_groupConfig[group][key] = value;

    saveConfig();
}

void TConf::delKey(const std::string &group, const std::string &key)
{
    readConfig();
    GroupDef::iterator iterGroup = m_groupConfig.find(group);
    if(iterGroup != m_groupConfig.end())
    {
        KeyValueDef valuelist = iterGroup->second;
        KeyValueDef::iterator iterKey = valuelist.find(key);
        if(iterKey != valuelist.end())
        {
            valuelist.erase(iterKey);
        }
    }
    saveConfig();
}

void TConf::delGroup(const std::string &group)
{
    readConfig();
    GroupDef::iterator iterGroup = m_groupConfig.find(group);
    if(iterGroup != m_groupConfig.end())
    {
        m_groupConfig.erase(iterGroup);
    }
    saveConfig();
}

void TConf::readConfig()
{
    m_groupConfig.clear();
    std::size_t pos;
    std::string currentGroup, currentKey, currentValue;
    std::ifstream readFile;
    readFile.open(m_configName.c_str());
    if(readFile.is_open())
    {
        std::string strReadLine;
        while(std::getline(readFile,strReadLine))
        {
            if(strReadLine.length() > 0)
            {
                if('[' == strReadLine.at(0) && ']' == strReadLine.at(strReadLine.length() - 1))
                {
                    KeyValueDef null_value;
                    m_groupConfig[strReadLine] = null_value;
                    currentGroup = strReadLine;
                }
                else if('#' == strReadLine.at(0)) {
                    continue;
                }
                else if ( (pos = strReadLine.find_first_of("=")) != strReadLine.npos )
                {
                    std::string key = strReadLine.substr(0, pos);
                    std::string value = strReadLine.substr(pos + 1);
                    if(0 == key.length())
                        continue;

                    m_groupConfig[currentGroup][key] = value;
                }
            }
            else
            {

            }
        }
        readFile.close();
    }
}

void TConf::saveConfig()
{
    std::string strOut;
    GroupDef::iterator iterGroup = m_groupConfig.begin();
    for ( ; iterGroup != m_groupConfig.end(); ++iterGroup )
    {
        if ( iterGroup->first != "" )
            strOut += (iterGroup->first) + "\n";

        // for each value
        KeyValueDef valuelist = iterGroup->second;
        KeyValueDef::iterator iterValue = valuelist.begin();
        for ( ; iterValue != valuelist.end(); ++iterValue )
            strOut += (iterValue->first) + "=" + (iterValue->second) + "\n";
    }

    std::ofstream outFile;
    outFile.open(m_configName.c_str());
    if(outFile.is_open())
    {
        outFile << strOut;
        outFile.close();
    }
}

} //namespace WebTool

#ifdef TEST_MAIN
int main(int args, char* argv[])
{

    WebTool::TConf mConf("./test.conf");
    mConf.setConfStr("[LOG]", "newlevel", "l23");
    mConf.setConfStr("[LOG]", "lklk", "abc9");

    mConf.setConfStr("[ENV]", "ip", "192.168.0.1");
    mConf.setConfStr("[ENV]", "port", "9090");

    CDBG << mConf.getConfStr("[LOG]", "level");
    CDBG << mConf.getConfStr("[LOG]", "lklk");

    CDBG << mConf.getConfStr("[ENV]", "port");

    return 0;
}
#endif
