
#include "meta.hpp"

#include "AssignmentToken.hpp"
#include "ParenthesisToken.hpp"
#include "NameToken.hpp"
#include "NumberLiteralToken.hpp"
#include "StringLiteralToken.hpp"


const std::vector<TokenMeta*> TokenMeta::objects{
    // ATTENTION: ORDER IS IMPORTANT
    new _TokenMetaImpl<ParenthesisToken>,
    new _TokenMetaImpl<StringLiteralToken>,
    new _TokenMetaImpl<NumberLiteralToken>,
    new _TokenMetaImpl<AssignmentToken>,
    new _TokenMetaImpl<NameToken>,
};
