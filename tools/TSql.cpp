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

/////////////////
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

/////////////////////////////////////////////
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
#if 0
    std::cout << "----------TSQL test----------" << std::endl;
    WebTool::TMysql mysql;
    mysql.connectMySql("192.168.244.131", 3306, "root",\
            "123456", "carbarn");
#endif
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
    return 0;
}
#endif
