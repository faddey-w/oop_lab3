#ifndef LAB3_TESTTOKENIZING_H
#define LAB3_TESTTOKENIZING_H

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
        const vector<Token::Ptr> expected_tokens({
            Token::Ptr(new AssignmentToken("variable")),
            Token::Ptr(new AssignmentToken("another")),
            Token::Ptr(new NameToken("function")),
            Token::Ptr(new ParenthesisToken(true)),
            Token::Ptr(new AssignmentToken("arg1")),
            Token::Ptr(new NameToken("value")),
            Token::Ptr(new AssignmentToken("arg2")),
            Token::Ptr(new NameToken("subcall")),
            Token::Ptr(new ParenthesisToken(true)),
            Token::Ptr(new AssignmentToken("argument")),
            Token::Ptr(new NameToken("another_value")),
            Token::Ptr(new ParenthesisToken(false)),
            Token::Ptr(new ParenthesisToken(false))
        });
        auto actual_tokens = tokenize(statement);
        TS_ASSERT(expected_tokens.size() == actual_tokens.size());
        for(int i = 0; i < expected_tokens.size(); ++i) {
            TS_ASSERT(*expected_tokens[i] == *actual_tokens[i]);
        }
    }

    void test_failing_tokenizing() {
        const string statement = "variable = another = 1_some wrong = = = tokens";
        TS_ASSERT_THROWS(tokenize(statement), SyntaxError);
    }

};

#endif //LAB3_TESTTOKENIZING_H
