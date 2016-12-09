#ifndef LAB3_FUNCTIONCALL_HPP
#define LAB3_FUNCTIONCALL_HPP

#include <map>
#include <algorithm>
#include <string>
#include "expressions.hpp"


class FunctionCall: public Expression {

    typedef std::map<std::string, ExprPtr> ArgsMap;

    std::string name;
    ArgsMap arguments;

public:
    typedef std::shared_ptr<FunctionCall> Ptr;

    FunctionCall(const std::string& name): name(name), arguments() {};
    FunctionCall(const std::string& name, const ArgsMap& args): name(name), arguments(args) {};

    bool add_argument(const std::string& name, const ExprPtr& expr) {
        if (arguments.count(name) > 0) {
            return false;
        }
        arguments[name] = expr;
        return true;
    }
    const ArgsMap& get_args() const {
        return arguments;
    };

    void accept(ExpressionVisitor& v) { v.visit(*this); }

    const std::vector<ExprPtr> get_children() const {
        std::vector<ExprPtr> ret;
        for(auto &item: arguments) {
            ret.push_back(item.second);
        }
        return ret;
    }

    const std::string& get_name() const { return name; }

protected:
    bool equals(const Expression& other) const {
        auto fc = dynamic_cast<const FunctionCall*>(&other);
        if (!fc) return false;
        if (name != fc->name) return false;
        if (arguments.size() != fc->arguments.size()) return false;
        for(auto item: arguments) {
            auto corresponding = fc->arguments.find(item.first);
            if (corresponding == fc->arguments.end()
                || *item.second != *corresponding->second) {
                return false;
            }
        }
        return true;
    }

protected:


};


#endif //LAB3_FUNCTIONCALL_HPP