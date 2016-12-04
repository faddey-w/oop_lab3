
#ifndef LAB2_META_HPP
#define LAB2_META_HPP

#include <string>
#include <array>


class TokenMeta {
public:
    static const std::array<const TokenMeta*> objects;
    const std::string& get_type() const = 0;
    const Token* try_parse(const std::string, unsigned &offset) const = 0;
};


template <class TokenType>
class _TokenMetaImpl: public TokenMeta {
    const TokenType &instance;

public:
    _TokenMetaImpl(): instance() {}

    const std::string& get_type() const {
        return instance.get_type();
    };

    const Token* try_parse(const std::string str, unsigned &offset) const {
        return TokenType::try_parse(str, offset);
    }
};


#include "grammar/AssignmentToken.hpp"
#include "grammar/BraceToken.hpp"
#include "grammar/NameToken.hpp"


const std::array<const TokenMeta*> TokenMeta::objects{
    // ATTENTION: ORDER IS IMPORTANT
    new _TokenMetaImpl<AssignmentToken>,
    new _TokenMetaImpl<BraceToken>,
    new _TokenMetaImpl<NameToken>,
};


#endif //LAB2_META_HPP
