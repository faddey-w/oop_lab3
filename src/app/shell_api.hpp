#ifndef LAB3_APP_SHELL_API_HPP
#define LAB3_APP_SHELL_API_HPP


#include "../shell/api.h"
#include "model/Company.hpp"
#include "model/Employee.hpp"

namespace CM {

    using std::string;

//    auto create_position = Function::New<Position(string)>(
//        [] (str_ptr s) {return Position::New(s);},
//        {"title"}, "Creates new Position");
//    auto get_position_title = Function::New<string(Position)>(
//        [] (Position::Ptr pos) {return pos->get_title();},
//        {"position"}, "Returns the title of given position");
//    auto set_position_title = Function::New<string(Position, string)>(
//        [] (Position::Ptr pos, str_ptr s) {return pos->set_title(s);},
//        {"position", "title"}, "Sets the title for given position");
//
//    auto create_employee = Function::New<Employee(string, string, Company, Position, int)>(
//        [] (str_ptr first_name, str_ptr last_name, CompanyPtr comp, Position::Ptr pos, int_ptr salary) {
//            return Employee::New(first_name, last_name, comp, pos, salary);
//        }, {"first_name", "last_name", "company", "position", "salary"},
//        "Creates an employee for given company. Does not set the supervisor => "
//        "searches will not yield that user until he will be attached to the hierarchy."
//    );
};




#endif //LAB3_APP_SHELL_API_HPP
