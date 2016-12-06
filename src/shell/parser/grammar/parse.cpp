#include <vector>
#include "parse.h"
#include "expressions.hpp"

#include "Variable.hpp"
#include "FunctionCall.hpp"
#include "StringLiteral.hpp"
#include "NumberLiteral.hpp"


Statement parse(const std::vector<std::shared_ptr<Token> > &tokens) {
    return Statement(ExprPtr(new Variable("")), {});
}


