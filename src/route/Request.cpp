#include "Request.h"

Request::Request():
    m_method(""),
    m_url(""),
    m_params(""),
    m_cookie("")
{

}

Request::~Request()
{

}

void Request::setMethod(TString str)
{
    m_method = str;
}

void Request::setUrl(TString str)
{
    m_url = str;
}

void Request::setParams(TString str)
{
    m_params = str;
}

void Request::setCookie(TString str)
{
    m_cookie = str;
}

TString Request::getMethod()
{
    return m_method;
}

TString Request::getUrl()
{
    return m_url;
}

TString Request::getParams()
{
    return m_params;
}

TString Request::getCookie()
{
    return m_cookie;
}

//////////////////////////////////////////////////////
Response::Response():
    m_contentType("text/html"),
    m_setCookie(""),
    m_resData("")
{

}

Response::~Response()
{

}

void Response::setContentType(const TString str)
{
    m_contentType = str;
}

void Response::setSetCookie(const Cookie cookie)
{
    m_setCookie = cookie;
}

void Response::setResData(TString str)
{
    m_resData = str;
}

TString Response::Out()
{
    std::vector<TString>  vecSetCookieList = m_setCookie.toVecKeyValue();
    TString retStr;
    retStr += "Content-type: " + m_contentType + "\r\n";
    for(int i = 0; i < vecSetCookieList.size(); i++)
    {
        retStr += "Set-Cookie: " + vecSetCookieList[i] + "\r\n";
    }
    retStr += "\r\n";

    DBG(L_DEBUG, "%s", retStr.c_str());
    retStr += m_resData;
    return retStr;

}
