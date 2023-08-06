#include "databaseConnect.h"

databaseConnect::databaseConnect() {
    //mysql 环境初始化
    m_conn = mysql_init(nullptr);
    //mysql 字符集设置 utf8
    mysql_set_character_set(m_conn, "utf8");
}

databaseConnect::~databaseConnect() {
    //mysql 环境关闭
    if (m_conn != nullptr) {
        mysql_close(m_conn);
    }
    freeResult();
}

bool databaseConnect::connect(string user, string passwd, string dbName, string ip, unsigned short port) {
    MYSQL* ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);
    return ptr != nullptr;
}

bool databaseConnect::update(string sql) {
    if (mysql_query(m_conn, sql.c_str()))   return false;
    return true;
}

bool databaseConnect::query(string sql) {
    freeResult();//保存结果时，清空上一次的结果
    if (mysql_query(m_conn, sql.c_str()))   return false;
    m_result = mysql_store_result(m_conn);
    return true;
}

bool databaseConnect::next() {
    if (m_result != nullptr) {
        m_row = mysql_fetch_row(m_result);
        if (m_row != nullptr)   return true;
    }
    return false;
}

string databaseConnect::value(int index) {
    int listCount = mysql_num_fields(m_result);
    if (index >= listCount || index < 0)    return string();
    char* val = m_row[index];//返回值为char* 有'\0'
    unsigned long length = mysql_fetch_lengths(m_result)[index];//取出第index列的属性长度
    return string(val, length);//去除'\0'
}

bool databaseConnect::transaction() {
    return mysql_autocommit(m_conn, false);
}

bool databaseConnect::commit() {
    return mysql_commit(m_conn);
}

bool databaseConnect::rollback() {
    return mysql_rollback(m_conn);
}

void databaseConnect::freeResult() {
    if (m_result) {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}

void databaseConnect::refreshAliveTime() {
    m_alivetime = steady_clock::now();
}

long long databaseConnect::getAliveTime() {
    nanoseconds res = steady_clock::now() - m_alivetime;
    milliseconds millisec = duration_cast<milliseconds>(res);
    return millisec.count();
}
