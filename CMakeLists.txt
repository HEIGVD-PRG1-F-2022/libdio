cmake_minimum_required(VERSION 3.23)
project(libdio VERSION 0.1.9 DESCRIPTION "Input and display methods for PRG1-F")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(libdio STATIC src/display.cpp)
set_target_properties(libdio PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(libdio PUBLIC include)

add_executable(example example/main.cpp)
target_link_libraries(example libdio)
