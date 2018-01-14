#include "CLogin.h"

CLogin::CLogin()
{

}

CLogin::~CLogin()
{

}

///@ /login
Response CLogin::login(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    Response res;
    TString data;
    if("GET" == req.getMethod())
    {
        data.sprintf("this is login test html: %s", req.getParams().c_str());
        res.setResData(data);
    }
    else if("POST" == req.getMethod())
    {
        res.setResData("post success test");
    }
    return res;
}

///@ /regist
Response CLogin::regist(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    Response res;
    TString data;
    if("GET" == req.getMethod())
    {
        data.sprintf("this is regist test html: %s", req.getParams().c_str());
        res.setResData(data);
    }
    else if("POST" == req.getMethod())
    {
        res.setResData("post success test");
    }
    return res;
}
