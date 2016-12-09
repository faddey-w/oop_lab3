#ifndef LAB2_TESTNUMBERLITERALTOKEN_H
#define LAB2_TESTNUMBERLITERALTOKEN_H

#include <cxxtest/TestSuite.h>
#include <tests/utils.h>
#include <src/shell/parser/tokens/NumberLiteralToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestNumberLiteralToken: public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(NumberLiteralToken(1) == NumberLiteralToken(1));
        TS_ASSERT(NumberLiteralToken(10) != NumberLiteralToken(20));
    }

    void test_correct_parsing() {
        vector< tuple<string, int, int> > cases{
            {"10", 10, 2},
            {" 12 ", 12, 3},
            {"-105 ", -105, 4},
            {" - 1 ", -1, 4},
            {"10 000", 10, 2},
            {" 00000 ", 0, 6},
            {" 5) ", 5, 2},
            {"1f", 1, 1},
            {"2.5", 2, 1}
        };
        for(const auto &item: cases) {
            int offset = -1;
            const std::string& input = std::get<0>(item);
            Token *token = Token::try_parse<NumberLiteralToken>(input, offset);
            TSM_ASSERT(input, token != nullptr);
            if (token) {
                NumberLiteralToken *coerced_token = dynamic_cast<NumberLiteralToken *>(token);
                TSM_ASSERT(input, coerced_token != nullptr);
                if (coerced_token) {
                    TSM_ASSERT(input, *coerced_token == NumberLiteralToken(std::get<1>(item)));
                    TSM_ASSERT(input, offset == std::get<2>(item));
                }
                delete token;
            }
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "--1", ""
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<NumberLiteralToken>(str, offset);
            TSM_ASSERT(str, token == nullptr);
            TSM_ASSERT(str, offset == -1);
        }
    }

};


#endif //LAB2_TESTNUMBERLITERALTOKEN_H
