#include "Template.h"
#include "TLog.h"
#include<stdlib.h>

namespace WebTool {

Template::Template(const TString &filePath)
{
    m_strText.loadFile(filePath);
}

Template::~Template()
{

}

void Template::set(const TString &name, TString value)
{
    m_mapNameValue[name] = value;
}

TString Template::toStr()
{
    //replace all {{$xxx}}
    std::map<TString,TString>::iterator iter = m_mapNameValue.begin();
    for ( ; iter != m_mapNameValue.end(); ++iter )
    {
        m_strText.replaceAll("{{$" + iter->first + "}}", iter->second);
    }
    //move all {{$xxx}}
    std::string::size_type posStart = 0;
    std::string::size_type posEnd = 0;
    while(std::string::npos != (posStart = m_strText.find_first_of("{{$"))
          && std::string::npos != (posEnd = m_strText.find_first_of("}}"))
          && posStart < posEnd)
    {
        m_strText = m_strText.left(posStart) + m_strText.right(m_strText.length() - posEnd - 2);
    }
    return m_strText;
}


}//namespace WebTool

#ifdef TEST_MAIN
#include <iostream>
int main(int args, char* argv[])
{
    WebTool::Template tStr("/home/liukang/example.teml");
    tStr.set("username", "liukang");
    tStr.set("value", "helo");
    CDBG << tStr.toStr();
    return 0;
}
#endif
