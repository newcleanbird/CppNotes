# 单文件CMake

# 指定版本
cmake_minimum_required(VERSION 3.0) 

# 指定C++标准:-std=c++11
set(CMAKE_CXX_STANDARD 11)  

# 工程名
project(demo)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  #设置c++的编译选项
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")  #设置c的编译选项

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 指定输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(main ${SRC})
