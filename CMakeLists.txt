project(lab2)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)


include_directories(libs)


aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})


find_package(CxxTest)
set(CXXTEST_TESTGEN_INTERPRETER bash)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
include_directories(${CXXTEST_INCLUDE_DIR})
enable_testing()
CXXTEST_ADD_TEST(tests testrunner.cpp
        ${TESTS_DIR}/TestConstructionWorker.h
        ${SRC_LIST})

