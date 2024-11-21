

# This section compiles the unit tests ------------------------------------
find_package(GTest CONFIG REQUIRED COMPONENTS GTest)

SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage -O0 -g")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include(GoogleTest)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(test_month_element
    month_test.cpp
    ${CMAKE_SOURCE_DIR}/month_element.cpp
)

add_executable(test_util
    util_test.cpp
    ${CMAKE_SOURCE_DIR}/util.cpp
)

# This test includes a template, so no production source is required
add_executable(test_gregorian
    gregorian_test.cpp
)

target_link_libraries(test_month_element gmock gtest gtest_main) 
target_link_libraries(test_util gmock gtest gtest_main)
target_link_libraries(test_gregorian gmock gtest gtest_main)

gtest_discover_tests(test_month_element)
gtest_discover_tests(test_util)
gtest_discover_tests(test_gregorian)

# This section adds coverage the unit tests -------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CodeCoverage)
setup_target_for_coverage_lcov(
    NAME coverage
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    EXCLUDE
      test
      /usr
    EXECUTABLE ctest
    LCOV_ARGS
      --ignore-errors inconsistent
      --rc branch_coverage=1
    GENHTML_ARGS
      --branch-coverage
      --filter branch
      --filter brace
      --dark-mode
    DEPENDENCIES
      test_month_element
      test_util
      test_gregorian 
)
