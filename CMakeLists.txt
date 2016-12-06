project(lab3)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)


include_directories(libs)


set(SRC_LIST
        src/shell/parser/tokenization.h
        src/shell/parser/tokenize.cpp

        src/shell/parser/tokens/meta.hpp
        src/shell/parser/tokens/meta.cpp
        src/shell/parser/tokens/AssignmentToken.hpp
        src/shell/parser/tokens/ParenthesisToken.hpp
        src/shell/parser/tokens/NameToken.hpp
        src/shell/parser/tokens/StringLiteralToken.hpp
        src/shell/parser/tokens/NumberLiteralToken.hpp

        src/shell/parser/grammar/expressions.hpp
        src/shell/parser/grammar/Statement.hpp
        src/shell/parser/grammar/FunctionCall.hpp
        src/shell/parser/grammar/Variable.hpp
        src/shell/parser/grammar/StringLiteral.hpp
        src/shell/parser/grammar/NumberLiteral.hpp
        src/shell/parser/grammar/parse.h
        src/shell/parser/grammar/parse.cpp
)
set(TESTS_LIST
        tests/shell/tokens/TestAssignmentToken.h
        tests/shell/tokens/TestParenthesisToken.h
        tests/shell/tokens/TestNameToken.h
        tests/shell/tokens/TestNumberLiteralToken.h
        tests/shell/tokens/TestStringLiteralToken.h

        tests/shell/tokens/TestTokensMeta.h
        tests/shell/tokens/TestTokenizing.h

        tests/shell/grammar/TestFunctionCall.h
        tests/shell/grammar/TestTokensParsing.hpp

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
