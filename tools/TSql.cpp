#include <iostream>
#include "TSql.h"

namespace WebTool {
    
TMysql::TMysql()
{
    m_pMySql = mysql_init(NULL);
    if(!m_pMySql)
    {
        std::cout << "error:" << mysql_error(m_pMySql);
        exit(1);
    }
}

TMysql::~TMysql()
{

}

int TMysql::connectMySql(const std::string sIp,
                     unsigned short uiPort,
                     const std::string sUserName,
                     const std::string sPassword,
                     const std::string sDatabase)
{
    if(mysql_real_connect(m_pMySql, sIp.c_str(),\
                sUserName.c_str(),\
                sPassword.c_str(),\
                sDatabase.c_str(), uiPort, NULL, 0))
    {
        std::cout << "connect mysql succeed!" << std::endl;
        return MYSQL_SUCCESS;
    }
    else
    {      
        std::cout << "error:" << mysql_error(m_pMySql);
    }
}

} //namespace WebTool


#ifdef TEST_MAIN
int main(int args, char* argv[])
{
    std::cout << "----------TSQL test----------" << std::endl;
    WebTool::TMysql mysql;
    mysql.connectMySql("192.168.244.131", 3306, "root",\
            "123456", "carbarn");
    return 0;
}
#endif
