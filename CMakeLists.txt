#项目配置
cmake_minimum_required(VERSION 3.0)
project(database_connect_pool)

#指定c++ 20
set(CMAKE_CXX_STANDARD 20)

#生成ycm可识别的json文件，让源文件找到头文件
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON )

#源文件、头文件、输出路径
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ../bin)

#调试
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#输出可执行文件
add_executable(database_connect_pool ${SRC})

#将可执行文件链接动态库，使用jsoncpp
target_link_libraries(database_connect_pool jsoncpp)
#将可执行文件链接动态库，使用mysqlclient
target_link_libraries(database_connect_pool libmysqlclient.so)
