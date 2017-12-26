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

int main(void)  
{  
    TLOG->initConfig(L_DEBUG, "file");
    DBG(L_DEBUG, "===========start===========");

    //login module
    CLogin appLogin;

    Route appRoute;
    appRoute.addRoute("/login", routeBind(CLogin::login, appLogin));
    appRoute.addRoute("/regist", routeBind(CLogin::regist, appLogin));

    appRoute.exec();

    return 0;  
}
