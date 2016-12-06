#ifndef LAB3_TESTTOKENSPARSING_HPP
#define LAB3_TESTTOKENSPARSING_HPP

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/grammar/parse.h>
#include <src/shell/parser/grammar/Variable.hpp>
#include <src/shell/parser/grammar/FunctionCall.hpp>
#include <src/shell/parser/grammar/StringLiteral.hpp>
#include <src/shell/parser/grammar/NumberLiteral.hpp>


class TestTokensParsing: public CxxTest::TestSuite {
public:

    void test_simple_variable() {
        std::vector<Token::Ptr> input_tokens = tokenize(
            "some_variable"
        );
        Statement expected_statement({
            ExprPtr(new Variable("some_variable")),
            {}
        });
        TS_ASSERT_EQUALS(expected_statement, parse(input_tokens));
    }

    void test_simple_function_call() {
        std::vector<Token::Ptr> input_tokens = tokenize(
            "function(arg=val)"
        );
        Statement expected_statement{
            ExprPtr(new FunctionCall(
                "function", {
                    {"arg", ExprPtr(new Variable("val"))}
                }
            )),
            {}
        };
        TS_ASSERT_EQUALS(expected_statement, parse(input_tokens));
    }

    void test_simple_assignment() {
        std::vector<Token::Ptr> input_tokens = tokenize(
            "variable = value"
        );
        Statement expected_statement{
            ExprPtr(new Variable("value")),
            {"variable"}
        };
        TS_ASSERT_EQUALS(expected_statement, parse(input_tokens));
    }

    void test_multiple_assignments() {
        std::vector<Token::Ptr> input_tokens = tokenize(
            "variable1 = variable2 = variable3 = value"
        );
        Statement expected_statement{
            ExprPtr(new Variable("value")),
            {"variable1", "variable2", "variable3"}
        };
        TS_ASSERT_EQUALS(expected_statement, parse(input_tokens));
    }

    void test_complex_function_call_with_assignment() {
        std::vector<Token::Ptr> input_tokens = tokenize(
            "result = function1(arg=value param=function2(x=\"literal\" y=1))"
        );
        Statement expected_statement{
            ExprPtr(new FunctionCall(
                "function1", {
                    {"arg", ExprPtr(new Variable("value"))},
                    {"param", ExprPtr(new FunctionCall(
                        "function2", {
                            {"x", ExprPtr(new StringLiteral("literal"))},
                            {"y", ExprPtr(new NumberLiteral(1))}
                        }
                    ))},
                }
            )),
            {"result"}
        };
        TS_ASSERT_EQUALS(expected_statement, parse(input_tokens));
    }

};



#endif //LAB3_TESTTOKENSPARSING_HPP
