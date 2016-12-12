#ifndef LAB3_COMPANY_H
#define LAB3_COMPANY_H

#include <string>
#include "Base.hpp"
#include "utils.h"

namespace CM {

    class Employee;
    typedef std::shared_ptr<Employee> EmployeePtr;

    class Company : public Base<Company> {

        str_ptr name;
        EmployeePtr director;

    public:
        Company(const str_ptr& name, const EmployeePtr& director): name(name), director(director) {};

        EmployeePtr get_director() const { return director; }
        const str_ptr& get_name() const { return name; }

        friend class Employee;

    };


};


inline std::ostream& operator<<(std::ostream& stream, const CM::Company& company) {
    return stream << *company.get_name();
}

#endif //LAB3_COMPANY_H
