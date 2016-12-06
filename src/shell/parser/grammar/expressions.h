#ifndef LAB3_EXPRESSIONS_H
#define LAB3_EXPRESSIONS_H

#include <vector>

class FunctionCall;
class Variable;

class ExpressionVisitor {
public:
    virtual void visit(FunctionCall&) = 0;
    virtual void visit(Variable&) = 0;
};


class Expression {
public:
    virtual void accept(ExpressionVisitor& v) = 0;

    void traverse(ExpressionVisitor& v) {
        accept(v);
        for(auto child: get_children()) {
            child->traverse(v);
        }
    }

protected:
    virtual std::vector<Expression*> get_children() const = 0;
};


#endif //LAB3_EXPRESSIONS_H
