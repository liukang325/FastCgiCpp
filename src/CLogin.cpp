#include "CLogin.h"

CLogin::CLogin()
{

}

CLogin::~CLogin()
{

}

// /login
Response CLogin::login(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    if("GET" == req.getMethod())
    {
        Response res;
        res.setSetCookie("lk=cookie");
        TString data;
        data.sprintf("this is login html: %s", req.getParams().c_str());
        res.setResData(data);
        return res;
    }
    else if("POST" == req.getMethod())
    {

    }
}

// /regist
Response CLogin::regist(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    if("GET" == req.getMethod())
    {
        Response res;
        res.setSetCookie("lk=cookie");
        TString data;
        data.sprintf("this is regist html: %s", req.getParams().c_str());
        res.setResData(data);

        return res;
    }
    else if("POST" == req.getMethod())
    {

    }
}
