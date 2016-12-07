#ifndef LAB2_TESTASSIGNMENTTOKEN_H
#define LAB2_TESTASSIGNMENTTOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/AssignmentToken.hpp>

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
            {"var_1 = expression", "var_1", 7},
            {" variable = ", "variable", 11},
            {"variable = two expressions", "variable", 10},
            {"v1 =", "v1", 4},
            {"dense=nexttoken", "dense", 6},
            {"sparse   =    nexttoken", "sparse", 10},
        };
        for(const auto &item: cases) {
            int offset = -1;
            const std::string& input = std::get<0>(item);
            Token *token = Token::try_parse<AssignmentToken>(input, offset);
            TSM_ASSERT(input, token != nullptr);
            if (token) {
                AssignmentToken *assign_token = dynamic_cast<AssignmentToken *>(token);
                TS_ASSERT(assign_token != nullptr);
                if (assign_token) {
                    TS_ASSERT(*assign_token == AssignmentToken(std::get<1>(item)));
                    TS_ASSERT(offset == std::get<2>(item));
                }
                delete token;
            }
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "variable", "", "1variable", "= expr"
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
