#ifndef LAB3_STRINGLITERAL_HPP
#define LAB3_STRINGLITERAL_HPP

#include <string>
#include "expressions.hpp"


class StringLiteral: public Expression {
    std::string value;

public:
    typedef std::shared_ptr<StringLiteral> Ptr;
    StringLiteral(const std::string& value): value(value) {}

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<ExprPtr> get_children() const {
        return std::vector<ExprPtr>();
    }

    const std::string& get_value() const { return value; }

protected:
    bool equals(const Expression& other) const {
        auto v = dynamic_cast<const StringLiteral*>(&other);
        if (!v) return false;
        return value == v->value;
    }

};

#endif //LAB3_STRINGLITERAL_HPP
