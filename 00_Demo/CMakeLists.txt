# 收集所有源文件
# file(GLOB SRC_FILES "*.c")

# 或者明确列出源文件（推荐）
set(SRC_FILES
    src/main.c
    src/utils.c
    src/math_operations.c
)

# 包含头文件目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 创建可执行文件
add_executable(demo ${SRC_FILES})

# 设置输出目录
# set_target_properties(demo PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

# 链接库（如果有）
# target_link_libraries(${PROJECT_NAME} m)  # 链接数学库

# 安装目标
# install(TARGETS ${PROJECT_NAME}
#     RUNTIME DESTINATION bin
# )