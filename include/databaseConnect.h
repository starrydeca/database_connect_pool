#pragma once
#include <iostream>
using namespace std;
#include <chrono>
using namespace chrono;
#include <string>
#include <mysql/mysql.h>

class databaseConnect {
  public:
    //初始化数据库连接
    databaseConnect();
    //释放数据库连接
    ~databaseConnect();
    //连接数据库
    bool connect(string user, string passwd, string dbName, string ip, unsigned short port = 3306);
    //更新数据库连接
    bool update(string sql);
    //查询数据库连接
    bool query(string sql);
    //遍历查询得到的结果集
    bool next();
    //得到结果集中的字段值
    string value(int index);
    //事物操作
    bool transaction();
    //提交事物
    bool commit();
    //事物回滚
    bool rollback();
    //刷新起始的空闲时间点
    void refreshAliveTime();
    //计算连接存活的总时长
    long long getAliveTime();
  private:
    void freeResult();//释放结果集
  private:
    MYSQL* m_conn = nullptr;//数据库对象
    MYSQL_RES* m_result = nullptr;//数据库结果集
    MYSQL_ROW m_row = nullptr;//结构为MYSQL_ROW的下一行结果
    steady_clock::time_point m_alivetime;    
};
