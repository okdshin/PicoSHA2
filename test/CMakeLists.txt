cmake_minimum_required(VERSION 3.10)

include(CTest)

add_executable(unittest)

target_sources(unittest PRIVATE test.cpp)

target_include_directories(unittest
    PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

add_test(NAME unittest COMMAND unittest)