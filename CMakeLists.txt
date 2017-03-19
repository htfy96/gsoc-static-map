cmake_minimum_required(VERSION 3.1)
project(static_map)

set(static_map-build_tests OFF CACHE BOOL "Whether to build tests")
# Enable C++14
set (CMAKE_CXX_STANDARD 14)

include_directories(include/)
set(static_map_header include/static_map/constexpr_string_view.hpp include/static_map/static_map.hpp)
if (static_map-build_tests)
	enable_testing()
	add_executable(static_map-test test/static_map.cpp ${static_map_header})
	add_test(static_map-test1 ${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test test_1\(\))
	add_test(static_map-test2 ${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test test_2\(\))
endif()
