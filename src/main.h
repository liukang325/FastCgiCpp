/*
 * =====================================================================================
 *
 *       Filename:  main.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018年01月14日 13时24分24秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

#pragma once

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "route/Route.h"
#include "route/Cookie.h"
#include "route/Params.h"


#include "apps/CIndex.h"
#include "apps/CLogin.h"

#include "TConf.h"
static TConf gConf("fcgi.conf");

#define HTML_PATH   "/home/liukang/workspace/FastCgiCpp/html/"
