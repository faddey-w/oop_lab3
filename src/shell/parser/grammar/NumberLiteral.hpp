#ifndef LAB3_NUMBERLITERAL_HPP
#define LAB3_NUMBERLITERAL_HPP

#include <string>
#include "expressions.hpp"


class NumberLiteral: public Expression {
    int value;

public:
    typedef std::shared_ptr<NumberLiteral> Ptr;
    NumberLiteral(int value): value(value) {}

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<ExprPtr> get_children() const {
        return std::vector<ExprPtr>();
    }

protected:
    bool equals(const Expression& other) const {
        auto v = dynamic_cast<const NumberLiteral*>(&other);
        if (!v) return false;
        return value == v->value;
    }

};

#endif //LAB3_NUMBERLITERAL_HPP
