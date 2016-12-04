//
// Created by faddey on 04.12.16.
//

#ifndef LAB3_TOKENS_HPP
#define LAB3_TOKENS_HPP

#include <string>
#include <vector>
#include <exception>


class SyntaxError: public std::runtime_error {
//    SyntaxError()
};


class Token {
public:
    template<typename ConcreteToken>
    static Token* try_parse(std::string str, unsigned &offset) {
        ConcreteToken *token = new ConcreteToken;
        try {
            token._parse(str, offset);
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

    virtual std::string get_type() const = 0;

protected:
    // May throw SyntaxError
    virtual void _parse(std::string, unsigned &offset) = 0;

    virtual bool _equals(const Token*) const = 0;
};


std::vector<Token*> tokenize(std::string str);


#endif //LAB3_TOKENS_HPP
