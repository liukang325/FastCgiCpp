/*
 * =====================================================================================
 *
 *       Filename:  Params.h
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

typedef std::map<TString, TString> ParamsList;

class  Params
{
public:
    Params(const TString paramsStr);
    ~Params();

    /// 取得cookie内容
    TString getParams( const TString &name );

    /// 取得cookie内容
    inline TString operator[] ( const TString &name ) {
        return this->getParams( name );
    }

    TString toStr();
private:

    ParamsList m_mapParams;

    bool m_bJson;
};

