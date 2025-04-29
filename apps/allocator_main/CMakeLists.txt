if (VIRTUAL_ENV)
    message(STATUS "Using virtual environment: ${VIRTUAL_ENV}")

    find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

    set(PYBIND11_DIR "${VIRTUAL_ENV}/lib/python3.12/site-packages/pybind11/share/cmake/pybind11")
    message(STATUS "Looking for pybind11 in: ${PYBIND11_DIR}")

    set(PYBIND11_FINDPYTHON ON)
    find_package(pybind11 REQUIRED PATHS ${PYBIND11_DIR} NO_DEFAULT_PATH)
else()
    message(STATUS "VIRTUAL_ENV is not defined. Skipping Python module build.")
endif()



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
