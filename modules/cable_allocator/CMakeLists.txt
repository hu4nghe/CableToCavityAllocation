if (DEFINED ENV{VIRTUAL_ENV})
    set(PYBIND11_DIR "$ENV{VIRTUAL_ENV}/lib/python3.X/site-packages/pybind11/share/cmake/pybind11")
    find_package(pybind11 REQUIRED PATHS ${PYBIND11_DIR} NO_DEFAULT_PATH)
endif()

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
)