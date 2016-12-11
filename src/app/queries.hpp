#ifndef LAB3_QUERIES_H
#define LAB3_QUERIES_H

#include "src/app/model/hierarchy.h"

namespace CM { namespace query {

    template <class OrderT = BySubordination>
    class Query : private EmployeeVisitor {
    public:
        typedef bool(*Predicate)(const Employee::Ptr&, int);

        Query(Predicate p): predicate(p) {};

        std::vector<Employee::Ptr> run(const Company::Ptr company) {
            result.clear();
            iterator = new OrderT(company->get_director());
            visit_all(*iterator);
            delete iterator;
            return result;
        }

    private:

        void visit(Employee::Ptr empl) {
            if (predicate(empl, iterator->get_depth())) {
                result.push_back(empl);
            }
        }

        Predicate predicate;
        OrderT* iterator;
        std::vector<Employee::Ptr> result;

    };

}}

#endif //LAB3_QUERIES_H
