cmake_minimum_required(VERSION 3.21)
project(itmo_se_assignments)

set(CMAKE_CXX_STANDARD 17)

# Libraries
include_directories(lib/dataStructures)
add_subdirectory(lib/dataStructures)

include_directories(lib/io)
add_subdirectory(lib/io)

include_directories(lib/flaviusJosephus)
add_subdirectory(lib/flaviusJosephus)

include_directories(lib/infectionSimulator)
add_subdirectory(lib/infectionSimulator)

# Executables for task solutions
add_executable(flaviusJosephus flaviusJosephus/main.cpp)
target_link_libraries(flaviusJosephus dataStructures_lib io_lib)

add_executable(infectionSimulator infectionSimulator/main.cpp)
target_link_libraries(infectionSimulator infectionSimulator_lib)
