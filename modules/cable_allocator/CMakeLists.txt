if (DEFINED ENV{VIRTUAL_ENV})
    # Find Python first
    find_package(Python REQUIRED COMPONENTS Interpreter Development)
    
    # Set pybind11 path using correct Python version
    set(PYBIND11_DIR "$ENV{VIRTUAL_ENV}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/pybind11/share/cmake/pybind11")
    message(STATUS "Looking for pybind11 in: ${PYBIND11_DIR}")
    
    # Enable modern Python discovery
    set(PYBIND11_FINDPYTHON ON)
    find_package(pybind11 REQUIRED PATHS ${PYBIND11_DIR} NO_DEFAULT_PATH)

    # Create the Python module
    pybind11_add_module(cable_allocator_py src/cable_allocator_binding.cpp)
    
    # Set Python module output directory
    set_target_properties(cable_allocator_py 
        PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python_modules
    )
    
    # Link against our main library
    target_link_libraries(cable_allocator_py 
        PRIVATE 
            cable_allocator)
    
    # Add include directories for Python module
    target_include_directories(cable_allocator_py 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${pybind11_INCLUDE_DIRS}
    )
endif()

# Main library
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(cable_allocator STATIC ${SOURCES})

target_include_directories(cable_allocator 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(cable_allocator
    PUBLIC
        electronic_container
        electronic_component
        csv_parser
)

# Enable testing
enable_testing()

# Add test directory if it exists
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
endif()