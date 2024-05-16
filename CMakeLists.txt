#project name
project(SWAP_LIBRARY)

#以上两个命令是必须的两个命令

#add compile options
add_compile_options("-std=c++17")

#宏定义
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set CMAKE_BUILD_TYPE
set( CMAKE_BUILD_TYPE Debug )

# 把所有头文件包含进目录文件夹
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/inc/log_util)
# 搜集指定目录 . 和./src 下的源文件，将输出结果列表储存到变量ALL_SOURCE中
#aux_source_directory(. ALL_SOURCE)
aux_source_directory(${CMAKE_SOURCE_DIR}/src ALL_SOURCE)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/log_util ALL_SOURCE)

# Add an executable with the above sources
add_executable(web_server main.cpp ${ALL_SOURCE})