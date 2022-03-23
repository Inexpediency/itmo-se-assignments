cmake_minimum_required(VERSION 3.21)
project(itmo_se_assignments)

set(CMAKE_CXX_STANDARD 17)


include_directories(lib/dataStructures)
add_subdirectory(lib/dataStructures)

include_directories(lib/io)
add_subdirectory(lib/io)

add_executable(1-2_lab_1 1-2_lab_1/main.cpp)
target_link_libraries(1-2_lab_1 dataStructures_lib io_lib)
