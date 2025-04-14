add_executable(allocator_main src/main.cpp)
# Explicitly inherit includes from linked library

target_link_libraries(allocator_main
    PRIVATE
        csv_parser
        cable_allocator
        electronic_container
        electronic_component
)