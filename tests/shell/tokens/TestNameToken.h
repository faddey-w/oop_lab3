#ifndef LAB2_TESTNAMETOKEN_H
#define LAB2_TESTNAMETOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/NameToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestNameToken : public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(NameToken("qwe") == NameToken("qwe"));
        TS_ASSERT(NameToken("123") != NameToken("qwe"));
        TS_ASSERT(NameToken("qwer") != NameToken("qwe"));
    }

    void test_correct_parsing() {
        vector<tuple<string, string, int> > cases{
            {" variable = expression", "variable",   9},
            {"var = expression",       "var",        3},
            {"variable_1",             "variable_1", 10},
            {"variable(expr)",         "variable",   8},
            {"variable)",              "variable",   8},
            {"numbers123 next",        "numbers123", 10},
        };
        for (const auto &item: cases) {
            int offset = -1;
            const std::string& input = std::get<0>(item);
            Token *token = Token::try_parse<NameToken>(input, offset);
            TSM_ASSERT(input, token != nullptr);
            if (token) {
                NameToken *coerced_token = dynamic_cast<NameToken *>(token);
                TSM_ASSERT(input, coerced_token != nullptr);
                if (coerced_token) {
                    TSM_ASSERT(input, *coerced_token == NameToken(std::get<1>(item)));
                    TSM_ASSERT(input, offset == std::get<2>(item));
                }
                delete token;
            }
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "", "1variable", "(variable)", "=var", "?var",
            "&var", "#var", "!var", "-var"
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<NameToken>(str, offset);
            TSM_ASSERT(str, token == nullptr);
            TS_ASSERT(offset == -1);
        }
    }

};


#endif //LAB2_TESTNAMETOKEN_H
