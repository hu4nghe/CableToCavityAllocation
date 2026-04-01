# ---------- Python / venv ----------
set(venv_path "${CMAKE_SOURCE_DIR}/Python/DSLyon")

if(WIN32)
    set(python_exe "${venv_path}/Scripts/python.exe")
else()
    set(python_exe "${venv_path}/bin/python")
endif()

if(NOT EXISTS "${python_exe}")
    message(FATAL_ERROR "Python venv not found.\n")
endif()

set(Python3_EXECUTABLE "${python_exe}" CACHE FILEPATH "Python executable" FORCE)
set(Python3_FIND_VIRTUALENV FIRST)
set(Python3_FIND_STRATEGY LOCATION)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Using Python from venv:")
message(STATUS "Executable: ${Python3_EXECUTABLE}")
message(STATUS "Include:    ${Python3_INCLUDE_DIRS}")
message(STATUS "Library:    ${Python3_LIBRARIES}")

set(Python3_ROOT_DIR venv_path)
set(Python3_FIND_VIRTUALENV TRUE)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Using Python: ${Python3_EXECUTABLE}")
message(STATUS "Python include dirs: ${Python3_INCLUDE_DIRS}")

execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Found pybind11 CMake dir: ${PYBIND11_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

add_executable(allocator_main src/main.cpp)

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
