cmake_minimum_required(VERSION 3.3)
project(FreeRTOS-win)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 关闭 pointer-to-int-cast int转换警告  关闭mavlink警告 address-of-packed-member
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS}  -Wno-pointer-to-int-cast -Wno-address-of-packed-member")


file(GLOB FreeRTOSSrc
    FreeRTOS/*.c
    FreeRTOS/include/*.h
    FreeRTOS/portable/*.c
    FreeRTOS/portable/*.h
    FreeRTOS/portable/WinMM/*.c
    FreeRTOS/portable/WinMM/*.h
    lib/libenjoy/src/libenjoy_p.h
    lib/libenjoy/src/libenjoy.h
    lib/libenjoy/src/libenjoy.c
    lib/libenjoy/src/libenjoy_win32.c
    lib/libenjoy/src/libenjoy_win32.h
    MAVLINK/common/*.*
    MAVLINK/*.*
    src/*.*
    src/TASK/*.*
    src/DATALINK/*.*
    src/RC_INPUT/*.*

#    FreeRTOS/portable/Posix/*.c
#    FreeRTOS/portable/Posix/*.h
)

set(SOURCE_FILES src/main.c ${FreeRTOSSrc})
include_directories(. FreeRTOS/include FreeRTOS/portable MAVLINK src src/DATALINK src/TASK src/RC_INPUT lib/libenjoy/src)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 主要是适配portable 接口的
target_link_libraries(${PROJECT_NAME} winmm.dll ws2_32.dll)
#target_link_libraries(${PROJECT_NAME} X:/24-freerots/01-FreeRTOS-win/lib/pThread/lib/pthreadVC2.dll)