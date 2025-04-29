if(DEFINED ENV{VIRTUAL_ENV})
    set(Python3_ROOT_DIR "$ENV{VIRTUAL_ENV}")
    message(STATUS "Using Python from virtualenv: $ENV{VIRTUAL_ENV}")
endif()
find_package(pybind11 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)


add_executable(allocator_main src/main.cpp)
# Explicitly inherit includes from linked library

target_link_libraries(allocator_main
    PRIVATE
        cable_allocator
        electronic_container
        electronic_component
        geometry_tools
        pybind11::embed
        Python3::Python    
)

target_include_directories(allocator_main PRIVATE ${Python3_INCLUDE_DIRS})
