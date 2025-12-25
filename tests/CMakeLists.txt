# 添加测试可执行文件
add_executable(test_math test_math.c)

# 包含头文件
target_include_directories(test_math PRIVATE ../include)

# 链接主项目中的函数（如果需要测试内部函数）
# 或者使用完整的测试框架如Check
target_link_libraries(test_math ${PROJECT_NAME})

# 添加测试
add_test(NAME MathTest COMMAND test_math)