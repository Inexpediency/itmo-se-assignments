cmake_minimum_required(VERSION 3.21)
project(itmo_se_assignments)

set(CMAKE_CXX_STANDARD 17)

# Libraries
include_directories(lib/slae)
add_subdirectory(lib/slae)

# Executables for task solutions
add_executable(slaeSolver slaeSolver/main.cpp)
target_link_libraries(slaeSolver slae_lib)
