#ifndef LAB2_TESTSTRINGLITERALTOKEN_H
#define LAB2_TESTSTRINGLITERALTOKEN_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/StringLiteralToken.hpp>

using std::string;
using std::tuple;
using std::vector;


class TestStringLiteralToken : public CxxTest::TestSuite {
public:

    void test_comparison() {
        TS_ASSERT(StringLiteralToken("qwe") == StringLiteralToken("qwe"));
        TS_ASSERT(StringLiteralToken("123") != StringLiteralToken("qwe"));
        TS_ASSERT(StringLiteralToken("qwer") != StringLiteralToken("qwe"));
    }

    void test_correct_parsing() {
        vector<tuple<string, string, int> > cases{
            {"\"\" next tokens",          "",                 2},
            {"\"some data\" next tokens", "some data",        11},
            {"\"\\\"quoted\\\"\"",        "\"quoted\"",       12},
            {"\"with\\nnew\\nlines\"",    "with\nnew\nlines", 18},
            {"\"xxx\")",                  "xxx",              5},
        };
        for (const auto &item: cases) {
            int offset = -1;
            const std::string& input = std::get<0>(item);
            Token *token = Token::try_parse<StringLiteralToken>(input, offset);
            TSM_ASSERT(input, token != nullptr);
            if (token) {
                StringLiteralToken *coerced_token = dynamic_cast<StringLiteralToken *>(token);
                TSM_ASSERT(input, coerced_token != nullptr);
                if (coerced_token) {
                    TSM_ASSERT(input, *coerced_token == StringLiteralToken(std::get<1>(item)));
                    TSM_ASSERT(input, offset == std::get<2>(item));
                }
                delete token;
            }
        }
    }

    void test_failing_parsing() {
        vector<string> cases{
            "\"some data\"justafter", "", "\"not closed", " not opened\""
        };
        for(const auto &str: cases) {
            int offset = -1;
            Token *token = Token::try_parse<StringLiteralToken>(str, offset);
            TSM_ASSERT(str, token == nullptr);
            TSM_ASSERT(str, offset == -1);
        }
    }

};


#endif //LAB2_TESTSTRINGLITERALTOKEN_H
