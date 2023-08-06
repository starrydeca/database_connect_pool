# database_connect_pool
## 参考链接

<a herf="https://www.bilibili.com/video/BV1Fr4y1s7w4?p=16&vd_source=9d3fcd844b0ad55a330b3afec653d682" title="基于C++11的数据库连接池【C++/数据库/多线程/MySQL】">基于C++11的数据库连接池【C++/数据库/多线程/MySQL】</a>

## 环境配置

### Linux版本
    Ubuntu

### Mysql

    # 安装mysql
    sudo apt upgrade && sudo apt install mysql-server mysql-client libmysqlclient-dev
    # 进入mysql
    sudo mysql -u root
    # 创建用户——这里根据自己所需配置
    create user 'starry'@'%' identified by 'root';
    # 给新用户符全部权限
    grant all on *.* to 'starry'@'%';
    
    # 退出mysql
    exit

    # 设置mysql远程连接
    sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
    # 注释掉
    bind-address = 127.0.0.1
    # 或者改成
    bind-address = 0.0.0.0
    # 重启mysql服务
    sudo service mysql restart

### jsoncpp

    # 安装jsoncpp
    sudo apt upgrade && sudo apt install libjsoncpp-dev
    
### CMake 
    # 如果你不会Cmake下面就不用看了，自己编译的时候链接上面两个库就行啦

    # 要编译本项目，要安装CMake
    sudo apt upgrade && sudo apt install cmake    

    # 如果你想学CMake,自己去找资料吧。这里说作者的难点，编译，链接上方两个库
    # 将可执行文件链接动态库，使用jsoncpp
    target_link_libraries(database_connect_pool jsoncpp)
    # 将可执行文件链接动态库，使用mysqlclient
    target_link_libraries(database_connect_pool libmysqlclient.so)

## 编译

    # 在build目录下，执行以下命令
    cmake ..
    make

## 运行
    
    # 可执行文件，在bin/下

## 运行结果
    1.单线程：使用/不使用连接池
        不使用：非连接池，单线程，用时：42693912629纳秒，42693毫秒
        使用：连接池，单线程，用时：9150030844纳秒，9150毫秒
    2.多线程：使用/不使用连接池
        不使用：非连接池，多线程，用时：60792322338纳秒，60792毫秒
        使用：连接池，多线程，用时：3522916191纳秒，3522毫秒

## 最后

如果有帮助，留下star吧！
