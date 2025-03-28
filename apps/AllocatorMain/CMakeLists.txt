cmake_minimum_required(VERSION 3.10.0)
project(AllocatorMain VERSION 0.1.0 LANGUAGES C CXX)

add_executable(AllocatorMain src/main.cpp)
# Explicitly inherit includes from linked library
target_include_directories(AllocatorMain PRIVATE $<TARGET_PROPERTY:CableAllocation,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(AllocatorMain PRIVATE CableAllocation)
