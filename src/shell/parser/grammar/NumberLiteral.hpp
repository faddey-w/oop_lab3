#ifndef LAB3_NUMBERLITERAL_HPP
#define LAB3_NUMBERLITERAL_HPP

#include <string>
#include "expressions.hpp"


class NumberLiteral: public Expression {
    int value;

public:
    NumberLiteral(int value): value(value) {}

protected:
    bool equals(const Expression& other) const {
        auto v = dynamic_cast<const NumberLiteral*>(&other);
        if (!v) return false;
        return value == v->value;
    }

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<Ptr>& get_children() const {
        return std::vector<ExprPtr>();
    }

};

#endif //LAB3_NUMBERLITERAL_HPP
