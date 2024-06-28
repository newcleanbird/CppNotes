#设置cmake最小的版本要求
cmake_minimum_required(VERSION 3.10)
#设置项目名
project(project_name)
#添加可执行文件(第一个参数是生成的可执行文件的名字，第二个参数是源文件)
add_executable(project_name xxx.cpp)
