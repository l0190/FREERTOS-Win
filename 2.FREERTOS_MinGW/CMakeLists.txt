#设置CMake最低版本号
cmake_minimum_required(VERSION 3.5)
#设置工程名称
project(FREERTOS_Project)

#设置编译参数
set(CMAKE_CXX_STANDARD 11)#设置C++版本]]
set(CMAKE_BUILD_TYPE "Debug")# 设置CMake构建类型:调试debug(可以查看中间变量),发布用Release(运行速度快)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)# 设置输出文件路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)#设置库文件输出目录

# 设置源文件
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)
# 设置变量FREERTOS_DIR的值
set(FREERTOS_DIR "D:/tools/code/c/FreeRTOS/FreeRTOS")

#输出验证FREERTOS_DIR的值
message("Value of FREERTOS_DIR: ${FREERTOS_DIR}")

#将指定目录下的所有.c文件载入FREERTOS_SOURCES
FILE(GLOB FREERTOS_SOURCES ${FREERTOS_DIR}/Source/*.c)# 递归遍历目录,获取所有的c文件
list(APPEND FREERTOS_SOURCES "${FREERTOS_DIR}/Source/portable/MemMang/heap_3.c")
list(APPEND FREERTOS_SOURCES "${FREERTOS_DIR}/Source/portable/MSVC-MingW/port.c")
message("Value of FREERTOS_SOURCES: ${FREERTOS_SOURCES}")
# 添加头文件路径
include_directories(
        include
        ${FREERTOS_DIR}/Source/include/
        ${FREERTOS_DIR}/Source/portable/MSVC-MingW/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# 将源码编译成一个可执行文件,名字为FREERTOS_Project.
# add_executable(可执行文件名字 源文件位置)
add_executable(FREERTOS_Project ${SOURCE_FILES} ${FREERTOS_SOURCES})

# 添加相关的win链接库
target_link_libraries(${PROJECT_NAME} winmm.dll ws2_32.dll)