#include "Params.h"
#include "TJson.h"

Params::Params(const TString paramsStr):
    m_bJson(false)
{

    m_bJson = WebTool::TJson::isValid(paramsStr);

    if(!m_bJson)
    {
        //not json;
        std::vector<TString> pairslist = paramsStr.split("&");

        for ( size_t i = 0; i < pairslist.size(); ++i )
        {
            TString name = pairslist[i].substr( 0, pairslist[i].find("=") );
            TString value = pairslist[i].substr( pairslist[i].find("=") + 1 );

            m_mapParams[name] = value;
        }
    }
}

Params::~Params()
{

}

TString Params::getParams(const TString &name)
{
    if ( name != "" && m_mapParams.find(name) != m_mapParams.end() )
        return m_mapParams[name];
    else
        return TString("");
}

TString Params::toStr()
{
    TString retStr;
    ParamsList::iterator iterMap = m_mapParams.begin();
    for(; iterMap != m_mapParams.end(); iterMap++)
    {
        retStr.append(iterMap->first);
        retStr.append("=");
        retStr.append(iterMap->second);
        retStr.append("&");
    }
    return retStr.left(retStr.length() - 1);
}
