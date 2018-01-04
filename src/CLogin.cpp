#include "CLogin.h"

CLogin::CLogin()
{

}

CLogin::~CLogin()
{

}

// /login
void CLogin::login(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str());

    if("GET" == req.getMethod())
    {
        Response res;
        res.setSetCookie("lk=cookie");
        TString str;
        str.sprintf("this is login html: %s", req.getParams().c_str());
        res.responseStr(str);
    }
    else if("POST" == req.getMethod())
    {

    }
}

// /regist
void CLogin::regist(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str());
    if("GET" == req.getMethod())
    {
        Response res;
        res.setSetCookie("lk=cookie");
        TString str;
        str.sprintf("this is regist html: %s", req.getParams().c_str());
        res.responseStr(str);
    }
    else if("POST" == req.getMethod())
    {

    }
}
