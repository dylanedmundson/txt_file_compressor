cmake_minimum_required(VERSION 3.0.0)
set(this txt_file_compressor)
project(${this} VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(txt_file_compressor-exe)
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(tests) 
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)