
#ifndef LAB2_META_HPP
#define LAB2_META_HPP

#include <string>
#include <array>


class TokenMeta {
public:
    static const std::vector<TokenMeta*> objects;
    virtual const std::string& get_type() const = 0;
    virtual const Token* try_parse(const std::string&, int &offset) const = 0;
};


template <class TokenType>
class _TokenMetaImpl: public TokenMeta {
    const TokenType instance;

public:
    _TokenMetaImpl(): instance() {}

    const std::string& get_type() const {
        return instance.get_type();
    };

    const Token* try_parse(const std::string &str, int &offset) const {
        return Token::try_parse<TokenType>(str, offset);
    }
};


#include "AssignmentToken.hpp"
#include "BraceToken.hpp"
#include "NameToken.hpp"


const std::vector<TokenMeta*> TokenMeta::objects{
    // ATTENTION: ORDER IS IMPORTANT
    new _TokenMetaImpl<AssignmentToken>,
    new _TokenMetaImpl<BraceToken>,
    new _TokenMetaImpl<NameToken>,
};


#endif //LAB2_META_HPP
