enable_testing()

add_executable(testPriorityQueue datastructures/testPriorityQueue.c)
add_executable(testCompressHoff datastructures/testCompressHoff.c)
add_test(
    NAME testPriorityQueue COMMAND testPriorityQueue
)
add_test(NAME testCompressHoff COMMAND testCompressHoff)

target_link_libraries(testPriorityQueue PUBLIC datastructures)
target_link_libraries(testCompressHoff PUBLIC datastructures)