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

std::string TJson::getStr(const std::string obj, const std::string sKey)
{
    TJson json(obj);
    return json.m_root[sKey].asString();
}

std::string TJson::getObj(const std::string obj, const std::string sKey)
{

    TJson json(obj);
    return json.m_root[sKey].toStyledString();
}

int TJson::getInt(const std::string obj,  const std::string sKey)
{
    TJson json(obj);
    return json.m_root[sKey].asInt();
}

std::vector<std::string> TJson::getArray(const std::string obj, const std::string sKey)
{
    TJson json(obj);
    TJson jsonArray(json.getObj(obj, sKey));
    std::vector<std::string> array;
    for(auto str : jsonArray.m_root)
    {
        array.push_back(str.asString());
    }    
    return array;
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


void TJson::setArray(std::string& obj, const std::string sKey, const std::vector<std::string> array)
{
    
    TJson json(obj);
    TJson jsonTemp("");
    for(auto str : array)
    {
        jsonTemp.m_root.append(str);
    }  
    json.m_root[sKey] = jsonTemp.m_root;
    obj = json.m_root.toStyledString();
}

} //namespace WebTool

#ifdef TEST_MAIN

#include <iostream>

int main(int args, char* argv[])
{
    std::string str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}"; 
    std::cout << str << std::endl;
    std::string jsonStr;
    std::cout << "-----set func test---------" << std::endl;
    WebTool::TJson::setStr(jsonStr, "aaa", "中文测试");
    WebTool::TJson::setInt(jsonStr, "num", 1024);
    WebTool::TJson::setObj(str, "json", jsonStr);
    std::vector<std::string> testArray;
    testArray.push_back("1");
    testArray.push_back("2");
    WebTool::TJson::setArray(str, "array", testArray);
    std::cout << str << std::endl;
    // get func test
    std::cout << "------get func test---------" << std::endl;
    std::cout << WebTool::TJson::getInt(str,"code") << std::endl;
    std::cout << WebTool::TJson::getStr(str, "uploadid") << std::endl;
    std::cout << WebTool::TJson::getObj(str, "json") << std::endl;
    std::vector<std::string> testGetArray;
    testArray = WebTool::TJson::getArray(str, "array");
    for(auto testStr : testArray)
    {
        std::cout << testStr << std::endl;   
    }
    return 0;
}
#endif
