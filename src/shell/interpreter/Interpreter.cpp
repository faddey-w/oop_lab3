#include "Interpreter.h"
#include <memory>
#include <sstream>


string Interpreter::exec(const string &input) {
    try {
        // empty input - empty output, it's just an empty line
        if (input.size() == 0) { return ""; }

        // print help - list of existing functions
        if (input == "??" || input == "?") {
            std::stringstream str;
            str << "Defined functions:\n";
            for(const string& func_name: world->get_function_names()) {
                str << "\n" << func_name;
            }
            return str.str();
        }

        // print help on specific function
        if (input[0] == '?') {
            const string func_name = input.substr(1);
            if (world->has_function(func_name)) {
                return "Help on function " + func_name + ":\n\n"
                       + world->get_function(func_name)->get_help_text();
            } else {
                return "Name error: function " + func_name;
            }
        }

        auto tokens = tokenize(input);
        auto statement = parse(tokens);
        auto expr = statement.get_expr();

        NamesValidator(world).validate(expr);
        auto value = ExprEvaluator(world).evaluate(expr);

        if (statement.has_assignments()) {
            if (value->has_type<void>()) {
                for(const string& name: statement.get_assignments()) {
                    world->delete_variable(name);
                }
            } else {
                for (const string &name: statement.get_assignments()) {
                    world->set_variable(name, value);
                }
            }
            return "";
        } else {
            return value->to_string();
        }

    } catch (SyntaxError& err) {
        return string("Syntax error: ") + err.what();
    } catch (InvalidNameError &err) {
        return string("Name error: ")
               + (err.is_function() ? "function " : "variable ")
               + err.what();
    } catch (TypeError &err) {
        return string("Type error: ") + err.what();
    } catch (Interrupted& err) {
        throw;
    } catch (std::runtime_error& err) {
        return string("Unexpected failure: ") + err.what();
    }
}

void Interpreter::interactive_loop(std::istream &in, std::ostream &out) {
    string line;

    while (true) {
        try {
            out << ">>> ";
            std::getline(in, line);
            string response = exec(line);
            if (response.size() > 0) {
                out << response << std::endl;
            }
        } catch (Interrupted&) { break; }
    }
}

void NamesValidator::visit(FunctionCall &fc) {
    if (function_names.count(fc.get_name()) == 0) {
        throw InvalidNameError(fc.get_name(), true);
    }
    for(auto child: fc.get_children()) {
        child->accept(*this);
    }
}

void NamesValidator::validate(ExprPtr expr) {
    expr->accept(*this);
}

void NamesValidator::visit(Variable &v) {
    if (variable_names.count(v.get_name()) == 0) {
        throw InvalidNameError(v.get_name(), false);
    }
}

void NamesValidator::visit(NumberLiteral &) {}

void NamesValidator::visit(StringLiteral &) {}

Object::Ptr ExprEvaluator::evaluate(ExprPtr expr) {
    expr->accept(*this);
    return _tmp_value;
}

void ExprEvaluator::visit(FunctionCall &fc) {
    ArgsMapping args;
    for (auto &item : fc.get_args()) {
        item.second->accept(*this);
        args[item.first] = _tmp_value;
    }
    _tmp_value = world->get_function(fc.get_name())->call(args);
}

void ExprEvaluator::visit(Variable &v) {
    _tmp_value = world->get_variable(v.get_name());
}

void ExprEvaluator::visit(NumberLiteral &nl) {
    _tmp_value = Object::New<int>(std::shared_ptr<int>(new int(nl.get_value())));
}

void ExprEvaluator::visit(StringLiteral &sl) {
    _tmp_value = Object::New<string>(std::shared_ptr<string>(new string(sl.get_value())));
}
