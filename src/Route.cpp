#include "Route.h"
#include "memory.h"

#ifdef MULTI_THREAD
#define THREAD_COUNT 20
static int counts[THREAD_COUNT];
#endif

Route::Route()
{

}

Route::~Route()
{

}

void Route::addRoute(TString requestRoute, FuncHttp func)
{
    m_routeMap.insert(std::map<TString , FuncHttp>::value_type(requestRoute, func));
}

void Route::exec()
{
#ifdef MULTI_THREAD
    pthread_t id[THREAD_COUNT];
    FCGX_Init();
    for (int i = 1; i < THREAD_COUNT; i++)
    {
        threadStruct p;
        p.pthis = this;
        p.threadID = i;
        pthread_create(&id[i], NULL, pthreadTask, (void*)&p);
    }
    processMessage(0);

#else

    while(FCGI_Accept() >= 0)
    {
        //"GET" or "POST"
        TString requestMethod =  TString(getenv("REQUEST_METHOD"));
        //"/login?key=value&name=pwd"
        TString requestUri = TString(getenv("REQUEST_URI"));
        size_t pos = requestUri.find_first_of("?");
        TString requestRoute = requestUri.left(pos);
        TString requestParam;
        if("GET" == requestMethod)
        {
            requestParam = requestUri.right(requestUri.length() - pos - 1);
        }
        else if("POST" == requestMethod)
        {
            int ilen = atoi(getenv("CONTENT_LENGTH")) + 1;
            char *bufpost = (char* )malloc(ilen);
            memset(bufpost, 0, ilen);
            FCGI_fread(bufpost, ilen, 1, FCGI_stdin);
            requestParam = TString(bufpost);
            free(bufpost);
        }

        std::map<TString , FuncHttp>::iterator iterMap;;
        iterMap = m_routeMap.find(requestRoute);
        if(iterMap == m_routeMap.end())
        {
            DBG(L_ERROR, "not find route: %s ", requestUri.c_str());
        }
        else
        {
            FuncHttp func = iterMap->second;
            Request req;
            req.setMethod(requestMethod);
            req.setUrl(requestRoute);
            req.setParams(requestParam);
            req.setCookie(getenv("HTTP_COOKIE"));

            Response res = func(req);

            FCGI_printf(res.Out().c_str());
        }
    }
#endif
}


#ifdef MULTI_THREAD
void Route::processMessage(int threadID)
{
    pid_t pid = getpid();
    int rc;
    FCGX_Request request;
    FCGX_InitRequest(&request, 0, 0);
    for(;;)
    {
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
        static pthread_mutex_t counts_mutex = PTHREAD_MUTEX_INITIALIZER;

        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(&request);
        pthread_mutex_unlock(&accept_mutex);
        if (rc < 0)
            break;

        std::string httpCookie;
        if(FCGX_GetParam("HTTP_COOKIE", request.envp))
            httpCookie = std::string(FCGX_GetParam("HTTP_COOKIE", request.envp));

        //"GET" or "POST"
        TString requestMethod;
        if(FCGX_GetParam("REQUEST_METHOD", request.envp))
            requestMethod = TString(FCGX_GetParam("REQUEST_METHOD", request.envp));

        //"/login?key=value&name=pwd"
        TString requestUri;
        if(FCGX_GetParam("REQUEST_URI", request.envp))
            requestUri = TString(FCGX_GetParam("REQUEST_URI", request.envp));

        size_t pos = requestUri.find_first_of("?");

        TString requestRoute = requestUri.left(pos);
        TString requestParam;
        if("GET" == requestMethod)
        {
            if(-1 != pos)
            {
                requestParam = requestUri.right(requestUri.length() - pos - 1);
            }
        }
        else if("POST" == requestMethod)
        {
            if(FCGX_GetParam("CONTENT_LENGTH", request.envp))
            {
                int ilen = atoi(FCGX_GetParam("CONTENT_LENGTH", request.envp)) + 1;
                char *bufpost = (char* )malloc(ilen);
                memset(bufpost, 0, ilen);
//                FCGI_fread(bufpost, ilen, 1, FCGI_stdin);
                FCGX_GetStr(bufpost,ilen,request.in);
                requestParam = TString(bufpost);
                free(bufpost);
            }
        }

        std::map<TString , FuncHttp>::iterator iterMap;;
        iterMap = m_routeMap.find(requestRoute);
        if(iterMap == m_routeMap.end())
        {
            DBG(L_ERROR, "not find route: %s ", requestUri.c_str());
        }
        else
        {
            FuncHttp func = iterMap->second;
            Request req;
            req.setMethod(requestMethod);
            req.setUrl(requestRoute);
            req.setParams(requestParam);
            req.setCookie(httpCookie);

            Response res = func(req);

            DBG(L_DEBUG, "res.Out: %s", res.Out().c_str());

            FCGX_PutS(res.Out().c_str(), request.out);
        }

        //sleep(2);

        pthread_mutex_lock(&counts_mutex);
        DBG(L_DEBUG, "counts: %5d , PID: %d, threadID: %d" , ++counts[threadID], pid, threadID);
        pthread_mutex_unlock(&counts_mutex);
        FCGX_Finish_r(&request);
    }
}
#endif
