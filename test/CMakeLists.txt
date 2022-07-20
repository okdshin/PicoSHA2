include(CTest)

add_executable(unittest test.cpp)

target_link_libraries(unittest PRIVATE picosha2)

add_test(NAME unittest COMMAND unittest)