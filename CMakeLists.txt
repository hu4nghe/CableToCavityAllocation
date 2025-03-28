cmake_minimum_required(VERSION 3.10.0)

project(CableAllocationProject)


# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add subdirectories
add_subdirectory(libs/CableAllocation)
add_subdirectory(apps/AllocatorMain)