#ifndef LAB2_TESTSTRINGLITERALTOKEN_H
#define LAB2_TESTSTRINGLITERALTOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/StringLiteralToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestStringLiteralToken: public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(StringLiteralToken("qwe") == StringLiteralToken("qwe"));
        TS_ASSERT(StringLiteralToken("123") != StringLiteralToken("qwe"));
        TS_ASSERT(StringLiteralToken("qwer") != StringLiteralToken("qwe"));
    }

    void test_correct_parsing() {
        vector< tuple<string, string, int> > cases{
            {"\"\" next tokens", "", 2},
            {"\"some data\" next tokens", "some data", 11},
            {"\"\\\"quoted\\\"\"", "\"quoted\"", 12},
            {"\"with\\\nnew\\\nlines\"", "with\nnew\nlines", 18},
        };
        for(const auto &item: cases) {
            int offset = -1;
            Token *token = Token::try_parse<StringLiteralToken>(std::get<0>(item), offset);
            TS_ASSERT(token != nullptr);
            StringLiteralToken *coerced_token = dynamic_cast<StringLiteralToken*>(token);
            TS_ASSERT(coerced_token != nullptr);
            TS_ASSERT_EQUALS(*coerced_token, StringLiteralToken(std::get<1>(item)));
            TS_ASSERT_EQUALS(offset, std::get<2>(item));
            delete token;
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "\"some data\"justafter", "", "\"not closed", " not opened\""
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<StringLiteralToken>(str, offset);
            TS_ASSERT(token == nullptr);
            TS_ASSERT(offset == -1);
        }
    }

};


#endif //LAB2_TESTSTRINGLITERALTOKEN_H
