#include "Employee.hpp"
#include "hierarchy.h"
#include <list>

namespace CM {

    class StaffFlattener : private EmployeeVisitor {

        std::list<Employee::Ptr> result;

        void visit(const Employee::Ptr& empl) {
            result.push_back(empl);
        }

    public:
        template<class Order>
        static std::list<Employee::Ptr> get_department(const Employee::Ptr& dpt_head) {
            StaffFlattener sf;
            sf.visit_all<Order>(dpt_head);
            return sf.result;
        }

    };


    void Employee::set_supervisor(const Ptr &sv) {
        remove_supervisor();
        supervisor = sv;
        sv->subordinates.push_back(new_ptr());
        company = sv->get_company();
    }

    void Employee::remove_supervisor() {
        if (supervisor) {
            for(int i = 0; i < supervisor->subordinates.size(); ++i) {
                if (this == supervisor->subordinates[i].get()) {
                    supervisor->subordinates.erase(supervisor->subordinates.begin()+i);
                }
            }
            supervisor.reset();
        }
    }

    void Employee::leave_company() {
        check(is_employed());
        if (this == company->get_director().get()) {
            // all employees leave the company.
            // we do it in reverse order to avoid transfers
            // after deletion from the non-terminal hierarchy node
            for(const auto& sub: get_subordinates()) {
                auto department = StaffFlattener::get_department<ByLevel>(sub);
                for(auto r_it = department.rbegin(); r_it != department.rend(); r_it++) {
                    (*r_it)->leave_company();
                }
            }
            company->director.reset();
        } else {
            for(const auto& sub: get_subordinates()) {
                sub->set_supervisor(supervisor);
            }
            remove_supervisor();
        }
        company.reset();
        position.reset();
        salary = int_ptr(new int(0));
    }

    bool Employee::is_supervisor_of(const Ptr& empl) const {
        for(const auto& sub: subordinates) {
            if (sub.get() == empl.get()) return true;
        }
        return false;
    }

    void Employee::employ(const Ptr &supervisor, const str_ptr &position, const int_ptr &salary) {
        check(!is_employed());
        Employee::company = supervisor->get_company();
        transfer(supervisor, position);
        set_salary(salary);
    }

    void Employee::transfer(const Ptr& supervisor, const str_ptr& position) {
        check(is_employed());
        if (supervisor) set_supervisor(supervisor);
        if (position) Employee::position = position;
    }

    Company::Ptr Employee::create_company(const str_ptr &name) {
        check(!is_employed());
        company = Company::New(name, new_ptr());
        position = mk_string("CEO");
        set_salary(mk_int(0));
        return company;
    }

}
