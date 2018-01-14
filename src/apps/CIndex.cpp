#include "CIndex.h"
#include "../main.h"

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

    if("GET" == req.getMethod())
    {
        Response res;
//        res.setSetCookie("lk=cookie");
        TString data;
        if(0)
        {
            //login
            data.loadFile(TString(HTML_PATH) + "index.html");
        }
        else
        {
            //no login
            data.loadFile(TString(HTML_PATH) + "login.html");
        }
        res.setResData(data);
        return res;
    }
    else if("POST" == req.getMethod())
    {

        Response res;
        TString data;
        if(1)
        {
            //login success
            data.loadFile(TString(HTML_PATH) + "index.html");
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
