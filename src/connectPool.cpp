#include "connectPool.h"
#include <chrono>
#include <jsoncpp/json/json.h>
using namespace Json;
#include <fstream>
#include <thread>

connectPool* connectPool::getConnectPool() {
    static connectPool pool;
    return &pool;
}

bool connectPool::parseJsonFile() {
    ifstream ifs("dbconf.json");
    Reader rd;
    Value root;
    rd.parse(ifs, root);
    if (root.isObject()) {
        m_ip = root["ip"].asString();
        m_port = root["port"].asInt();
        m_user = root["userName"].asString();
        m_passwd = root["password"].asString();
        m_dbName = root["dbName"].asString();
        m_minSize = root["minSize"].asInt();
        m_maxSize = root["maxSize"].asInt();
        m_maxIdTime = root["maxIdTime"].asInt();
        m_timeout = root["timeout"].asInt();
        return true;
    }
    return false;
}

void connectPool::produceConnection() {
    while (true) {
        unique_lock<mutex> locker(m_mutexQ);
        while (int(m_connectQ.size()) >= m_minSize) {
            m_cond.wait(locker);
        }
        addConnection();
        m_cond.notify_all();
    }
}

void connectPool::recycleConnection() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(500));
        lock_guard<mutex> locker(m_mutexQ);
        while (int(m_connectQ.size()) > m_minSize) {
            databaseConnect* conn = m_connectQ.front();
            if (conn->getAliveTime() >= m_maxIdTime) {
                m_connectQ.pop();
                delete conn;
            }
            else break;
        }
    }
}

void connectPool::addConnection() {
    databaseConnect* conn = new databaseConnect;
    conn->connect(m_user, m_passwd, m_dbName, m_ip, m_port);
    conn->refreshAliveTime();
    m_connectQ.push(conn);
}

    shared_ptr<databaseConnect> connectPool::getConnection() {
        unique_lock<mutex> locker(m_mutexQ);
    while (m_connectQ.empty()) {
        if (cv_status::timeout == m_cond.wait_for(locker, chrono::milliseconds(m_timeout))) {
            if (m_connectQ.empty()) continue;
        }
    }
    shared_ptr<databaseConnect> connptr(m_connectQ.front(), [this](databaseConnect* conn) {
            lock_guard<mutex> locker(m_mutexQ);
            conn->refreshAliveTime();
            m_connectQ.push(conn);
            });
    m_connectQ.pop();
    m_cond.notify_all();
    return connptr;
}

connectPool::connectPool() {
    //加载配置文件
    if (!parseJsonFile())   return ;

    for (int i = 0; i < m_minSize; i++) {
        addConnection();       
    }
    thread prodecer(&connectPool::produceConnection, this);
    thread recycler(&connectPool::recycleConnection, this);
    prodecer.detach();
    recycler.detach();
}

connectPool::~connectPool() {
    while (!m_connectQ.empty()) {
        databaseConnect* conn = m_connectQ.front();
        m_connectQ.pop();;
        delete  conn;
    }
}
