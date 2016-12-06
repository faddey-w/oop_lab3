
#ifndef LAB2_META_HPP
#define LAB2_META_HPP

#include <string>
#include <array>
#include "../tokenization.h"


class TokenMeta {
public:
    static const std::vector<TokenMeta*> objects;
    virtual const std::string& get_type() const = 0;
    virtual Token* try_parse(const std::string&, int &offset) const = 0;
};


template <class TokenType>
class _TokenMetaImpl: public TokenMeta {
    const TokenType instance;

public:
    _TokenMetaImpl(): instance() {}

    const std::string& get_type() const {
        return instance.get_type();
    };

    Token* try_parse(const std::string &str, int &offset) const {
        return Token::try_parse<TokenType>(str, offset);
    }
};

#endif //LAB2_META_HPP
