#pragma once
#include <queue>
#include "databaseConnect.h"
#include <mutex>
#include <condition_variable>

class connectPool {
  public:
    static connectPool* getConnectPool();
    connectPool(const connectPool& obj) = delete;
    connectPool& operator=(const connectPool& obj) = delete;
    shared_ptr<databaseConnect>  getConnection();
    ~connectPool();
  private:
    connectPool();//懒汉模式——用到时创建
    bool parseJsonFile();
    void produceConnection();
    void recycleConnection();
    void addConnection();
  private:
    string m_ip;
    string m_user;
    string m_passwd;
    string m_dbName;
    unsigned short m_port;
    //连接池中，可连接数范围
    int m_minSize;
    int m_maxSize;
    //超时时间
    int m_timeout;
    int m_maxIdTime;

    queue<databaseConnect*> m_connectQ;//队列存放数据库连接
    mutex m_mutexQ;//操作连接池锁住
    condition_variable m_cond;//生产者消费者，控制连接池连接个数
};
