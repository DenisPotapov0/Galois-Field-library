cmake_minimum_required(VERSION 3.10)
project(GaloisField256 VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Add library
add_library(GaloisField256 STATIC
    src/Galois_Field_256.c
)

# Target include directories
target_include_directories(GaloisField256 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set properties for the library
set_target_properties(GaloisField256 PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Add test executable
add_executable(test_gf256
    test/test_Galois_Field_256.c
)

# Link libraries
target_link_libraries(test_gf256
    GaloisField256
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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(GCOVR_EXECUTABLE gcovr)
    
    if(GCOVR_EXECUTABLE)
        add_custom_target(coverage_text
            COMMAND ${CMAKE_COMMAND} -E echo "=== Coverage Report ==="
            COMMAND ${GCOVR_EXECUTABLE} --root ${CMAKE_SOURCE_DIR} 
                     --exclude "test/.*" 
                     --exclude ".*_test.*"
                     --print-summary
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating text coverage report"
        )
        
        add_custom_target(coverage_html
            COMMAND ${GCOVR_EXECUTABLE} --root ${CMAKE_SOURCE_DIR} 
                     --exclude "test/.*"
                     --exclude ".*_test.*"
                     --html --html-details -o coverage_report.html
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage report: ${CMAKE_BINARY_DIR}/coverage_report.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating HTML coverage report"
        )
        
        add_custom_target(coverage
            DEPENDS coverage_text coverage_html
            COMMENT "Generating all coverage reports"
        )
        
    else()
        message(WARNING "gcovr not found. Install with: pip install gcovr")
        
        find_program(LCOV_EXECUTABLE lcov)
        find_program(GENHTML_EXECUTABLE genhtml)
        
        if(LCOV_EXECUTABLE AND GENHTML_EXECUTABLE)
            add_custom_target(coverage
                COMMAND ${LCOV_EXECUTABLE} --capture --directory . 
                         --output-file coverage.info
                COMMAND ${LCOV_EXECUTABLE} --remove coverage.info 
                         '/usr/*' '*/test/*' --output-file coverage.info
                COMMAND ${GENHTML_EXECUTABLE} coverage.info 
                         --output-directory coverage_html
                COMMAND ${CMAKE_COMMAND} -E echo "Coverage report: ${CMAKE_BINARY_DIR}/coverage_html/index.html"
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating coverage report with lcov"
            )
        else()
            message(WARNING "Neither gcovr nor lcov found. Install with: pip install gcovr")
        endif()
    endif()
endif()

# Optional: Add main test runner if needed
option(BUILD_TESTS "Build test executable" ON)

# Optional: Add main test runner if needed
option(BUILD_TESTS "Build test executable" ON)

# Print summary
message(STATUS "Build configuration:")
message(STATUS "  - Library: GaloisField256")
if(BUILD_TESTS)
    message(STATUS "  - Tests: enabled")
    message(STATUS "  - Check library: ${CHECK_LIBRARIES}")
endif()
