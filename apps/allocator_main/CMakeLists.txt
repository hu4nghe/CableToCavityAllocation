find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)


message(STATUS "Found pybind11 CMake dir: ${PYBIND11_DIR}")
find_package(pybind11 CONFIG REQUIRED PATHS "${PYBIND11_DIR}")

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
