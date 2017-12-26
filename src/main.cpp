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

#include "Route.h"

void login(std::string method, std::string url, std::string params)
{
    DBG(L_INFO, "~~~~method : %s,  url: %s~~ params: %s", method.c_str(), url.c_str(), params.c_str());

    Route::reponse("this is login html: %s", params.c_str());
}

int main(void)  
{  
    TLOG->initConfig(L_DEBUG, "file");
    DBG(L_DEBUG, "===========start===========");

    Route appRoute;
    appRoute.addRoute("/login", login);

    appRoute.exec();

    return 0;  
}
