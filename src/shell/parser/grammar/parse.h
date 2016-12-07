#ifndef LAB3_PARSE_HPP
#define LAB3_PARSE_HPP

#include <vector>
#include "../tokens/meta.hpp"
#include "Statement.hpp"


Statement parse(const std::vector<Token::Ptr> &tokens);


#endif //LAB3_PARSE_HPP
