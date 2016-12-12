#ifndef LAB3_APP_SHELL_API_HPP
#define LAB3_APP_SHELL_API_HPP


#include <stdexcept>
#include <fstream>
#include "model/Company.hpp"
#include "model/Employee.hpp"
#include "../shell/api.h"
#include "db.hpp"
#include "queries.hpp"
#include "model/hierarchy.h"

namespace CM {

    using std::string;

    auto create_employee = Function::New<Employee(string, string)>(
        [] (str_ptr fn, str_ptr ln) {return Employee::New(fn, ln);},
        {"first_name", "last_name"}
    );
    auto get_first_name = Function::New<string(Employee)>(
        [] (Employee::Ptr empl) {return empl->get_first_name();},
        {"employee"}
    );
    auto get_last_name = Function::New<string(Employee)>(
        [] (Employee::Ptr empl) {return empl->get_last_name();},
        {"employee"}
    );
    auto get_company = Function::New<Company(Employee)>(
        [] (Employee::Ptr empl) {return empl->get_company();},
        {"employee"}
    );
    auto get_position = Function::New<string(Employee)>(
        [] (Employee::Ptr empl) {return empl->get_position();},
        {"employee"}
    );
    auto get_salary = Function::New<int(Employee)>(
        [] (Employee::Ptr empl) {return empl->get_salary();},
        {"employee"}
    );
    auto get_supervisor = Function::New<Employee(Employee)>(
        [] (Employee::Ptr empl) {return empl->get_supervisor();},
        {"employee"}
    );
    auto is_employed = Function::New<bool(Employee)>(
        [] (Employee::Ptr empl) {
            return std::make_shared<bool>(empl->is_employed());
        },
        {"employee"}
    );
    auto get_subordinates = Function::New<vector<Employee::Ptr>(Employee)>(
        [] (Employee::Ptr empl) {
            return std::make_shared<vector<Employee::Ptr> >(empl->get_subordinates());
        }, {"employee"}
    );
    auto is_supervisor_of = Function::New<bool(Employee, Employee)>(
        [] (Employee::Ptr empl1, Employee::Ptr empl2) {
            return std::make_shared<bool>(empl1->is_supervisor_of(empl2));
        }, {"supervisor", "subordinate"}
    );

    auto employ = Function::New<void(Employee, Employee, string, int)>(
        [] (Employee::Ptr empl, Employee::Ptr sv, str_ptr pos, int_ptr slr) {
            empl->employ(sv, pos, slr);
        }, {"employee", "supervisor", "position", "salary"}
    );
    auto transfer_full = Function::New<void(Employee, Employee, string)>(
        [] (Employee::Ptr empl, Employee::Ptr sv, str_ptr pos) {
            empl->transfer(sv, pos);
        }, {"employee", "new_supervisor", "new_position"}
    );
    auto transfer_sv = Function::New<void(Employee, Employee)>(
        [] (Employee::Ptr empl, Employee::Ptr supervisor) {empl->transfer(supervisor);},
        {"employee", "new_supervisor"}
    );
    auto transfer_pos = Function::New<void(Employee, string)>(
        [] (Employee::Ptr empl, str_ptr position) {empl->transfer(position);},
        {"employee", "new_position"}
    );
    auto set_salary = Function::New<void(Employee, int)>(
        [] (Employee::Ptr empl, int_ptr salary) {empl->set_salary(salary);},
        {"employee", "salary"}
    );
    auto leave_company = Function::New<void(Employee)>(
        [] (Employee::Ptr empl) {empl->leave_company();},
        {"employee"}
    );
    auto create_company = Function::New<Company(Employee, string)>(
        [] (Employee::Ptr empl, str_ptr name) {return empl->create_company(name);},
        {"director", "name"}
    );

    auto get_director = Function::New<Employee(Company)>(
        [] (Company::Ptr c) {return c->get_director();},
        {"company"}
    );
    auto get_company_name = Function::New<string(Company)>(
        [] (Company::Ptr c) {return c->get_name();},
        {"company"}
    );

    auto save_company = Function::New<void(Company, string)>(
        [] (Company::Ptr cmp, str_ptr fname) {
            std::ofstream stream(*fname);
            if (!stream.is_open()) {
                throw std::runtime_error("Cannot open file " + *fname);
            }
            DB::save(cmp, stream);
            stream.close();
        }, {"company", "file"}
    );
    auto load_company = Function::New<Company(string)>(
        [] (str_ptr fname) {
            std::ifstream stream(*fname);
            if (!stream.is_open()) {
                throw std::runtime_error("Cannot open file " + *fname);
            }
            Company::Ptr comp = DB::load(stream);
            stream.close();
            return comp;
        }, {"file"}
    );

    auto filter_by_salary = Function::New<vector<Employee::Ptr>(Company, int)>(
        [] (Company::Ptr company, int_ptr salary) {
            auto result = query::Query<>([salary] (const Employee::Ptr& empl, int depth) {
                return *empl->get_salary() >= *salary;
            }).run(company);
            return std::make_shared<vector<Employee::Ptr> >(result);
        }, {"company", "salary"}
    );

    auto filter_by_position = Function::New<vector<Employee::Ptr>(Company, string)>(
        [] (Company::Ptr company, str_ptr position) {
            auto result = query::Query<>([position] (const Employee::Ptr& empl, int depth) {
                return *empl->get_position() >= *position;
            }).run(company);
            return std::make_shared<vector<Employee::Ptr> >(result);
        }, {"company", "position"}
    );

    auto hierarchy_to_text = Function::New<string(Company, string)>(
        [] (Company::Ptr company, str_ptr mode) {
            HierarchyIterator *it;
            if (*mode == "level") {
                it = new ByLevel(company->get_director());
            } else if (*mode == "subord") {
                it = new BySubordination(company->get_director());
            } else {
                throw std::runtime_error("Incorrect mode: " + *mode
                                         + ". Expected: \"level\" or \"subord\"");
            }
            std::stringstream stream;
            while (it->has_next()) {
                Employee::Ptr empl = it->next();
                int depth = it->get_depth();
                for(int i = 0; i < depth; i++) {
                    stream << "   ";
                }
                stream << *empl->get_position() << ": " << *empl->get_first_name()
                       << " " << *empl->get_last_name() << std::endl;
            }
            delete it;
            return mk_string(stream.str());
        }, {"company", "mode"}
    );
};




#endif //LAB3_APP_SHELL_API_HPP
