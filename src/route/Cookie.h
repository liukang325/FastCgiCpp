/*
 * =====================================================================================
 *
 *       Filename:  TCookie.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年12月14日 16时24分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liukang
 *        Company:
 *
 * =====================================================================================
 */

#pragma once

#include <TString.h>
#include <map>

using namespace WebTool;

typedef std::map<TString, TString> CookieList;

class  Cookie
{
public:
    Cookie(const TString cookieStr);
    ~Cookie();

    /// 取得cookie内容
    TString getCookie( const TString &name );

    /// 取得cookie内容
    inline TString operator[] ( const TString &name ) {
        return this->getCookie( name );
    }

    /// 设置cookie内容
    /// \param name cookie名字
    /// \param value cookie值
    void setCookie( const TString &name, const TString &value);

    /// 清除指定的cookie内容
    /// \param name cookie名字
    inline void delCookie( const TString &name );

    TString toStr();
private:

    CookieList m_mapCookies;

};

