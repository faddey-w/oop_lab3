#ifndef LAB3_STRINGLITERALTOKEN_HPP
#define LAB3_STRINGLITERALTOKEN_HPP


#include "../tokenization.h"


class StringLiteralToken: public Token {
    std::string value;
public:

    StringLiteralToken() : StringLiteralToken("") {}
    StringLiteralToken(const std::string& value): value(value) {}

    const std::string& get_type() const {
        static const std::string type_name("string-literal");
        return type_name;
    }

    const std::string& get_value() const { return value; }

    int parse(const std::string& str) {
        size_t offset = str.find_first_not_of(" \n\t");
        if (str.size() <= offset+2) return -1;  // +2 characters for quotes, at least
        if (str[offset] != '\"') return -1;
        offset++;
        bool is_escaping = false;
        std::string buf;
        for(size_t idx = offset; idx < str.size(); idx++) {
            char ch = str[idx];
            if (is_escaping) {
                is_escaping = false;
                switch (ch) {
                    case 'n': buf.push_back('\n'); break;
                    case 't': buf.push_back('\t'); break;
                    case '\\': buf.push_back('\\'); break;
                    case '\"': buf.push_back('\"'); break;
                    default: return -1;
                }
            } else {
                if (ch == '\"') {
                    if (idx+1 < str.size() && !std::isspace(str[idx+1]))
                        return -1;
                    value = buf;
                    return int(idx+1);
                } else if (ch == '\\') {
                    is_escaping = true;
                    continue;
                } else {
                    buf.push_back(ch);
                }
            }
        }
        return -1;
    }
protected:
    bool _equals(const Token* t) const {
        const auto other = Token::try_convert<StringLiteralToken>(t);
        if (!other) return false;
        return value == other->value;
    }
};


#endif //LAB3_STRINGLITERALTOKEN_HPP
