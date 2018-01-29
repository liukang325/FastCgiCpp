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
            TString dataListStr;
            WebTool::Template videoTemp(TString(HTML_PATH) + "videoTemp.html");
            videoTemp.set("videoTitle", "广告一");
            videoTemp.set("videoSrc", "video/ad_01.mp4");

            WebTool::Template videoListTemp(TString(HTML_PATH) + "video.html");
            videoListTemp.set("videoList", videoTemp.toStr());

            WebTool::Template temp(TString(HTML_PATH) + "template.html");
            temp.set("newTitle1", "testTitle");
            temp.set("newTitle2", "article");
            temp.set("newHtml", videoListTemp.toStr());
            data = temp.toStr();
        }
        res.setResData(data);

    }
    else if("POST" == req.getMethod())
    {
        res.setResData("");
    }
    return res;
}
