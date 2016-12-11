#ifndef LAB3_HIERARCHY_H
#define LAB3_HIERARCHY_H

#include <queue>
#include <stack>
#include "Employee.hpp"

namespace CM {

    class HierarchyIterator {
    public:
        // check if there are any more employees
        virtual bool has_next() const = 0;

        // returns next employee by forwarding the iterator
        virtual const Employee::Ptr& next() = 0;

        // returns the current employee without forwarding
        // calls to this method should be always valid after calling first next()
        virtual const Employee::Ptr& get() const = 0;

        // returns depth of current employee in the company hierarchy
        virtual int get_depth() const = 0;
    };

    class EmployeeVisitor {
    public:
        virtual void visit(const Employee::Ptr&) = 0;

        template<class HIType>
        void visit_all(const Employee::Ptr& root) {
            HIType hi(root);
            visit_all(hi);
        }

        template<class HIType>
        void visit_all(const Company::Ptr& comp) {
            visit_all<HIType>(comp->get_director());
        }

        void visit_all(HierarchyIterator& hi) {
            while(hi.has_next()) {
                visit(hi.next());
            }
        }
    };

    class ByLevel : public HierarchyIterator {
        // first item in pairs is depth
        std::queue<std::pair<int, Employee::Ptr> > q;
        Employee::Ptr current;
        int current_depth;
    public:
        ByLevel(const Employee::Ptr& root)
            : q({{0, root}}), current(nullptr), current_depth(-1) {};

        bool has_next() const;
        const Employee::Ptr& next();
        const Employee::Ptr& get() const;
        int get_depth() const;
    };

    class BySubordination : public HierarchyIterator {
        // first item is a number of not processed subordinates
        std::stack<std::pair<int, Employee::Ptr> > st;
        // sum of numbers of unprocessed along the stack
        // used to determine whether there are more nodes to process
        int unprocessed_cnt;
        Employee::Ptr root;
    public:
        BySubordination(const Employee::Ptr& root)
            : st(), root(root), unprocessed_cnt(-1) {};

        bool has_next() const;
        const Employee::Ptr& next();
        const Employee::Ptr& get() const;
        int get_depth() const;
    };

}

#endif //LAB3_HIERARCHY_H
