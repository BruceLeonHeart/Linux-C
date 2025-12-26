cmake_minimum_required(VERSION 3.10)

project(my_project
    VERSION 1.0.0
    DESCRIPTION "LINUX-C"
    LANGUAGES C
)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


# 设置编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g -O0")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()


# 调试信息
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")


# 添加可执行文件
add_subdirectory(00_Demo)
add_subdirectory(01_File)
add_subdirectory(03_Thread)
add_subdirectory(05_Network)

# 如果需要添加测试
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# 安装规则（可选）
# install(DIRECTORY include/ DESTINATION include)
