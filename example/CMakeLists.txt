add_executable(hasher hasher.cpp)
target_link_libraries(hasher PRIVATE picosha2)

add_executable(interactive_hasher interactive_hasher.cpp)
target_link_libraries(interactive_hasher PRIVATE picosha2)