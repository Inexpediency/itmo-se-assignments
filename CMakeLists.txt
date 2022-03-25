cmake_minimum_required(VERSION 3.21)
project(itmo_se_assignments)

set(CMAKE_CXX_STANDARD 17)


include_directories(lib/dataStructures)
add_subdirectory(lib/dataStructures)

include_directories(lib/io)
add_subdirectory(lib/io)

add_executable(flaviusJosephus flaviusJosephus/main.cpp)
target_link_libraries(flaviusJosephus dataStructures_lib io_lib)
