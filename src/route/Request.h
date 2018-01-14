/*
 * =====================================================================================
 *
 *       Filename:  Request.h
 *
 *    Description:  Request/Response Class
 *
 *        Version:  1.0
 *        Created:  2018年01月13日 21时30分28秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include <fcgi_stdio.h>
#include "fcgi_config.h"
#include "TLog.h"
#include "TString.h"
#include "Cookie.h"

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
    void setSetCookie(const Cookie str);

    void setResData(TString str);

    TString Out();

private:

    //Content-type:
    TString m_contentType;

    //Set-Cookie:
    Cookie m_setCookie;

    //html txt
    TString m_resData;

};
