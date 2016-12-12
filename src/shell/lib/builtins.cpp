#include <iostream>
#include "builtins.h"

using std::vector;
using std::shared_ptr;
using std::string;

World::Ptr global_world;


void set_world(World::Ptr world) {
    global_world = world;
}


shared_ptr<vector<string> > list_variables() {
    const auto& var_names = global_world->get_variable_names();
    return std::make_shared<vector<string> >(var_names.begin(),
                                             var_names.end());
}


std::shared_ptr<string> string_concat(std::shared_ptr<string> s1, std::shared_ptr<string> s2) {
    return std::make_shared<string>(*s1 + *s2);
}


void print_variable(std::shared_ptr<string> var_name) {
    if (global_world->has_variable(*var_name)) {
        auto obj = global_world->get_variable(*var_name);
        std::cout << obj->to_string() << std::endl;
    } else {
        throw InvalidNameError(*var_name, false);
    }
}


void shell_exit() {
    throw Interrupted();
}





const std::map<std::string, Function::Ptr> builtins{
    {"dir", Function::New<vector<string>()>(
        list_variables, {},
        "Returns list of all variables. Return type: vector<string>"
    )},
    {"print", Function::New<void(string)>(
        print_variable, {"var"},
        "Prints value of variable to stdout. Returns nothing."
    )},
    {"strcat", Function::New<string(string, string)> (
        string_concat, {"s1", "s2"},
        "Concatenate two strings"
    )},
    {"exit", Function::New<void()>(
        shell_exit, {},
        "Exits from the shell."
    )}
};
