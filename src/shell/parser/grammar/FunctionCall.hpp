#ifndef LAB3_FUNCTIONCALL_H
#define LAB3_FUNCTIONCALL_H

#include "expressions.h"


class FunctionCall: public Expression {
public:



    void accept(ExpressionVisitor& v) { v.visit(*this); }

protected:


};


#endif //LAB3_FUNCTIONCALL_H