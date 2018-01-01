/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月12日 15时47分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>  
#include <stdlib.h>
#include <sys/types.h>  
  
#ifdef HAVE_UNISTD_H  
#include <unistd.h>  
#endif  

#include "CLogin.h"

#include "TConf.h"
TConf gConf("CgiCpp.conf");

int main(void)  
{  
    TString type = gConf.getConfStr("[LOG]", "type", "file");
    TString fileName = gConf.getConfStr("[LOG]", "fileName", "CgiCpp.log");
    TString ip = gConf.getConfStr("[LOG]", "ip", "127.0.0.1");
    TString port = gConf.getConfStr("[LOG]", "port", "9090");
//    CDBG << type;
//    CDBG << fileName;
//    CDBG << ip;
//    CDBG << port;
    TLOG->initConfig(L_DEBUG, type, fileName,ip, port.toInt());
    DBG(L_DEBUG, "===========start===========");

    //login module
    CLogin appLogin;

    Route appRoute;
    appRoute.addRoute("/login", routeBind(CLogin::login, appLogin));
    appRoute.addRoute("/regist", routeBind(CLogin::regist, appLogin));

    appRoute.exec();

    return 0;  
}
