# 添加第三方stb库依赖

set(STB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/stb")

# 添加测试可执行文件
# add_executable(test_math src/test_math.c)

add_executable(tcp_server src/tcp_server.c)
add_executable(tcp_client src/tcp_client.c)
add_executable(udp_client src/udp_client.c)
add_executable(udp_server src/udp_server.c)
# 包含头文件
# target_include_directories(test_math PRIVATE ../include)

target_include_directories(tcp_server PRIVATE ${STB_INCLUDE_DIR})
target_include_directories(tcp_client PRIVATE ${STB_INCLUDE_DIR})
target_include_directories(udp_client PRIVATE ${STB_INCLUDE_DIR})
target_include_directories(udp_server PRIVATE ${STB_INCLUDE_DIR})

target_link_libraries(udp_client PRIVATE m)
target_link_libraries(udp_server PRIVATE m)
# 链接主项目中的函数（如果需要测试内部函数）
# 或者使用完整的测试框架如Check
# target_link_libraries(test_math ${PROJECT_NAME})

# 添加测试
# add_test(NAME MathTest COMMAND test_math)

# copy 测试文件
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/asuna.jpg DESTINATION ${CMAKE_BINARY_DIR}/tests)
