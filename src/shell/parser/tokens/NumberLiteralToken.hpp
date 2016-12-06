#ifndef LAB3_NUMBERLITERALTOKEN_HPP
#define LAB3_NUMBERLITERALTOKEN_HPP


#include "../tokenization.h"


class NumberLiteralToken: public Token {
    int value;
public:

    NumberLiteralToken() : NumberLiteralToken(0) {}
    NumberLiteralToken(int value): value(value) {}

    const std::string& get_type() const {
        static const std::string type_name("brace");
        return type_name;
    }

    int get_value() { return value; }

    int parse(const std::string&) {
        return -1;
    }
protected:
    bool _equals(const Token*) const {
        return false;
    }
};


#endif //LAB3_NUMBERLITERALTOKEN_HPP
