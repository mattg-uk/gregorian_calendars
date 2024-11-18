

include(GoogleTest)
find_package(GTest CONFIG REQUIRED COMPONENTS GTest)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(test_month_element
    month_test.cpp
    ${CMAKE_SOURCE_DIR}/month_element.cpp
)

add_executable(test_util
    util_test.cpp
    ${CMAKE_SOURCE_DIR}/util.cpp
)

target_link_libraries(test_month_element gmock gtest gtest_main)
target_link_libraries(test_util gmock gtest gtest_main)

gtest_discover_tests(test_month_element)
gtest_discover_tests(test_util)
