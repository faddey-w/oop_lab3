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

void shell_exit() {
    throw Interrupted();
}





const std::map<std::string, Function::Ptr> builtins{
    {"dir", Function::New<vector<string>()>(
        list_variables, {},
        "Returns list of all variables. Return type: vector<string>"
    )},
    {"exit", Function::New<void()>(
        shell_exit, {},
        "Exits from the shell."
    )}
};
