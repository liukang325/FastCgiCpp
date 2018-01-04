#include "Request.h"

Request::Request()
{

}

Request::~Request()
{

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
