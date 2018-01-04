#include "CLogin.h"

CLogin::CLogin()
{

}

CLogin::~CLogin()
{

}

// /login
void CLogin::login(FunParams)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s", method.c_str(), url.c_str(), params.c_str());

    if("GET" == method)
    {
        Response res;
        res.setSetCookie("lk=cookie");
        TString str;
        str.sprintf("this is login html: %s", params.c_str());
        res.responseStr(str);
    }
    else if("POST" == method)
    {

    }
}

// /regist
void CLogin::regist(FunParams)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s", method.c_str(), url.c_str(), params.c_str());

    if("GET" == method)
    {
        Response res;
        res.setSetCookie("lk=cookie");
        TString str;
        str.sprintf("this is regist html: %s", params.c_str());
        res.responseStr(str);
    }
    else if("POST" == method)
    {

    }
}
