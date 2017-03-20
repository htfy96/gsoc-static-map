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
	add_test(static_map-test-int-key-constexpr
			${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test "test_int_key_constexpr\\\\(\\\\)")
	add_test(static_map-test-int-key-nonconstexpr
			${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test "test_int_key_nonconstexpr\\\\(\\\\)")
    add_test(static_map-test-int-key-assignment
            ${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test "test_int_key_assignment\\\\(\\\\)")
	add_test(static_map-test-string-view-key-constexpr
			${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test "test_string_view_key_constexpr\\\\(\\\\)")
	add_test(static_map-test-string-view-key-nonconstexpr
			${static_map_SOURCE_DIR}/check-all.sh ${static_map_BINARY_DIR}/static_map-test "test_string_view_key_nonconstexpr\\\\(\\\\)")
endif()
