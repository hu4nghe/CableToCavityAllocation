cmake_minimum_required(VERSION 3.16)
project(CableAllocationProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# libs
add_subdirectory(modules/electronic_component)
add_subdirectory(modules/electronic_container)
add_subdirectory(modules/cable_allocator)
add_subdirectory(modules/csv_parser)
add_subdirectory(modules/py_module)

# executable
add_subdirectory(apps/allocator_main)
add_subdirectory(apps/module_tester)