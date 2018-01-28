#include "CArticle.h"


///@ /article-list
Response CArticle::articleList(Request req)
{
    DBG(L_DEBUG, "method : %s,  url: %s,  params: %s, cookie: %s",
        req.getMethod().c_str(),
        req.getUrl().c_str(),
        req.getParams().c_str(),
        req.getCookie().c_str());

    Cookie reqCookie(req.getCookie());
    Response res;
    TString data;
    if("GET" == req.getMethod())
    {
        if(SESSION_PWD != WebTool::TEncode::base64Decode(reqCookie["session"]))
        {
            //not login
            data.loadFile(TString(HTML_PATH) + "login.html");
        }
        else
        {
            TString temStr;
            temStr.loadFile(TString(HTML_PATH) + "template.html");
            TString dataStr;
            dataStr.loadFile(TString(HTML_PATH) + "video.html");
            data.sprintf(temStr.c_str(), dataStr.c_str());
            DBG(L_INFO, "%s", data.c_str());
        }
        reqCookie.delCookie("password");
        res.setSetCookie(reqCookie);
        res.setResData(data);

    }
    else if("POST" == req.getMethod())
    {
        res.setResData("");
    }
    return res;
}
