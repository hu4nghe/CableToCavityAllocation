add_executable(module_tester src/module_tester.cpp)

target_link_libraries(module_tester
    PRIVATE
        electronic_container
        electronic_component
)