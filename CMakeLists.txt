cmake_minimum_required(VERSION 2.8)

project(Prac2)

set(MAIN_SOURCE ${PROJECT_SOURCE_DIR}/src/main.cpp)
set(CMAKE_CXX_STANDARD 11)
include_directories(./)

add_executable(main.cpp ${MAIN_SOURCE})

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FOR_TEST ${PROJECT_SOURCE_DIR}/test/main_test.cpp ${PROJECT_SOURCE_DIR}/test/my_tests.cpp)

enable_testing()
add_executable(CTest ${SOURCE_FOR_TEST})
target_link_libraries(CTest gtest gtest_main pthread)