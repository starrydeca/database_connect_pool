#include "connectPool.h"

connectPool* connectPool::getConnectPool() {
    static connectPool pool;
    return &pool;
}
