//
// Created by faddey on 06.12.16.
//

#ifndef LAB3_TESTTOKENIZATION_H
#define LAB3_TESTTOKENIZATION_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokenization.h>
#include <src/shell/parser/tokens/AssignmentToken.hpp>
#include <src/shell/parser/tokens/NameToken.hpp>
#include <src/shell/parser/tokens/ParenthesisToken.hpp>

using std::string;
using std::tuple;
using std::vector;
using std::shared_ptr;


class TestTokenizing: public CxxTest::TestSuite {
public:
    void test_successful_tokenizing() {
        const string statement = "variable = another = "
            "function(arg1=value arg2=subcall(argument=another_value))";
        const vector<shared_ptr<Token> > expected_tokens{
            new AssignmentToken("variable"),
            new AssignmentToken("another"),
            new NameToken("function"),
            new ParenthesisToken(true),
            new AssignmentToken("arg1"),
            new NameToken("value"),
            new AssignmentToken("arg2"),
            new NameToken("subcall"),
            new ParenthesisToken(true),
            new AssignmentToken("argument"),
            new NameToken("another_value"),
            new ParenthesisToken(false),
            new ParenthesisToken(false)
        };
        auto actual_tokens = tokenize(statement);
        TS_ASSERT_EQUALS(expected_tokens.size(), actual_tokens.size());
        for(int i = 0; i < expected_tokens.size(); ++i) {
            TS_ASSERT_EQUALS(expected_tokens[i], actual_tokens[i]);
        }
    }

    void test_failing_tokenizing() {
        const string statement = "variable = another = 1_some wrong = = = tokens";
        TS_ASSERT_THROWS(tokenize(statement), SyntaxError());
    }

};

#endif //LAB3_TESTTOKENIZATION_H
