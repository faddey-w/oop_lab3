#ifndef LAB3_VARIABLE_HPP
#define LAB3_VARIABLE_HPP

#include <string>
#include "expressions.hpp"


class Variable: public Expression {
    std::string name;

public:
    typedef std::shared_ptr<Variable> Ptr;
    Variable(const std::string& name): name(name) {}

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<ExprPtr> get_children() const {
        return std::vector<ExprPtr>();
    }

    const std::string& get_name() const { return name; }

protected:
    bool equals(const Expression& other) const {
        auto v = dynamic_cast<const Variable*>(&other);
        if (!v) return false;
        return name == v->name;
    }

};


#endif //LAB3_VARIABLE_HPP
