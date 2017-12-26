#include "CLogin.h"

CLogin::CLogin()
{

}

CLogin::~CLogin()
{

}

void CLogin::login(std::string method, std::string url, std::string params)
{
    DBG(L_INFO, "~~~~method : %s,  url: %s~~ params: %s", method.c_str(), url.c_str(), params.c_str());

    Route::reponse("this is login html: %s", params.c_str());
}

void CLogin::regist(std::string method, std::string url, std::string params)
{
    DBG(L_INFO, "~~~~method : %s,  url: %s~~ params: %s", method.c_str(), url.c_str(), params.c_str());

    Route::reponse("this is regist html: %s", params.c_str());
}
