#include "CIndex.h"

CIndex::CIndex()
{

}

CIndex::~CIndex()
{

}

///@ /index
Response CIndex::index(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    Params reqParams(req.getParams());
    Cookie reqCookie(req.getCookie());
    Response res;
    TString data;
    if("GET" == req.getMethod())
    {
        if("lk" == reqCookie["username"]
           && "325" == reqCookie["password"])
        {
            //login
            data.loadFile(TString(HTML_PATH) + "index.html");
        }
        else
        {
            //not login
            data.loadFile(TString(HTML_PATH) + "login.html");
        }
//        reqCookie.setCookie("username", "lk22");
//        reqCookie.setCookie("password", "32522");
        reqCookie.delCookie("password");
        res.setSetCookie(reqCookie);
        res.setResData(data);

    }
    else if("POST" == req.getMethod())
    {
        // sql database
        if("lk" == reqParams["username"]
                && "325" == reqParams["password"])
        {
            //login success
            data.loadFile(TString(HTML_PATH) + "index.html");
            reqCookie.setCookie("username", "lk");
            reqCookie.setCookie("password", "325");
            res.setSetCookie(reqCookie);
        }
        else
        {
            //login fail
            data.loadFile(TString(HTML_PATH) + "login.html");
        }
        res.setResData(data);
    }
    return res;
}
