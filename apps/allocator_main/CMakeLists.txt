find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

execute_process(
    COMMAND "${VIRTUAL_ENV}/Scripts/python.exe" -c
            "import pybind11; import os; print(os.path.join(os.path.dirname(pybind11.__file__), 'share', 'cmake', 'pybind11'))"
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
