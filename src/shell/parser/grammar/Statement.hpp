#ifndef LAB3_STATEMENT_HPP
#define LAB3_STATEMENT_HPP

#include <string>
#include "expressions.hpp"


class Statement {

    typedef std::vector<std::string> AssignmentsList;

    ExprPtr expr;
    AssignmentsList assignments;

public:
    Statement(
        const ExprPtr& expr,
        const AssignmentsList& assignments
    ): expr(expr), assignments(assignments) {};

    bool has_assignments() const { return assignments.size() > 0; }
    const AssignmentsList& get_assignments() const { return assignments; }
    const ExprPtr& get_expr() const { return expr; }

    bool operator==(const Statement& stmt) const {
        return *expr == *stmt.expr && assignments == stmt.assignments;
    }

};

#endif //LAB3_STATEMENT_HP
