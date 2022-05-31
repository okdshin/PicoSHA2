cmake_minimum_required(VERSION 3.10)

add_executable(hasher hasher.cpp)
target_include_directories(hasher
    PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
add_executable(interactive_hasher interactive_hasher.cpp)
target_include_directories(interactive_hasher
    PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)