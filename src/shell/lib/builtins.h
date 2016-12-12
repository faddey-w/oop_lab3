#ifndef LAB3_BUILTINS_H
#define LAB3_BUILTINS_H

#include "../interpreter/Interpreter.h"
#include "utils.h"

void set_world(World::Ptr);

std::shared_ptr<std::vector<std::string> > list_variables();


void shell_exit();


void print_variable(std::shared_ptr<string>);


std::shared_ptr<string> string_concat(std::shared_ptr<string>, std::shared_ptr<string>);


extern const std::map<std::string, Function::Ptr> builtins;


#endif //LAB3_BUILTINS_H
