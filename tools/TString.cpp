#include "TString.h"
#include "TLog.h"

namespace WebTool {


TString::TString()
{

}

TString::TString(const char *s)
{
    if(s)
        this->assign(s);
    else
        this->erase();
}

TString::TString(const std::string &s)
{
    this->assign(s);
}

TString::~TString()
{

}

TString TString::left(const std::string::size_type n) const
{
    size_t len = this->length();
    len = (n > len) ? len : n;
    return TString(this->substr(0, len));
}

TString TString::mid(const std::string::size_type pos, const std::string::size_type n) const
{
    if(pos > this->length())
        return TString("");
    return TString(this->substr(pos, n));
}

TString TString::right(const std::string::size_type n) const
{
    size_t len = this->length();
    len = (n > len) ? n : len;
    return TString(this->substr(len - n));
}

std::vector<TString> TString::split(const std::string &tag) const
{
    std::vector<TString> retVec;
    if(this->length() > 0)
    {
        size_t oldPos=0;
        size_t newPos=0;
        TString tempData;
        while(1)
        {
            newPos=this->find(tag,oldPos);
            if(newPos!=std::string::npos)
            {
                tempData = TString(this->substr(oldPos,newPos-oldPos));
                retVec.push_back(tempData);
                oldPos=newPos + tag.size();
            }
            else if(oldPos <= this->size())
            {
                tempData= TString(this->substr(oldPos));
                retVec.push_back(tempData);
                break;
            }
            else
            {
                break;
            }
        }
    }
    return retVec;
}

}//namespace WebTool

#ifdef TEST_MAIN
#include <iostream>
int main(int args, char* argv[])
{

    WebTool::TString tStr("key=value&name=lk&pwd=123");

    std::vector<WebTool::TString> vecStr = tStr.split("&");
    for(int i = 0; i < vecStr.size(); i++)
    {
        std::cout << vecStr.at(i) << "\n";
    }

    return 0;
}
#endif
