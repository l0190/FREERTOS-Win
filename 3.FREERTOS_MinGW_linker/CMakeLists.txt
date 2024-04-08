#设置CMake最低版本号
cmake_minimum_required(VERSION 3.5)
#设置工程名称
project(FREERTOS_Project)

#设置编译参数
set(CMAKE_CXX_STANDARD 11)#设置C++版本]]
set(CMAKE_BUILD_TYPE "Debug")# 设置CMake构建类型:调试debug(可以查看中间变量),发布用Release(运行速度快)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)# 设置输出文件路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)#设置库文件输出目录

#添加头文件目录
include_directories(./include)
#添加链接库目录
link_directories(./lib)
#添加源文件目录中所有的源文件
aux_source_directory(./src SRC_LIST)

# 将源码编译成一个可执行文件,名字为FREERTOS_Project.
# add_executable(可执行文件名字 源文件位置)
add_executable(${PROJECT_NAME} ${SRC_LIST} main.c)

# 添加相关的win链接库
target_link_libraries(${PROJECT_NAME} winmm.dll freertos_kernel.a)