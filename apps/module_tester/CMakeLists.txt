add_executable(module_tester src/module_tester.cpp)

target_link_libraries(module_tester
    PRIVATE
        cable_allocator
        electronic_container
        electronic_component
)