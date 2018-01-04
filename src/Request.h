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

private:


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
