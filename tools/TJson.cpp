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

void TJson::setStr(std::string& obj, const std::string sKey,const std::string sValue)
{
    TJson json(obj);
    json.m_root[sKey] = sValue;
    obj = json.m_root.toStyledString();
}

void TJson::setObj(std::string& obj, const std::string sKey,const std::string sValue)
{
    TJson json(obj);
    TJson jsonTemp(sValue);
    json.m_root[sKey] = jsonTemp.m_root;
    obj = json.m_root.toStyledString();
}

void TJson::setInt(std::string& obj, const std::string sKey,const int iValue)
{
    TJson json(obj);
    json.m_root[sKey] = iValue;
    obj = json.m_root.toStyledString();
}


} //namespace WebTool

#ifdef TEST_MAIN

#include <iostream>

int main(int args, char* argv[])
{
    std::string str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}"; 
    std::cout << str << std::endl;
    WebTool::TJson mJson(str);
    std::string jsonStr;
    mJson.setStr(jsonStr, "aaa", "aaa");
    mJson.setInt(jsonStr, "num", 1024);
    mJson.setObj(str, "json", jsonStr);
    std::cout << str << std::endl;
    std::cout << mJson.getInt("code") << std::endl;
    std::cout << mJson.getStr("uploadid") << std::endl;
    return 0;
}
#endif
