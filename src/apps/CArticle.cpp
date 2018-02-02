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
            TString videoListStr;

            std::vector<std::string> vecFile;
            vecFile = WebTool::TFile::getFileListFromDir("/home/liukang/workspace/video/advideo");
            for(auto fileName : vecFile)
            {
                WebTool::Template videoTemp(TString(HTML_PATH) + "videoTemp.html");
                videoTemp.set("videoTitle", fileName);
                videoTemp.set("videoSrc", "../../../video/advideo/" + fileName);
                videoListStr.append(videoTemp.toStr());
//                DBG(L_INFO,"%s", videoTemp.toStr().c_str());
            }

            WebTool::Template videoListTemp(TString(HTML_PATH) + "video.html");
            videoListTemp.set("videoList", videoListStr);

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
