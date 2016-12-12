#ifndef LAB3_INTERPRETER_HPP
#define LAB3_INTERPRETER_HPP

#include <vector>
#include <map>
#include <set>
#include <ios>
#include <string>
#include <stdexcept>
#include <memory>
#include "Function.hpp"
#include "Object.hpp"

#include "../parser/tokenization.h"
#include "../parser/grammar/parse.h"
#include "../parser/grammar/FunctionCall.hpp"
#include "../parser/grammar/Variable.hpp"
#include "../parser/grammar/NumberLiteral.hpp"
#include "../parser/grammar/StringLiteral.hpp"
#include "../parser/grammar/Statement.hpp"


using std::map;
using std::string;
using std::vector;
using std::set;


class InvalidNameError: public std::runtime_error {
    bool _is_function;
public:
    InvalidNameError(const string& name, bool is_function)
        : _is_function(is_function), std::runtime_error(name) {};
    bool is_function() const { return _is_function; }
};
class Interrupted : public std::runtime_error {
public:
    Interrupted(): std::runtime_error("") {};
};


class World {

    const map<string, Function::Ptr> functions;
    map<string, Object::Ptr> variables;
public:

    typedef std::shared_ptr<World> Ptr;

    World(const map<string, Function::Ptr>& functions,
          const map<string, Object::Ptr>& variables)
        : functions(functions), variables(variables) {}

    bool has_variable(const string& name) { return variables.count(name) > 0; }
    bool has_function(const string& name) { return functions.count(name) > 0; }

    Function::Ptr get_function(const string& name) { return functions.at(name); }
    Object::Ptr get_variable(const string& name) { return variables.at(name); }

    void set_variable(const string& name, Object::Ptr value) { variables[name] = value; }
    void delete_variable(const string& name) { variables.erase(name); }

    set<string> get_function_names() const {
        set<string> result;
        for(auto &item: functions) {
            result.insert(item.first);
        }
        return result;
    }
    set<string> get_variable_names() const {
        set<string> result;
        for(auto &item: variables) {
            result.insert(item.first);
        }
        return result;
    }

};


class Interpreter {

    World::Ptr world;

public:
    Interpreter(const map<string, Function::Ptr>& functions,
                const map<string, Object::Ptr>& variables)
        : world(new World(functions, variables)) {}
    Interpreter(World::Ptr world): world(world) {}

    string exec(const string& input, bool &failbit);

    void execfile(const string& filename);

    void interactive_loop(std::istream&, std::ostream&);

};

class NamesValidator : private ExpressionVisitor {
    const set<string> function_names;
    const set<string> variable_names;

public:

    NamesValidator(set<string> function_names, set<string> variable_names)
        : function_names(function_names), variable_names(variable_names)
        , ExpressionVisitor() {};
    NamesValidator(World::Ptr world)
        : function_names(world->get_function_names())
        , variable_names(world->get_variable_names())
        , ExpressionVisitor() {};

    void validate(ExprPtr expr);

    void visit(FunctionCall&);
    void visit(Variable&);
    void visit(NumberLiteral&);
    void visit(StringLiteral&);

};


class ExprEvaluator : private ExpressionVisitor {

    World::Ptr world;
    Object::Ptr _tmp_value;

public:
    ExprEvaluator(World::Ptr world): world(world), _tmp_value() {};

    Object::Ptr evaluate(ExprPtr expr);

    void visit(FunctionCall&);
    void visit(Variable&);
    void visit(NumberLiteral&);
    void visit(StringLiteral&);

};



#endif //LAB3_INTERPRETER_HPP
