#ifndef LAB2_TESTASSIGNMENTTOKEN_H
#define LAB2_TESTASSIGNMENTTOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/NameToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestNameToken: public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(NameToken("qwe") == NameToken("qwe"));
        TS_ASSERT(NameToken("123") != NameToken("qwe"));
        TS_ASSERT(NameToken("qwer") != NameToken("qwe"));
    }

    void test_correct_parsing() {
        vector< tuple<string, string, int> > cases{
            {" variable = expression", "variable", 9},
            {"var = expression", "var", 8},
            {"variable_1", "variable_1", 10},
            {"variable(expr)", "variable", 8},
            {"numbers123 next", "numbers123", 10},
        };
        for(const auto &item: cases) {
            int offset = -1;
            Token *token = Token::try_parse<NameToken>(std::get<0>(item), offset);
            TS_ASSERT(token != nullptr);
            TS_ASSERT_EQUALS(*token, NameToken(std::get<1>(item)));
            TS_ASSERT_EQUALS(offset, std::get<2>(item));
            delete token;
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "", "1variable", "(variable)", "=var", "var?",
            "var&", "var#", "var!", "var-"
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<NameToken>(str, offset);
            TS_ASSERT(token == nullptr);
            TS_ASSERT(offset == -1);
        }
    }

};


#endif //LAB2_TESTASSIGNMENTTOKEN_H
