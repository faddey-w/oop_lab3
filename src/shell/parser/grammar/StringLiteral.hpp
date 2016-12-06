#ifndef LAB3_STRINGLITERAL_HPP
#define LAB3_STRINGLITERAL_HPP

#include <string>
#include "expressions.hpp"


class StringLiteral: public Expression {
    std::string value;

public:
    StringLiteral(const std::string& value): value(value) {}

protected:
    bool equals(const Expression& other) const {
        auto v = dynamic_cast<const StringLiteral*>(&other);
        if (!v) return false;
        return value == v->value;
    }

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<Ptr> get_children() const {
        return std::vector<ExprPtr>();
    }

};

#endif //LAB3_STRINGLITERAL_HPP
