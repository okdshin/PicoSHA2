cmake_minimum_required(VERSION 3.10)
project(pico)

option(PICO_TEST "build test" OFF)
option(PICO_EXAMPLE "build example" OFF)

if(PICO_TEST)
    add_subdirectory(test)
endif()

if(PICO_EXAMPLE)
    add_subdirectory(example)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
