add_library(
    datastructures
    datastructures/compressHoff.c
    datastructures/compressHoff.h
    datastructures/priorityQueue.c
    datastructures/priorityQueue.h
)

target_include_directories(datastructures PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")