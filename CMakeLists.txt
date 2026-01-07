cmake_minimum_required(VERSION 3.16)
project(CableToCavityAllocation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(modules/electronic_component)
add_subdirectory(modules/electronic_container)
add_subdirectory(modules/cable_allocator)
add_subdirectory(modules/geometry_tools)
add_subdirectory(apps/allocator_main)