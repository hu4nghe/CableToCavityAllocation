cmake_minimum_required(VERSION 3.16)
project(CableAllocationProject)

if(NOT DEFINED ENV{VIRTUAL_ENV})
    set(_default_venv_path "${CMAKE_SOURCE_DIR}/Python/DSLyon")
    if(EXISTS "${_default_venv_path}/bin/activate")
        set(ENV{VIRTUAL_ENV} "${_default_venv_path}")
        set(VIRTUAL_ENV "${_default_venv_path}" CACHE PATH "Python virtual environment")
        message(STATUS "✅ Automatically using virtual env at ${_default_venv_path}")
    else()
        message(WARNING "❌ VIRTUAL_ENV is not set. Using system Python instead.")
    endif() 
else()
    set(VIRTUAL_ENV "$ENV{VIRTUAL_ENV}" CACHE PATH "Python virtual environment")
    message(STATUS "✅ Using virtual environment: $ENV{VIRTUAL_ENV}")
endif()


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
add_subdirectory(apps/module_tester)