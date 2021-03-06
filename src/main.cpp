#include "main.h"

int main(void)  
{  
    TString type = gConf.getConfStr("[LOG]", "type", "file");
    TString fileName = gConf.getConfStr("[LOG]", "fileName", "fcgi.log");
    TString ip = gConf.getConfStr("[LOG]", "ip", "127.0.0.1");
    TString port = gConf.getConfStr("[LOG]", "port", "9090");
    TString threadCount = gConf.getConfStr("[ROUTE]", "threadCount", "10");

    TLOG->initConfig(L_DEBUG, type, fileName,ip, port.toInt());
    DBG(L_DEBUG, "===========start=========== type:%s, fileName:%s, ip:%s, port:%s",
        type.c_str(), fileName.c_str(), ip.c_str(), port.c_str());




    Route appRoute(threadCount.toInt());
    CIndex appIndex;
    appRoute.addRoute("/", routeBind(CIndex::index, appIndex));
    appRoute.addRoute("/index", routeBind(CIndex::index, appIndex));
    CLogin appLogin;
    appRoute.addRoute("/logout", routeBind(CLogin::logout, appLogin));
    appRoute.addRoute("/login", routeBind(CLogin::login, appLogin));
    CArticle appArticle;
    appRoute.addRoute("/article-list", routeBind(CArticle::articleList, appArticle));

    appRoute.exec();

    return 0;  
}
