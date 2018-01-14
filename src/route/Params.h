/*
 * =====================================================================================
 *
 *       Filename:  Params.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018年01月14日 20时10分28秒
 *       Revision:  none
 *       Compiler:  g++
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
    /// @paramsStr eg:"key=value&name=pwd" or json
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

    /// 是否为json
    bool m_bJson;
};

