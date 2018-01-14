#include "Cookie.h"
#include "TEncode.h"
#include "TLog.h"

Cookie::Cookie(const TString cookieStr)
{
    std::vector<TString> pairslist = cookieStr.split("; ");

    for ( size_t i = 0; i < pairslist.size(); ++i )
    {
        TString name = pairslist[i].substr( 0, pairslist[i].find("=") );
        TString value = pairslist[i].substr( pairslist[i].find("=") + 1 );

//        name.replaceAll( "+", " " );
//        name = TEncode::uriDecode(name);
//        value.replaceAll( "+", " " );
//        value = TEncode::uriDecode(value);

        CookieValue cookieValue;
        cookieValue.value = value;
        m_mapCookies[name] = cookieValue;
    }
}

Cookie::~Cookie()
{

}

TString Cookie::getCookie(const TString &name)
{
    if ( name != "" && m_mapCookies.find(name) != m_mapCookies.end() )
        return m_mapCookies[name].value;
    else
        return TString("");
}

void Cookie::setCookie(const TString &name, const TString &value,
                       const TString &expires, const TString &path,
                       const TString &domain)
{
    if ( name != "")
    {
        CookieValue cookieValue;
        cookieValue.value = value;
        cookieValue.expires = expires;
        cookieValue.path = path;
        cookieValue.domain = domain;
        m_mapCookies[name] = cookieValue;
    }
}

void Cookie::delCookie(const TString &name)
{
    this->setCookie(name, "", "01-01-1970 08:00:01 GMT" );
}

TString Cookie::toSetCookieStr()
{
    TString retStr;
    CookieList::iterator iterMap = m_mapCookies.begin();
    for(; iterMap != m_mapCookies.end(); iterMap++)
    {
        CookieValue cookieValue = iterMap->second;
        retStr.append("Set-Cookie: " + iterMap->first + "=" + cookieValue.value +
                      "; expires=" + cookieValue.expires +
                      "; path=" + cookieValue.path +
                      "; domain=" + cookieValue.domain + "\r\n");
    }
    return retStr;
}

