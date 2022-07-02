cmake_minimum_required(VERSION 3.18)

project(Application)

set(APPLICATION_SOURCES
  app_main.cpp
  interface.cpp
  month_element.cpp
  )

add_executable(calendar ${APPLICATION_SOURCES})
set_property(TARGET calendar PROPERTY CXX_STANDARD 17)

add_custom_command(TARGET calendar POST_BUILD
                   COMMAND cp -r ${CMAKE_SOURCE_DIR}/Config ${CMAKE_BINARY_DIR}
) 

# Must enable testing before the subdirectory
enable_testing()
add_subdirectory(test)

