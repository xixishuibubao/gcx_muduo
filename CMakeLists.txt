
cmake_minimum_required(VERSION 3.17)
project(gcx_muduo)

# C++ 标准配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出路径（自动创建）
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH} ${EXECUTABLE_OUTPUT_PATH})

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -fPIC -pthread")

# 配置你的库的公开头文件路径（使用者需要）
set(PUBLIC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
include_directories(${PUBLIC_INCLUDE_DIR})  # 你的代码能找到自己的头文件

# 递归扫描：根目录 + src 所有子目录的 .c/.cpp
file(GLOB_RECURSE SRC_LIST
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/*.c
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# 排除无关目录（按需调整，保留你需要的目录）
list(FILTER SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/cmake-build-debug/.*")
list(FILTER SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/lib/.*")
list(FILTER SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/third_party/.*")
list(FILTER SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/examples/.*")
list(FILTER SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/tools/.*")

# 编译可执行文件（确保所有扫描到的 .cpp 中仅有一个 main 函数）
add_executable(gcx_muduo ${SRC_LIST})

# （可选）编译动态库（排除 main.cpp）
# list(FILTER SRC_LIST EXCLUDE REGEX ".*main.cpp")
# add_library(gcx_muduo SHARED ${SRC_LIST})