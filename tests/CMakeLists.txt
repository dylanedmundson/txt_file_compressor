cmake_minimum_required(VERSION 3.0.0)
set(this txt_file_compressor_tests)
project(${this} VERSION 0.1.0)

add_library(
    datastructure-tests
    datastructures/testCompressHoff.c
    datastructures/testPriorityQueue.c
)

set(SOURCES
    datastructures/testCompressHoff.c
    datastructures/testPriorityQueue.c
)

add_executable(${this} ${SOURCES})
add_test(${this} ${SOURCES})

target_link_libraries(${this} PRIVATE datastructures)