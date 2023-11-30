cmake_minimum_required(VERSION 3.3)

project(parser)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
    ../include
    ${GTEST_INCLUDE_DIRS}
)

add_executable(
  URL_Parser parser_test.cpp parser.h parser.cpp)

target_link_libraries(
  URL_Parser ${GTEST_LIBRARIES})

enable_testing()
add_test(URL_Parser "./TestFunctionUrl")
