#include "TJson.h"

namespace WebTool {

TJson::TJson(std::string sJson):
    m_sJson(sJson)
{
    if (m_reader.parse(m_sJson, m_root))
    {
        m_bValid = true;
    }
    else
    {
        m_bValid = false;
    }
}

TJson::~TJson()
{

}

bool TJson::isValid()
{
    return m_bValid;
}

std::string TJson::getStr(const std::string sKey)
{
    return m_root[sKey].asString();
}

std::string TJson::getObj(const std::string sKey)
{
//    return m_root[sKey].as;
}

int TJson::getInt(const std::string sKey)
{
    return m_root[sKey].asInt();
}

void TJson::setStr(const std::string sKey, std::string sValue)
{

}

void TJson::setObj(const std::string sKey, std::string sValue)
{

}

void TJson::setInt(const std::string sKey, int iValue)
{

}


} //namespace WebTool

#ifdef TEST_MAIN

#include <iostream>

int main(int args, char* argv[])
{
    std::string str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
    WebTool::TJson mJson(str);
    std::cout << mJson.getInt("code") << std::endl;
    std::cout << mJson.getStr("uploadid") << std::endl;

    return 0;
}
#endif
