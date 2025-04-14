# py_module/CMakeLists.txt

# === Step 1: Python & pybind11 detection ===
if (VIRTUAL_ENV)
    message(STATUS "✅ Using virtual environment: ${VIRTUAL_ENV}")

    # 1. Find Python interpreter and development libraries
    find_package(Python REQUIRED COMPONENTS Interpreter Development)

    # 2. Set pybind11 path manually using the virtualenv path
    set(PYBIND11_DIR "${VIRTUAL_ENV}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/pybind11/share/cmake/pybind11")
    message(STATUS "🔍 Looking for pybind11 in: ${PYBIND11_DIR}")

    set(PYBIND11_FINDPYTHON ON)
    find_package(pybind11 REQUIRED PATHS ${PYBIND11_DIR} NO_DEFAULT_PATH)

    # === Step 2: Source files ===
    file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

    # === Step 3: Define the pybind11 module ===
    pybind11_add_module(cable_allocator_pybind11 ${SOURCES})

    # === Step 4: Link other dependencies ===
    target_link_libraries(cable_allocator_pybind11
        PRIVATE
            electronic_container
            electronic_component
            cable_allocator
    )

    # === Step 5: Include directories ===
    target_include_directories(cable_allocator_pybind11 
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${pybind11_INCLUDE_DIRS}
    )

    # === Step 6: Output path (.so file) ===
    set_target_properties(cable_allocator_pybind11 
        PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/python_modules"
            PREFIX ""
            SUFFIX ".so"
    )

    # === Step 7: Install to site-packages of virtualenv ===
    install(TARGETS cable_allocator_pybind11 
        DESTINATION "${VIRTUAL_ENV}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages"
    )
else()
    message(WARNING "❌ VIRTUAL_ENV is not defined. Skipping Python module build.")
endif()
