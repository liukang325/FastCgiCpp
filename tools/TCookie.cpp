#include "TCookie.h"
#include "TEncode.h"

namespace WebTool {

TCookie::TCookie(const TString cookieStr)
{
    std::vector<TString> pairslist = cookieStr.split(";");

    for ( size_t i = 0; i < pairslist.size(); ++i )
    {
        TString name = pairslist[i].substr( 0, pairslist[i].find("=") );
        TString value = pairslist[i].substr( pairslist[i].find("=") + 1 );

        name.replaceAll( "+", " " );
        name = TEncode::uriDecode(name);
        value.replaceAll( "+", " " );
        value = TEncode::uriDecode(value);

        m_cookies[name] = value;
    }
}

TString TCookie::getCookie(const TString &name)
{

}

void TCookie::setCookie(const TString &name, const TString &value) const
{

}

void TCookie::delCookie(const TString &name) const
{

}


} //namespace WebTool
