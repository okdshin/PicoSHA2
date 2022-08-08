cmake_minimum_required(VERSION 3.10)
project(picosha2)

option(PICOSHA2_TEST "build test" OFF)
option(PICOSHA2_EXAMPLE "build example" OFF)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(PICOSHA2_TEST)
    add_subdirectory(test)
endif()
if(PICOSHA2_EXAMPLE)
    add_subdirectory(example)
endif()
