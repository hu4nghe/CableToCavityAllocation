file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(electronic_container STATIC ${SOURCES})

target_include_directories(electronic_container
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface>
)

target_link_libraries(electronic_container
    PUBLIC
        electronic_component
        geometry_tools
)
