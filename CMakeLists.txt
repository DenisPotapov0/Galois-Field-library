cmake_minimum_required(VERSION 3.10)
project(GaloisField256 VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(GaloisField256 STATIC src/Galois_Field_256.c)
target_include_directories(GaloisField256 PUBLIC src)

add_executable(test_gf256 test/test_Galois_Field_256.c)
target_include_directories(test_gf256 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_library(CUNIT_LIB cunit)
find_path(CUNIT_INCLUDE CUnit/CUnit.h)
target_link_libraries(test_gf256 PRIVATE GaloisField256 ${CUNIT_LIB})
target_include_directories(test_gf256 PRIVATE ${CUNIT_INCLUDE})

include(CTest)
add_test(NAME GF256_Field_Tests COMMAND test_gf256)
