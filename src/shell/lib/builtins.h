#ifndef LAB3_BUILTINS_H
#define LAB3_BUILTINS_H

#include "utils.h"
#include "../interpreter/Interpreter.h"

void set_world(World::Ptr);

std::shared_ptr<std::vector<std::string> > list_variables();


void shell_exit();


extern const std::map<std::string, Function::Ptr> builtins;


#endif //LAB3_BUILTINS_H
