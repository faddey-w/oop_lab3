#ifndef LAB3_STRINGLITERALTOKEN_HPP
#define LAB3_STRINGLITERALTOKEN_HPP


#include "../tokenization.h"


class StringLiteralToken: public Token {
    std::string value;
public:

    StringLiteralToken() : StringLiteralToken("") {}
    StringLiteralToken(const std::string& value): value(value) {}

    const std::string& get_type() const {
        static const std::string type_name("brace");
        return type_name;
    }

    const std::string& get_value() { return value; }

    int parse(const std::string&);
protected:
    bool _equals(const Token*) const;
};


int StringLiteralToken::parse(const std::string&) {
    return -1;
}


bool StringLiteralToken::_equals(const Token *) const {
    return false;
}


#endif //LAB3_STRINGLITERALTOKEN_HPP
