#ifndef LAB2_TESTASSIGNMENTTOKEN_H
#define LAB2_TESTASSIGNMENTTOKEN_H

#include <cxxtest/TestSuite.h>
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
            {" 12 ", 12, 3},
            {"-105 ", -105, 4},
            {" - 1 ", -1, 4},
            {"10 000", 10, 2},
            {" 00000 ", 0, 6},
        };
        for(const auto &item: cases) {
            int offset = -1;
            Token *token = Token::try_parse<NumberLiteralToken>(std::get<0>(item), offset);
            TS_ASSERT(token != nullptr);
            TS_ASSERT_EQUALS(*token, NumberLiteralToken(std::get<1>(item)));
            TS_ASSERT_EQUALS(offset, std::get<2>(item));
            delete token;
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "--1", "", "1.0", "1f "
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<NumberLiteralToken>(str, offset);
            TS_ASSERT(token == nullptr);
            TS_ASSERT(offset == -1);
        }
    }

};


#endif //LAB2_TESTASSIGNMENTTOKEN_H
