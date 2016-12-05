//
// Created by faddey on 04.12.16.
//

#ifndef LAB3_TOKENS_HPP
#define LAB3_TOKENS_HPP

#include <string>
#include <vector>
#include <exception>


class SyntaxError: public std::runtime_error {
public:
    SyntaxError(const std::string &s): std::runtime_error(s) {}
    SyntaxError(): SyntaxError("") {}
};


class Token {
public:
    template<typename ConcreteToken>
    static Token* try_parse(const std::string &str, int &offset) {
        ConcreteToken *token = new ConcreteToken;
        try {
            offset = token->parse(str);
            if (offset < 0) {
                throw SyntaxError();
            }
            return token;
        } catch (SyntaxError &err) {
            delete token;
            return nullptr;
        }
    }

    bool operator==(const Token &other) const {
        if (get_type() != other.get_type()) {
            return false;
        }
        return _equals(&other);
    }
    bool operator!=(const Token &other) const {
        return !(*this == other);
    }

    virtual const std::string& get_type() const = 0;

    // May throw SyntaxError
    virtual int parse(const std::string&) = 0;

protected:
    virtual bool _equals(const Token*) const = 0;
};


std::vector<const Token*> tokenize(const std::string &str);


#endif //LAB3_TOKENS_HPP
