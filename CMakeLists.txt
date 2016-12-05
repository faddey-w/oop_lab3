project(lab3)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)


include_directories(libs)


set(SRC_LIST
        src/shell/parser/grammar/meta.hpp
        src/shell/parser/grammar/AssignmentToken.hpp
        src/shell/parser/grammar/BraceToken.hpp
        src/shell/parser/grammar/NameToken.hpp
        src/shell/parser/tokenization.h
        src/shell/parser/tokenize.cpp
)
set(TESTS_LIST
        tests/shell/grammar/TestAssignmentToken.h
        tests/shell/grammar/TestTokensMeta.h
        tests/utils.h
)
set(ALL_CODE ${TESTS_LIST} ${SRC_LIST})
add_executable(manage_company ${SRC_LIST})


find_package(CxxTest)
set(CXXTEST_TESTGEN_INTERPRETER bash)
include_directories(${CXXTEST_INCLUDE_DIR})
enable_testing()

FUNCTION(PREPEND var prefix)
    SET(listVar "")
    FOREACH(f ${ARGN})
        LIST(APPEND listVar "${prefix}/${f}")
    ENDFOREACH(f)
    SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

PREPEND(PATHS_FOR_CXXTEST ${CMAKE_CURRENT_SOURCE_DIR} ${ALL_CODE})
CXXTEST_ADD_TEST(tests testrunner.cpp ${PATHS_FOR_CXXTEST})
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
