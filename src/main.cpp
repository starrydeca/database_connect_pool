#include "connectPool.h"
#include "databaseConnect.h"

int query() {
    databaseConnect conn;
    conn.connect("starry", "root", "dbConnectPool", "192.168.80.128");
    string sql = "insert into person values(6, 18, 'man', 'starry')";
    bool flag = conn.update(sql);
    cout << "flag value" << flag << endl;

    sql = "select * from person";
    conn.query(sql);
    while (conn.next()) {
        cout << conn.value(0) << ", "
            << conn.value(1) << ", "
            << conn.value(2) << ", "
            << conn.value(3) << endl;
    }
    return 0;
}

int main() {
    query();
    return 0;
}

