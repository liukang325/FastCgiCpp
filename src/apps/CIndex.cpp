#include "CIndex.h"

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
            TString dataStr;
            dataStr.loadFile(TString(HTML_PATH) + "index.html");

            WebTool::Template temp(TString(HTML_PATH) + "template.html");
            temp.set("newTitle1", "首页");
            temp.set("newTitle2", "我的桌面");
            temp.set("newHtml", dataStr);
            data = temp.toStr();
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
            TString dataStr;
            dataStr.loadFile(TString(HTML_PATH) + "index.html");

            WebTool::Template temp(TString(HTML_PATH) + "template.html");
            temp.set("newTitle1", "首页");
            temp.set("newTitle2", "我的桌面");
            temp.set("newHtml", dataStr);
            data = temp.toStr();
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
