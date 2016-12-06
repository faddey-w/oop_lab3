#ifndef LAB3_FUNCTIONCALL_H
#define LAB3_FUNCTIONCALL_H

#include <map>
#include <algorithm>
#include <string>
#include "expressions.hpp"


class FunctionCall: public Expression {

    typedef std::map<std::string, ExprPtr> ArgsType;

    std::string name;
    ArgsType arguments;

public:

    FunctionCall(const std::string& name): name(name), arguments() {};
    FunctionCall(const std::string& name, const ArgsType& args): name(name), arguments(args) {};

    bool add_argument(const std::string& name, const ExprPtr& expr) {
        if (arguments.count(name) > 0) {
            return false;
        }
        arguments[name] = expr;
        return true;
    }
    const ArgsType& get_args() const {
        return arguments;
    };

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<Ptr>& get_children() const {
        std::vector<ExprPtr> ret;
        for(auto &item: arguments) {
            ret.push_back(item.second);
        }
        return ret;
    }

protected:
    bool equals(const Expression& other) const {
        auto fc = dynamic_cast<const FunctionCall*>(&other);
        if (!fc) return false;
        return name == fc->name
            && arguments.size() == fc->arguments.size()
            && std::equal(arguments.begin(), arguments.end(),
                          fc->arguments.begin());;
    }

protected:


};


#endif //LAB3_FUNCTIONCALL_H