cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_GLIBCXX_DEBUG -ftrapv)
add_compile_options(-Wall -Wextra -pedantic)

include(GoogleTest)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(algorithm-test)
include_directories(../src)
include_directories(.)
enable_testing()

# Math

add_executable(ModIntTest math/modint_test.cpp)
target_link_libraries(ModIntTest gtest gtest_main)
gtest_add_tests(TARGET ModIntTest)

add_executable(GcdTest math/gcd_test.cpp)
target_link_libraries(GcdTest gtest gtest_main)
gtest_add_tests(TARGET GcdTest)

add_executable(PrimeTest math/prime_test.cpp)
target_link_libraries(PrimeTest gtest gtest_main)
gtest_discover_tests(PrimeTest)

add_executable(FFTTest math/fft_test.cpp)
target_link_libraries(FFTTest gtest gtest_main)
gtest_add_tests(TARGET FFTTest)

add_executable(NFTTest math/nft_test.cpp)
target_link_libraries(NFTTest gtest gtest_main)
gtest_discover_tests(NFTTest)

add_executable(MatModTest math/matrix_mod_test.cpp)
target_link_libraries(MatModTest gtest gtest_main)
gtest_discover_tests(MatModTest)

add_executable(MatMod2Test math/matrix_mod2_test.cpp)
target_link_libraries(MatMod2Test gtest gtest_main)
gtest_discover_tests(MatMod2Test)

# Graph

add_executable(SCCTest graph/scc_test.cpp)
target_link_libraries(SCCTest gtest gtest_main)
gtest_add_tests(TARGET SCCTest)

add_executable(TWOSATTest graph/twosat_test.cpp)
target_link_libraries(TWOSATTest gtest gtest_main)
gtest_add_tests(TARGET TWOSATTest)

add_executable(MFTest graph/mf_test.cpp)
target_link_libraries(MFTest gtest gtest_main)
gtest_add_tests(TARGET MFTest)

add_executable(MCFTest graph/mcf_test.cpp)
target_link_libraries(MCFTest gtest gtest_main)
gtest_add_tests(TARGET MCFTest)

# Tree

add_executable(LCATest tree/lca_test.cpp)
target_link_libraries(LCATest gtest gtest_main)
gtest_discover_tests(LCATest)

# Datastructure

add_executable(FenwickTest datastructure/fenwick_test.cpp)
target_link_libraries(FenwickTest gtest gtest_main)
gtest_discover_tests(FenwickTest)

add_executable(WaveletTest datastructure/wavelet_test.cpp)
target_link_libraries(WaveletTest gtest gtest_main)
gtest_discover_tests(WaveletTest)

# String

add_executable(SATest string/suffixarray_test.cpp)
target_link_libraries(SATest gtest gtest_main)
gtest_discover_tests(SATest)

# Geo

add_executable(GeoTest geo/geo_test.cpp)
target_link_libraries(GeoTest gtest gtest_main)
gtest_add_tests(TARGET GeoTest)
