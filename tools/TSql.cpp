#include <iostream>
#include "TLog.h"
#include "TSql.h"

namespace WebTool {

TSqlData::TSqlData()
{

}

TSqlData::~TSqlData()
{

}

void TSqlData::addRowData(TSqlData::KeyValue sigKeyValueData, TSqlData::ColValue sigColValueData)
{
    m_vecKeyValueData.push_back(sigKeyValueData);
    m_vecColValueData.push_back(sigColValueData);
    m_row = m_vecKeyValueData.size();
    m_col = sigKeyValueData.size();
}

int TSqlData::getRow()
{
    return m_row;
}

int TSqlData::getCol()
{
    return m_col;
}

std::string TSqlData::getData(int row, std::string key)
{
    if(m_vecKeyValueData.size() > row)
    {
        KeyValue tmpKeyValue = m_vecKeyValueData.at(row);
        KeyValue::iterator iterMap;;
        iterMap = tmpKeyValue.find(key);
        if(iterMap != tmpKeyValue.end())
        {
            return tmpKeyValue[key];
        }
    }
    return "";
}

std::string TSqlData::getData(int row, int col)
{
    if(m_vecColValueData.size() > row)
    {
        ColValue tmpColValue = m_vecColValueData.at(row);
        ColValue::iterator iterMap;;
        iterMap = tmpColValue.find(col);
        if(iterMap != tmpColValue.end())
        {
            return tmpColValue[col];
        }
    }
    return "";
}


TMysql::TMysql(const std::string sIp,
               unsigned short uiPort,
               const std::string sUserName,
               const std::string sPassword,
               const std::string sDatabase):
    m_sIp(sIp),
    m_uiPort(uiPort),
    m_sUserName(sUserName),
    m_sPassword(sPassword),
    m_sDatabase(sDatabase)
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

int TMysql::openDB()
{
    if(mysql_real_connect(m_pMySql, m_sIp.c_str(),\
                m_sUserName.c_str(),\
                m_sPassword.c_str(),\
                m_sDatabase.c_str(), m_uiPort, NULL, 0))
    {
        std::cout << "connect mysql succeed!" << std::endl;
        return MYSQL_SUCCESS;
    }
    else
    {      
        std::cout << "error:" << mysql_error(m_pMySql);
    }
}


void TMysql::closeDB()
{
    if(m_pMySql)
    {
        mysql_close(m_pMySql);    
        std::cout << "close mysql" << std::endl;
        m_pMySql = NULL;
    }
}


int TMysql::execSQL(const std::string sSqlStr)
{
    if(!m_pMySql)
    {
        std::cout << "sql is disconnnect!" << std::endl;
        return MYSQL_E_CONNECT;
    }
    if(sSqlStr.length() == 0)
    {
        std::cout << "param error" << std::endl;
        return MYSQL_E_PARAM;
    }
    if(mysql_real_query(m_pMySql, sSqlStr.c_str(), sSqlStr.length())\
                != MYSQL_SUCCESS)
    {
        assert(m_pMySql != NULL);
        std::cout << "mysql error: " << mysql_errno(m_pMySql) \
            << mysql_error(m_pMySql) << std::endl;
        return MYSQL_E_QUERY;
    }
    return MYSQL_SUCCESS;
}


int TMysql::execSQL(const std::string sSqlStr,TSqlData &sqlData)
{
    if(!m_pMySql)
    {
        std::cout << "sql is disconnnect!" << std::endl;
        return MYSQL_E_CONNECT;
    }
    if(sSqlStr.length() == 0)
    {
        std::cout << "param error" << std::endl;
        return MYSQL_E_PARAM;
    }
    if(mysql_real_query(m_pMySql, sSqlStr.c_str(), sSqlStr.length())\
                != MYSQL_SUCCESS)
    {
        assert(m_pMySql != NULL);
        std::cout << "mysql error: " << mysql_errno(m_pMySql) \
            << mysql_error(m_pMySql) << std::endl;
        return MYSQL_E_QUERY;
    }
    auto result = mysql_store_result(m_pMySql);
    MYSQL_FIELD* field = mysql_fetch_fields(result);
    if(result)
    {
        auto num_row=mysql_num_rows(result);  
        auto num_col=mysql_num_fields(result);
        for(int row = 0; row < num_row; row++)
        {
            MYSQL_ROW mysqlRow = mysql_fetch_row(result);
            TSqlData::ColValue colValue;
            TSqlData::KeyValue keyValue;
            for(int col = 0; col < num_col; col++)
            {
                colValue[col] = mysqlRow[col];
                keyValue[field[col].name] = mysqlRow[col];
            }
            sqlData.addRowData(keyValue,colValue);
        }

    }
    return MYSQL_SUCCESS;
}


TSqlite::TSqlite(std::string dbFilePath):
    m_filePath(dbFilePath)
{

}

TSqlite::~TSqlite()
{

}

int TSqlite::openDB()
{
    return sqlite3_open(m_filePath.c_str(), &m_db);
}

int TSqlite::closeDB()
{
    return sqlite3_close(m_db);
}

int TSqlite::execSQL(std::string sql)
{
    char *errmsg = 0;
    int ret = sqlite3_exec(m_db, sql.c_str(), NULL, NULL, &errmsg);
    if(ret != SQLITE_OK)
    {
        CDBG << "ret = " <<  ret<<" , delete table fail: " << errmsg;
    }
    sqlite3_free(errmsg);
    return ret;
}

int sqlite3Callback(void *para, int n_column, char **column_value, char **column_name)
{
    //para是你在 sqlite3_exec 里传入的 void * 参数. 这里，我不使用 para 参数。忽略它的存在.
    //通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
    //n_column是这一条记录有多少个字段 (即这条记录有多少列)
    //char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以\0结尾）
    //char ** column_name 跟 column_value是对应的，表示这个字段的字段名称

    TSqlData* sqlData = (TSqlData*)para;

    TSqlData::KeyValue tmpKeyValue;
    TSqlData::ColValue tmpColValue;
    CDBG << n_column;
    for(int i = 0 ; i < n_column; i ++ )
    {
       tmpKeyValue[column_name[i]] = column_value[i];
       tmpColValue[i] = column_value[i];
       CDBG << column_name[i] << " = " <<column_value[i];
    }
    sqlData->addRowData(tmpKeyValue, tmpColValue);
   CDBG << "------------------\n";
   return 0;
}

int TSqlite::execSQL(std::string sql, TSqlData &retSqlData)
{
    char *errmsg = 0;
    int ret = sqlite3_exec(m_db, sql.c_str(), sqlite3Callback, &retSqlData, &errmsg);
    if(ret != SQLITE_OK)
    {
        CDBG << "ret = " <<  ret<<" , delete table fail: " << errmsg;
    }
    sqlite3_free(errmsg);
    return ret;
}





} //namespace WebTool


#ifdef TEST_MAIN
int main(int args, char* argv[])
{
#if 1
    std::cout << "----------TSQL test----------" << std::endl;
    WebTool::TMysql mysql("192.168.244.131", 3306, "root",\
                          "123456", "carbarn");
    mysql.openDB();
   // std::string sqlStr = "CREATE TABLE car(\
   //       id INT UNSIGNED AUTO_INCREMENT,\
   //       name VARCHAR(100) NOT NULL,\
   //       LicensePlate VARCHAR(40) NOT NULL,\
   //       date DATE,\
   //       PRIMARY KEY (_id)\
   //       )ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   // mysql.queryMySql(sqlStr);
    WebTool::TSqlData sqlData;
    mysql.execSQL("select * from car", sqlData);
    CDBG << sqlData.getCol();
    CDBG << sqlData.getRow();
    CDBG << sqlData.getData(0, "id");
    CDBG << sqlData.getData(0, 1);
    std::cout << std::endl;
    mysql.closeDB();

#else
    WebTool::TSqlite sqlite("/home/liukang/test.db");
    WebTool::TSqlData data;
    sqlite.openDB();
//    sqlite.execSQL("create table tb_test(ID int PRIMAY_KEY, name NVARCHAR_32)");
//    sqlite.execSQL("insert into tb_test values(1, 'liukang')");
//    sqlite.execSQL("insert into tb_test values(2, 'tutu')");
    sqlite.execSQL("select * from tb_test", data);

    CDBG << data.getCol();
    CDBG << data.getRow();
    CDBG << data.getData(0, "ID");
    CDBG << data.getData(0, 1);
    sqlite.closeDB();
#endif
    return 0;
}
#endif
