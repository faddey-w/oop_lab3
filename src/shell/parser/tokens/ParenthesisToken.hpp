#ifndef LAB3_PARENTHESISTOKEN_HPP
#define LAB3_PARENTHESISTOKEN_HPP

#include "../tokenization.h"


class ParenthesisToken: public Token {
    bool _is_open = true;
public:

    ParenthesisToken() : ParenthesisToken(true) {}
    ParenthesisToken(bool is_open): _is_open(is_open) {}

    const std::string& get_type() const {
        static const std::string type_name("parenthesis");
        return type_name;
    }

    bool is_open() const { return _is_open; }

    int parse(const std::string& str) {
        bool started_parsing = false;
        for(int idx = 0; idx < str.size(); ++idx) {
            char ch = str[idx];
            if (ch == '(' || ch == ')') {
                _is_open = (ch == '(');
                return idx+1;
            } else if(std::isspace(ch)) {
                if (started_parsing) return -1;
                started_parsing = true;
                continue;
            } else {
                return -1;
            }
        }
        return -1;
    }
protected:
    bool _equals(const Token* t) const {
        const auto other = Token::try_convert<ParenthesisToken>(t);
        if (!other) return false;
        return _is_open == other->_is_open;
    }
};

#endif // LAB3_PARENTHESISTOKEN_HPP
