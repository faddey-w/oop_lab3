#ifndef LAB3_EXPRESSIONS_HPP
#define LAB3_EXPRESSIONS_HPP

#include <vector>
#include <memory>

class FunctionCall;
class Variable;
class NumberLiteral;
class StringLiteral;

class ExpressionVisitor {
public:
    virtual void visit(FunctionCall&) = 0;
    virtual void visit(Variable&) = 0;
    virtual void visit(NumberLiteral&) = 0;
    virtual void visit(StringLiteral&) = 0;
};

class Expression {
public:
    typedef std::shared_ptr<Expression> Ptr;

    virtual void accept(ExpressionVisitor& v) = 0;

    void traverse(ExpressionVisitor& v, bool acceptbefore) {
        if (acceptbefore) accept(v);
        for(auto child: get_children()) {
            child->traverse(v, acceptbefore);
        }
        if (!acceptbefore) accept(v);
    }

    virtual const std::vector<Ptr> get_children() const = 0;

    bool operator==(const Expression& other) const {
        return equals(other);
    }
    bool operator!=(const Expression& other) const {
        return !equals(other);
    }

protected:
    virtual bool equals(const Expression& other) const = 0;
};
typedef Expression::Ptr ExprPtr;


#endif //LAB3_EXPRESSIONS_HPP
