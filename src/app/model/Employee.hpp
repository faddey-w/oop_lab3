#ifndef LAB3_EMPLOYEE_H
#define LAB3_EMPLOYEE_H

#include <algorithm>
#include <string>
#include <vector>
#include "utils.h"
#include "Base.hpp"
#include "Company.hpp"


namespace CM {


    class Employee : public Base<Employee> {

        // personal info
        const str_ptr first_name;
        const str_ptr last_name;

        // employment info
        Company::Ptr company;
        str_ptr position;
        Employee::Ptr supervisor;
        std::vector<Employee::Ptr> subordinates;
        int_ptr salary;

    public:

        Employee(str_ptr first_name, str_ptr last_name)
        : first_name(first_name), last_name(last_name), company(nullptr),
          position(nullptr), salary(nullptr), supervisor(nullptr), subordinates() {};

        const str_ptr &get_first_name() const { return first_name; }
        const str_ptr &get_last_name() const { return last_name; }

        const Company::Ptr& get_company() const { return company; }
        const str_ptr &get_position() const { return position; }
        int_ptr get_salary() const { return salary; }
        const Employee::Ptr &get_supervisor() const { return supervisor; }
        bool is_employed() const { return bool(company); }
        const std::vector<Employee::Ptr> get_subordinates() const { return subordinates; }
        bool is_supervisor_of(const Ptr& empl) const;

        void employ(const Ptr &supervisor, const str_ptr &position, const int_ptr &salary);
        void transfer(const Ptr& supervisor, const str_ptr& position);
        void transfer(const Ptr& supervisor) { transfer(supervisor, nullptr); }
        void transfer(const str_ptr& position) { transfer(nullptr, position); }
        void set_salary(const int_ptr& salary) { Employee::salary = salary; }
        void leave_company();
        Company::Ptr create_company(const str_ptr&);

    protected:
        void set_supervisor(const Ptr &sv);
        void remove_supervisor();
    };

}

#endif //LAB3_EMPLOYEE_H
