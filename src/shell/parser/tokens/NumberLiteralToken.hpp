#ifndef LAB3_NUMBERLITERALTOKEN_HPP
#define LAB3_NUMBERLITERALTOKEN_HPP


#include "../tokenization.h"


class NumberLiteralToken: public Token {
    int value;
public:

    NumberLiteralToken() : NumberLiteralToken(0) {}
    NumberLiteralToken(int value): value(value) {}

    const std::string& get_type() const {
        static const std::string type_name("number-literal");
        return type_name;
    }

    int get_value() const { return value; }

    int parse(const std::string& str) {
        bool started_parsing = false;
        bool digits_found = false;
        bool is_positive = true;
        int value = 0;
        for(int idx = 0; idx < str.size(); idx++) {
            char ch = str[idx];
            if (std::isdigit(ch)) {
                digits_found = true;
                started_parsing = true;
                value = (10*value + (ch-'0'));
            } else if (ch == '-') {
                if (started_parsing) return -1;
                started_parsing = true;
                is_positive = false;
            } else {
                if (digits_found) {
                    this->value = is_positive? value : -value;
                    return idx;
                }
                if (!std::isspace(ch)) break;
            }
        }
        if (digits_found) {
            this->value = value;
            return int(str.size());
        }
        return -1;
    }
protected:
    bool _equals(const Token* t) const {
        const auto other = Token::try_convert<NumberLiteralToken>(t);
        if (!other) return false;
        return value == other->value;
    }
};


#endif //LAB3_NUMBERLITERALTOKEN_HPP
