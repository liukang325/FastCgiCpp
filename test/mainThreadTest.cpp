/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年1月5日 12时47分06秒
 *       Revision:  none
 *       Compiler:  g++ -o mainThreadTest.cgi mainThreadTest.cpp -lfcgi -lpthread
 *
 *         Author:  liukang
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>  
#include <fcgi_stdio.h>  
#include "fcgi_config.h"  
#include <stdlib.h>
  
#include <sys/types.h>  
  
#ifdef HAVE_UNISTD_H  
#include <unistd.h>  
#endif  
  
using namespace std;  
  
#define THREAD_COUNT 20

static int counts[THREAD_COUNT];

static void *pthread_func(void *a)
{
    int threadID = (int)(a);
    pid_t pid = getpid();
    int rc;
    FCGX_Request request;
    FCGX_InitRequest(&request, 0, 0);
    for (;;)
    {
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
        static pthread_mutex_t counts_mutex = PTHREAD_MUTEX_INITIALIZER;

        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(&request);
        pthread_mutex_unlock(&accept_mutex);

        if (rc < 0)
            break;

        std::string strRetData;
        strRetData += "Hello World Thread FCGI~~~ ";

        std::string serverSoftware;
        if(FCGX_GetParam("SERVER_SOFTWARE", request.envp))
            serverSoftware = std::string(FCGX_GetParam("SERVER_SOFTWARE", request.envp));
        std::string queryString;
        if(FCGX_GetParam("QUERY_STRING", request.envp))
            queryString = std::string(FCGX_GetParam("QUERY_STRING", request.envp));
        std::string requestMethod;
        if(FCGX_GetParam("REQUEST_METHOD", request.envp))
            requestMethod = std::string(FCGX_GetParam("REQUEST_METHOD", request.envp));
        std::string contentType;
        if(FCGX_GetParam("CONTENT_TYPE", request.envp))
            contentType = std::string(FCGX_GetParam("CONTENT_TYPE", request.envp));
        std::string contentLength;
        if(FCGX_GetParam("CONTENT_LENGTH", request.envp))
            contentLength = std::string(FCGX_GetParam("CONTENT_LENGTH", request.envp));
        std::string scriptFilename;
        if(FCGX_GetParam("SCRIPT_FILENAME", request.envp))
            scriptFilename = std::string(FCGX_GetParam("SCRIPT_FILENAME", request.envp));
        std::string scriptName;
        if(FCGX_GetParam("SCRIPT_NAME", request.envp))
            scriptName = std::string(FCGX_GetParam("SCRIPT_NAME", request.envp));
        std::string requestUri;
        if(FCGX_GetParam("REQUEST_URI", request.envp))
            requestUri = std::string(FCGX_GetParam("REQUEST_URI", request.envp));
        std::string documentUri;
        if(FCGX_GetParam("DOCUMENT_URI", request.envp))
            documentUri = std::string(FCGX_GetParam("DOCUMENT_URI", request.envp));
        std::string documentRoot;
        if(FCGX_GetParam("DOCUMENT_ROOT", request.envp))
            documentRoot = std::string(FCGX_GetParam("DOCUMENT_ROOT", request.envp));
        std::string serverPortocol;
        if(FCGX_GetParam("SERVER_PROTOCOL", request.envp))
            serverPortocol = std::string(FCGX_GetParam("SERVER_PROTOCOL", request.envp));
        std::string remoteAddr;
        if(FCGX_GetParam("REMOTE_ADDR", request.envp))
            remoteAddr = std::string(FCGX_GetParam("REMOTE_ADDR", request.envp));
        std::string remotePort;
        if(FCGX_GetParam("REMOTE_PORT", request.envp))
            remotePort = std::string(FCGX_GetParam("REMOTE_PORT", request.envp));
        std::string serverAddr;
        if(FCGX_GetParam("SERVER_ADDR", request.envp))
            serverAddr = std::string(FCGX_GetParam("SERVER_ADDR", request.envp));
        std::string serverPort;
        if(FCGX_GetParam("SERVER_PORT", request.envp))
            serverPort = std::string(FCGX_GetParam("SERVER_PORT", request.envp));
        std::string serverName;
        if(FCGX_GetParam("SERVER_NAME", request.envp))
            serverName = std::string(FCGX_GetParam("SERVER_NAME", request.envp));
        std::string httpCookie;
        if(FCGX_GetParam("HTTP_COOKIE", request.envp))
            httpCookie = std::string(FCGX_GetParam("HTTP_COOKIE", request.envp));

        strRetData += "<br> SERVER_SOFTWARE: " + serverSoftware;
        strRetData += "<br> QUERY_STRING: " + queryString;
        strRetData += "<br> REQUEST_METHOD: " + requestMethod;
        strRetData += "<br> CONTENT_TYPE: " + contentType;
        strRetData += "<br> CONTENT_LENGTH: " + contentLength;
        strRetData += "<br> SCRIPT_FILENAME: " + scriptFilename;
        strRetData += "<br> SCRIPT_NAME: " + scriptName;
        strRetData += "<br> REQUEST_URI: " + requestUri;
        strRetData += "<br> DOCUMENT_URI: " + documentUri;
        strRetData += "<br> DOCUMENT_ROOT: " + documentRoot;
        strRetData += "<br> SERVER_PROTOCOL: " + serverPortocol;
        strRetData += "<br> REMOTE_ADDR: " + remoteAddr;
        strRetData += "<br> REMOTE_PORT: " + remotePort;
        strRetData += "<br> SERVER_ADDR: " + serverAddr;
        strRetData += "<br> SERVER_PORT: " + serverPort;
        strRetData += "<br> SERVER_NAME: " + serverName;
        strRetData += "<br> HTTP_COOKIE: " + httpCookie;

        FCGX_PutS("Content-type: text/html\r\n\r\n", request.out);
        FCGX_PutS(strRetData.c_str(), request.out);

//        sleep(2);

        pthread_mutex_lock(&counts_mutex);
        ++counts[threadID];
        for (int i = 0; i < THREAD_COUNT; i++)
            FCGX_FPrintF(request.out, "<br>counts: %5d , PID: %d, threadID: %d" , counts[i], pid, threadID);
        pthread_mutex_unlock(&counts_mutex);
        FCGX_Finish_r(&request);
    }
    return NULL;
}

int main(void)
{
    pthread_t id[THREAD_COUNT];

    FCGX_Init();

    for (int i = 1; i < THREAD_COUNT; i++)
        pthread_create(&id[i], NULL, pthread_func, (void*)i);

    pthread_func(0);
    return 0;
}
