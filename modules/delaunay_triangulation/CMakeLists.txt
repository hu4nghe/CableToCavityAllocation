# Set the source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Create the static library
add_library(delaunay_triangulation STATIC ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(delaunay_triangulation
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)