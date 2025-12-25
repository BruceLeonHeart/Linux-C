

add_executable(thread_demo src/thread.c)
add_executable(thread_input src/thread_input.c)
add_executable(thread_output src/thread_output.c)

target_link_libraries(thread_demo pthread)
target_link_libraries(thread_input pthread)
target_link_libraries(thread_output pthread)
