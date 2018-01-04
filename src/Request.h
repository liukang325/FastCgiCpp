#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include <fcgi_stdio.h>
#include "fcgi_config.h"
#include "TLog.h"
#include "TString.h"

using namespace WebTool;

class  Request
{
public:
    Request();
    ~Request();

    void setMethod(TString str);
    void setUrl(TString str);
    void setParams(TString str);
    void setCookie(TString str);

    TString getMethod();
    TString getUrl();
    TString getParams();
    TString getCookie();

private:

    TString m_method;
    TString m_url;
    TString m_params;
    TString m_cookie;

};


class  Response
{
public:
    Response();
    ~Response();

    void setContentType(const TString str);
    void setSetCookie(const TString str);
    void responseStr(const TString str);

private:

    TString m_contentType;
    TString m_setCookie;


};
