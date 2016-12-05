#ifndef LAB2_TESTASSIGNMENTTOKEN_H
#define LAB2_TESTASSIGNMENTTOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/grammar/AssignmentToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestAssignmentToken: public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(AssignmentToken("qwe") == AssignmentToken("qwe"));
        TS_ASSERT(AssignmentToken("123") != AssignmentToken("qwe"));
        TS_ASSERT(AssignmentToken("qwer") != AssignmentToken("qwe"));
    }

    void test_correct_parsing() {
        vector< tuple<string, string, int> > cases{
            {" variable = expression", "variable", 11},
            {"variable = expression", "variable", 10},
            {" variable = ", "variable", 11},
            {"variable = two expressions", "variable", 10},
            {"v1 =", "v1", 4},
        };
        for(const auto &item: cases) {
            int offset = -1;
            Token *token = Token::try_parse<AssignmentToken>(std::get<0>(item), offset);
            TS_ASSERT(token != nullptr);
            TS_ASSERT_EQUALS(*token, AssignmentToken(std::get<1>(item)));
            TS_ASSERT_EQUALS(offset, std::get<2>(item));
            delete token;
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "variable", "", "1variable"
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<AssignmentToken>(str, offset);
            TS_ASSERT(token == nullptr);
            TS_ASSERT(offset == -1);
        }
    }

};


#endif //LAB2_TESTASSIGNMENTTOKEN_H
