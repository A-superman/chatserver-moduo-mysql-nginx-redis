cmake_minimum_required(VERSION 3.0) #最低cmake版本
project(main) #非可执行文件名，工程名

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g) #加上-g选项（默认带-o？）

#指定搜索的子目录
add_subdirectory(testmuduo)