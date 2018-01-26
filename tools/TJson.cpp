#include "TJson.h"
#include "Json/include/json.h"

namespace WebTool {

bool TJson::isValid(const std::string &obj)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    return jsonReader.parse(obj, jsonRoot);
}

std::string TJson::getStr(const std::string &obj, const std::string &sKey)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    if(jsonReader.parse(obj, jsonRoot))
    {
        return jsonRoot[sKey].asString();
    }
    return "";
}

std::string TJson::getObj(const std::string &obj, const std::string &sKey)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    if(jsonReader.parse(obj, jsonRoot))
    {
        return jsonRoot[sKey].toStyledString();
    }
    return "";
}

int TJson::getInt(const std::string &obj,  const std::string &sKey)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    if(jsonReader.parse(obj, jsonRoot))
    {
        return jsonRoot[sKey].asInt();
    }
    return -1;
}

std::vector<std::string> TJson::getArray(const std::string &obj, const std::string &sKey)
{

    std::string strArray = getObj(obj, sKey);
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    std::vector<std::string> array;
    if(jsonReader.parse(strArray, jsonRoot))
    {
        for(auto str : jsonRoot)
        {
            array.push_back(str.asString());
        }
    }
    return array;
}

void TJson::setStr(std::string &obj, const std::string &sKey,const std::string &sValue)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    jsonReader.parse(obj, jsonRoot);
    jsonRoot[sKey] = sValue;
    obj = jsonRoot.toStyledString();
}

void TJson::setObj(std::string &obj, const std::string &sKey,const std::string &sValue)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    Json::Value jsonRootTmp;
    jsonReader.parse(obj, jsonRoot);
    jsonReader.parse(sValue, jsonRootTmp);
    jsonRoot[sKey] = jsonRootTmp;
    obj = jsonRoot.toStyledString();
}

void TJson::setInt(std::string &obj, const std::string &sKey,const int &iValue)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    jsonReader.parse(obj, jsonRoot);
    jsonRoot[sKey] = iValue;
    obj = jsonRoot.toStyledString();
}

void TJson::setArray(std::string &obj, const std::string &sKey, const std::vector<std::string> &array)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    Json::Value jsonRootTmp;
    jsonReader.parse("", jsonRootTmp);
    for(auto str : array)
    {
        jsonRootTmp.append(str);
    }
    jsonReader.parse(obj, jsonRoot);
    jsonRoot[sKey] = jsonRootTmp;
    obj = jsonRoot.toStyledString();
}

} //namespace WebTool

#ifdef TEST_MAIN

#include <iostream>

int main(int args, char* argv[])
{
    std::string str = "{\"uploadid\": \"teststr\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
    std::cout << str << std::endl;
    std::cout << WebTool::TJson::isValid(str) << std::endl;
    std::cout << WebTool::TJson::getInt(str,"code") << std::endl;
    std::cout << WebTool::TJson::getStr(str, "uploadid") << std::endl;

    std::string jsonStr;
    std::string newStr;
    std::cout << "-----set func test---------" << std::endl;
    WebTool::TJson::setStr(jsonStr, "aaa", "中文测试");
    WebTool::TJson::setInt(jsonStr, "num", 1024);
    WebTool::TJson::setObj(newStr, "json", jsonStr);
    std::vector<std::string> testArray;
    testArray.push_back("1");
    testArray.push_back("2");
    WebTool::TJson::setArray(newStr, "array", testArray);
    WebTool::TJson::setStr(newStr, "strKey", "xxx");
    WebTool::TJson::setInt(newStr, "intKey", 102);
    std::cout << newStr << std::endl;
    // get func test
    std::cout << "------get func test---------" << std::endl;
    std::cout << WebTool::TJson::getInt(newStr, "intKey") << std::endl;
    std::cout << WebTool::TJson::getStr(newStr, "strKey") << std::endl;
    std::cout << WebTool::TJson::getObj(newStr, "json") << std::endl;
    std::vector<std::string> testGetArray;
    testGetArray = WebTool::TJson::getArray(newStr, "array");
    for(auto testStr : testGetArray)
    {
        std::cout << testStr << std::endl;   
    }
    return 0;
}
#endif
