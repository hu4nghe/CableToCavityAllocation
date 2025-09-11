cmake_minimum_required(VERSION 3.16)
project(CableAllocationProject)

set(_default_venv_path "${CMAKE_SOURCE_DIR}/Python/DSLyon")

if(WIN32)
    set(_python_exe "${_default_venv_path}/Scripts/python.exe")
else()
    set(_python_exe "${_default_venv_path}/bin/python")
endif()

if(EXISTS "${_python_exe}")
    set(Python3_EXECUTABLE "${_python_exe}" CACHE FILEPATH "Python executable" FORCE)
    message(STATUS "✅ Using Python from venv: ${_python_exe}")
else()
    message(FATAL_ERROR "❌ Virtualenv not found at ${_default_venv_path}, please create it first.")
endif()

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

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
add_subdirectory(modules/geometry_tools)

# executable
add_subdirectory(apps/allocator_main)