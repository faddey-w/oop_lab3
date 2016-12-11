#ifndef LAB3_COMPANY_H
#define LAB3_COMPANY_H

#include <string>
#include "Base.hpp"
#include "utils.h"

namespace CM {

    class Employee;
    typedef std::shared_ptr<Employee> EmployeePtr;
    typedef std::weak_ptr<Employee> EmployeeWeakPtr;

    class Company : public Base<Company> {

        str_ptr name;
        EmployeeWeakPtr director;

    public:
        Company(const str_ptr& name, const EmployeePtr& director): name(name), director(director) {};

        EmployeePtr get_director() const {
            if (director.expired()) return EmployeePtr(nullptr);
            return EmployeePtr(director);
        }
        const str_ptr& get_name() const { return name; }

        friend class Employee;

    };


};

#endif //LAB3_COMPANY_H
