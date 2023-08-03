#pragma once 

class connectPool {
 public:
     static connectPool* getConnectPool();
 private:
     connectPool();//懒汉模式——用到时创建
};
