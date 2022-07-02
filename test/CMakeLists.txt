
include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(test_calendar
    calendar_test.cpp)

target_include_directories(test_calendar PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(test_calendar gtest_main gmock gtest)

gtest_discover_tests(test_calendar)