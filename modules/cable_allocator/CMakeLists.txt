file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(cable_allocator STATIC ${SOURCES})

target_include_directories(cable_allocator 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(cable_allocator
    PUBLIC
        electronic_container
        electronic_component
)