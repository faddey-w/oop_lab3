#include <vector>
#include "../tokens/AssignmentToken.hpp"
#include "../tokens/NameToken.hpp"
#include "../tokens/StringLiteralToken.hpp"
#include "../tokens/NumberLiteralToken.hpp"
#include "../tokens/ParenthesisToken.hpp"
#include "parse.h"
#include "expressions.hpp"

#include "Variable.hpp"
#include "FunctionCall.hpp"
#include "StringLiteral.hpp"
#include "NumberLiteral.hpp"


ExprPtr _parse_expr(const std::vector<Token::Ptr> &tokens, size_t &idx);


Statement parse(const std::vector<Token::Ptr> &tokens) {
    size_t idx = 0;

    // variable assignments should be first tokens is the statement
    std::vector<std::string> assignments;
    while(idx < tokens.size() &&
        tokens[idx]->get_type() == AssignmentToken().get_type()) {
        const auto t = Token::try_convert<AssignmentToken>(tokens[idx]);
        assignments.push_back(t->get_var_name());
        idx++;
    }

    const ExprPtr& expr = _parse_expr(tokens, idx);
    if (idx < tokens.size()) throw SyntaxError("unexpected tokens");

    return Statement(expr, assignments);
}


ExprPtr _parse_expr(const std::vector<Token::Ptr> &tokens, size_t &idx) {
    if (idx >= tokens.size()) throw SyntaxError("expected expression");

    if (const auto name_t = Token::try_convert<NameToken>(tokens[idx])) {
        // function call of variable
        const ParenthesisToken* open_par_tok = nullptr;
        if (idx+1 < tokens.size())
            open_par_tok = Token::try_convert<ParenthesisToken>(tokens[idx+1]);
        if (open_par_tok != nullptr && open_par_tok->is_open()) {
            // it should be the function call
            if (idx + 2 >= tokens.size()) throw SyntaxError("expected function arguments");

            // ok, we have parsed "function("
            // now parse the arguments
            idx += 2; // we parsed 2 tokens
            FunctionCall::Ptr fc(new FunctionCall(name_t->get_name()));
            while (const auto assign_tok = Token::try_convert<AssignmentToken>(tokens[idx])) {
                idx++;
                ExprPtr sub_expr = _parse_expr(tokens, idx);  // <- this changes idx
                fc->add_argument(assign_tok->get_var_name(), sub_expr);

                // we need to check for index bounds
                // otherwise it may cause index error on next while() check
                if (idx >= tokens.size()) throw SyntaxError("expected closing parenthesis");
            }
            const auto close_par_tor = Token::try_convert<ParenthesisToken>(tokens[idx]);
            if (!close_par_tor || close_par_tor->is_open()) {
                throw SyntaxError("expected closing parenthesis");
            }
            idx++; // closing parenthesis

            return fc;
        } else {
            // it is not a function call, so we assume that it is a variable
            idx++;
            return ExprPtr(new Variable(name_t->get_name()));
        }
    } else if (const auto slt = Token::try_convert<StringLiteralToken>(tokens[idx])) {
        idx++;
        return ExprPtr(new StringLiteral(slt->get_value()));
    } else if (const auto nlt = Token::try_convert<NumberLiteralToken>(tokens[idx])) {
        idx++;
        return ExprPtr(new NumberLiteral(nlt->get_value()));
    } else {
        throw SyntaxError("unexpected tokens");
    }
}

