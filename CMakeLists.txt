#项目配置
cmake_minimum_required(VERSION 3.0)
project(database_connect_pool)

#生成json文件，让源文件找到头文件
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON )

#源文件、头文件、输出路径
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ..)

#调试
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#输出可执行文件
add_executable(database_connect_pool ${SRC})
