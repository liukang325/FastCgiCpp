#include "CIndex.h"

#define SESSION_PWD "abcdefgliukanghahatest"
#define TEST_USER   "liukang"
#define TEST_PWD    "325"

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
        if(SESSION_PWD == WebTool::TEncode::base64Decode(reqCookie["session"]))
        {
            //login
            data.loadFile(TString(HTML_PATH) + "index.html");
        }
        else
        {
            //not login
            data.loadFile(TString(HTML_PATH) + "login.html");
        }
        reqCookie.delCookie("password");
        res.setSetCookie(reqCookie);
        res.setResData(data);

    }
    else if("POST" == req.getMethod())
    {
        // sql database
        if(TEST_USER == reqParams["username"]
                && TEST_PWD == reqParams["password"])
        {
            //login success
            data.loadFile(TString(HTML_PATH) + "index.html");
            reqCookie.setCookie("session", WebTool::TEncode::base64Encode(SESSION_PWD));
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
