#include "CIndex.h"

CIndex::CIndex()
{

}

CIndex::~CIndex()
{

}

Response CIndex::index(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    Params reqParams(req.getParams());
    Cookie reqCookie(req.getCookie());
    if("GET" == req.getMethod())
    {
        Response res;
        TString data;
        if("lk" == reqCookie["username"]
           && "325" == reqCookie["password"])
        {
            //login
            data.loadFile(TString(HTML_PATH) + "index.html");
        }
        else
        {
            //no login
            data.loadFile(TString(HTML_PATH) + "login.html");
        }
        reqCookie.setCookie("username", "lk22");
        reqCookie.setCookie("password", "32522");
        res.setSetCookie(reqCookie);

        res.setResData(data);
        return res;
    }
    else if("POST" == req.getMethod())
    {

        Response res;
        TString data;
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
        return res;
    }
}
