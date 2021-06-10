# 设置最低cmake版本
cmake_minimum_required(VERSION 2.8.3)

project(cmake_test)

# 设置头文件
include_directories(include)

#set(SOURCES src/test.cpp include/algorithm.cpp)

file(GLOB SOURCES "src/*.cpp”)
file(GLOB SOURCES_2 "include/*.cpp”)
set(ALL_SOURCES SOURCES SOURCES_2)

#add_executable(cmake_test ${SOURCES})
add_executable(cmake_test ${ALL_SOURCES})