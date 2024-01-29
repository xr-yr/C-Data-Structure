cmake_minimum_required(VERSION 3.25)
project(DataStructure C)

set(CMAKE_C_STANDARD 11)

include_directories(common)

IF(WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=GBK")
ENDIF()

# 线性表结构
add_subdirectory(01.LinearTable)

# 树结构
add_subdirectory(02.Tree)

# 栈结构
add_subdirectory(03.Stack)

# 队列结构
add_subdirectory(04.Queue)
