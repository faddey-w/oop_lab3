#ifndef LAB3_TESTDB_H
#define LAB3_TESTDB_H

#include <sstream>
#include <cxxtest/TestSuite.h>
#include <src/app/db.hpp>
#include <src/app/model/Employee.hpp>

using namespace CM;


class TestDB : public CxxTest::TestSuite {
public:

    void test_correct_io() {
#define EMPL(fn) Employee::New(mk_string(fn), mk_string(""))
        Employee::Ptr ceo = EMPL("director");
        Employee::Ptr mgr1 = EMPL("manager 1");
        Employee::Ptr mgr2 = EMPL("manager 2");
        Employee::Ptr wrk11 = EMPL("worker 1-1");
        Employee::Ptr wrk12 = EMPL("worker 1-2");
        Employee::Ptr wrk21 = EMPL("worker 2-1");
        Employee::Ptr wrk22 = EMPL("worker 2-2");
#undef EMPL

        Company::Ptr company = ceo->create_company(mk_string("mycompany"));

        mgr1->employ(ceo, mgr1->get_first_name(), mk_int(1));
        mgr2->employ(ceo, mgr2->get_first_name(), mk_int(2));

        wrk11->employ(mgr1, wrk11->get_first_name(), mk_int(3));
        wrk12->employ(mgr1, wrk12->get_first_name(), mk_int(4));
        wrk21->employ(mgr2, wrk21->get_first_name(), mk_int(5));
        wrk22->employ(mgr2, wrk22->get_first_name(), mk_int(6));

        std::stringstream stream;
        DB::save(company, stream);

        stream.seekg(0);
        Company::Ptr deserialized_company = DB::load(stream);

        TS_ASSERT(*company->get_name() == *deserialized_company->get_name());
        compare_recursively(ceo, deserialized_company->get_director());
    }

    void compare_recursively(const Employee::Ptr& empl1,
                             const Employee::Ptr& empl2) {
        TS_ASSERT( *empl1->get_first_name() == *empl2->get_first_name() );
        TS_ASSERT( *empl1->get_last_name() == *empl2->get_last_name() );
        TS_ASSERT( *empl1->get_salary() == *empl2->get_salary() );
        TS_ASSERT( *empl1->get_position() == *empl2->get_position() );
        TS_ASSERT( empl1->get_subordinates().size() == empl2->get_subordinates().size() );
        for(int i = 0; i < empl1->get_subordinates().size(); ++i) {
            compare_recursively(
                empl1->get_subordinates()[i],
                empl2->get_subordinates()[i]
            );
        }
    }

};



#endif //LAB3_TESTDB_H
