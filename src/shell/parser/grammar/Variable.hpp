#ifndef LAB3_VARIABLE_HPP
#define LAB3_VARIABLE_HPP

#include <string>
#include "expressions.hpp"


class Variable: public Expression {
    std::string name;

public:
    Variable(const std::string& name): name(name) {}

protected:
    bool equals(const Expression& other) const {
        auto v = dynamic_cast<const Variable*>(&other);
        if (!v) return false;
        return name == v->name;
    }

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<Ptr> get_children() const {
        return std::vector<ExprPtr>();
    }

};


#endif //LAB3_VARIABLE_HPP
