#include "TString.h"
#include "TLog.h"
#include<stdlib.h>

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

int TString::toInt() const
{
    int ret = atoi(this->c_str());

    return ret;
}

std::string va_sprintf( va_list ap, const std::string &format ) {
    int strlen = 256;
    char *buf = new char[strlen];
    memset( buf, 0, strlen );

    int size = vsnprintf( buf, strlen, format.c_str(), ap );
    if ( size >= strlen ) {
        delete[] buf;
        buf = NULL;
        buf = new char[size+1];
        memset( buf, 0, size+1 );
        vsnprintf( buf, size+1, format.c_str(), ap );
    }

    std::string result = buf;
    delete[] buf;
    buf = NULL;
    return result;
}
bool TString::sprintf( const char *format, ... )
{
    va_list ap;
    va_start(ap, format);
    *this = va_sprintf(ap, format);
    va_end(ap);
    return true;
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
