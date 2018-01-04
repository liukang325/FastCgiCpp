#include "Request.h"

Request::Request()
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


Response::Response():
    m_contentType("text/html")
{

}

Response::~Response()
{

}

void Response::setContentType(const TString str)
{
    m_contentType = str;
}

void Response::setSetCookie(const TString str)
{
    m_setCookie = str;
}

void Response::responseStr(const TString str)
{
    TString retStr;
    retStr += "Content-type: " + m_contentType + "\r\n";
    retStr += "Set-Cookie: " + m_setCookie + "\r\n";
    retStr += "\r\n";
    retStr += str;
    FCGI_printf(retStr.c_str());
}
