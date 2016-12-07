#ifndef LAB2_TESTPARENTHESISTOKEN_H
#define LAB2_TESTPARENTHESISTOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/ParenthesisToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestParenthesisToken : public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(ParenthesisToken(true) == ParenthesisToken(true));
        TS_ASSERT(ParenthesisToken(false) == ParenthesisToken(false));
        TS_ASSERT(ParenthesisToken(true) != ParenthesisToken(false));
    }

    void test_correct_parsing() {
        vector<tuple<string, bool, int> > cases{
            {" (",          true,  2},
            {"(expression", true,  1},
            {")",           false, 1},
            {"()",          true,  1},
            {")(",          false, 1},
        };
        for (const auto &item: cases) {
            int offset = -1;
            Token *token = Token::try_parse<ParenthesisToken>(std::get<0>(item), offset);
            TS_ASSERT(token != nullptr);
            if (token) {
                ParenthesisToken *coerced_token = dynamic_cast<ParenthesisToken *>(token);
                if (coerced_token) {
                    TS_ASSERT(coerced_token != nullptr);
                    TS_ASSERT(*coerced_token == ParenthesisToken(std::get<1>(item)));
                    TS_ASSERT(offset == std::get<2>(item));
                }
                delete token;
            }
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "expression(", "", "=("
        };
        for (const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<ParenthesisToken>(str, offset);
            TS_ASSERT(token == nullptr);
            TS_ASSERT(offset == -1);
        }
    }

};


#endif //LAB2_TESTPARENTHESISTOKEN_H
