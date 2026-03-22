cmake_minimum_required(VERSION 3.10)
project(GaluaField256 VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

# Add library
add_library(GaluaField256 STATIC
    src/Galua_Field_256.c
)

# Target include directories
target_include_directories(GaluaField256 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set properties for the library
set_target_properties(GaluaField256 PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Add test executable
add_executable(test_gf256
    test/test_Galua_Field_256.c
)

# Link libraries
target_link_libraries(test_gf256
    GaluaField256
    ${CHECK_LIBRARIES}
)

# Include directories for test
target_include_directories(test_gf256 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CHECK_INCLUDE_DIRS}
)

# Enable testing
enable_testing()

# Add test to CTest
add_test(NAME GF256_Field_Tests COMMAND test_gf256)

# Optional: Add main test runner if needed
option(BUILD_TESTS "Build test executable" ON)

# Print summary
message(STATUS "Build configuration:")
message(STATUS "  - Library: GaluaField256")
if(BUILD_TESTS)
    message(STATUS "  - Tests: enabled")
    message(STATUS "  - Check library: ${CHECK_LIBRARIES}")
endif()