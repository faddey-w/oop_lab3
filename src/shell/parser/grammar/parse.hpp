#ifndef LAB3_PARSER_H
#define LAB3_PARSER_H

#include <vector>
#include "../tokens/meta.hpp"
#include "expressions.hpp"
#include "Statement.hpp"


Statement parse(const std::vector<std::shared_ptr<Token> > &tokens) {
    return Statement(new Variable, {});
}


#endif //LAB3_PARSER_H
