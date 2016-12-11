#ifndef LAB3_TESTMODELS_H
#define LAB3_TESTMODELS_H

#include <cxxtest/TestSuite.h>
#include <src/app/model/Employee.hpp>
#include <src/app/model/Company.hpp>
#include <src/app/model/utils.h>


class TestModels : public CxxTest::TestSuite {
public:

    void test_initial_state() {
        auto e = CM::Employee::New(mk_string("name"), mk_string("surname"));
        TS_ASSERT( e->get_first_name() && *e->get_first_name() == "name");
        TS_ASSERT( e->get_last_name() && *e->get_last_name() == "surname");
        TS_ASSERT( ! e->get_company() );
        TS_ASSERT( ! e->get_position() );
        TS_ASSERT( ! e->get_salary() );
        TS_ASSERT( ! e->get_supervisor() );
        TS_ASSERT( ! e->is_employed() );
        TS_ASSERT( e->get_subordinates().size() == 0 );
    }

    void test_create_company() {
        auto e = CM::Employee::New(mk_string(""), mk_string(""));
        auto comp = e->create_company(mk_string(""));
        TS_ASSERT( e->get_company() == comp );
        TS_ASSERT( e->get_position() && *e->get_position() == "CEO" );
        TS_ASSERT( e->get_salary() && *e->get_salary() == 0 );
        TS_ASSERT( ! e->get_supervisor() );
        TS_ASSERT( e->is_employed() );
        TS_ASSERT( e->get_subordinates().size() == 0 );
        TS_ASSERT( comp->get_director() == e );
    }

    void test_set_salary() {
        // set_salary() is available only if Employee is employed (or is CEO)
        auto ceo = CM::Employee::New(mk_string(""), mk_string(""));
        auto empl = CM::Employee::New(mk_string(""), mk_string(""));
        ceo->create_company(mk_string(""));
        ceo->set_salary(mk_int(500));
        TS_ASSERT(*ceo->get_salary() == 500);

        empl->employ(ceo, mk_string("Manager"), mk_int(100));
        TS_ASSERT(*empl->get_salary() == 100);

        empl->set_salary(mk_int(250));
        TS_ASSERT(*empl->get_salary() == 250);
    }

    void test_employ_as_subordinate_of_ceo() {
        auto ceo = CM::Employee::New(mk_string(""), mk_string(""));
        auto manager = CM::Employee::New(mk_string(""), mk_string(""));
        auto company = ceo->create_company(mk_string(""));

        manager->employ(ceo, mk_string("Manager"), mk_int(150));
        TS_ASSERT( manager->get_company() == company );
        TS_ASSERT( manager->get_position() && *manager->get_position() == "Manager" );
        TS_ASSERT( manager->get_salary() && *manager->get_salary() == 150 );
        TS_ASSERT( manager->get_supervisor() == ceo );
        TS_ASSERT( manager->is_employed() );
        TS_ASSERT( manager->get_subordinates().size() == 0 );
        TS_ASSERT( ceo->get_subordinates().size() == 1 );
        TS_ASSERT( ceo->get_subordinates()[0] == manager );
        TS_ASSERT( ceo->is_supervisor_of(manager) );
    }

    void test_employ_as_subordinate_of_non_ceo() {
        auto ceo = CM::Employee::New(mk_string(""), mk_string(""));
        auto manager = CM::Employee::New(mk_string(""), mk_string(""));
        auto empl = CM::Employee::New(mk_string(""), mk_string(""));
        auto company = ceo->create_company(mk_string(""));
        manager->employ(ceo, mk_string("Manager"), mk_int(150));

        empl->employ(manager, mk_string("Worker1"), mk_int(100));
        TS_ASSERT( empl->get_company() == company );
        TS_ASSERT( empl->get_position() && *empl->get_position() == "Worker1" );
        TS_ASSERT( empl->get_salary() && *empl->get_salary() == 100 );
        TS_ASSERT( empl->get_supervisor() == manager );
        TS_ASSERT( empl->is_employed() );
        TS_ASSERT( empl->get_subordinates().size() == 0 );
        TS_ASSERT( manager->get_subordinates().size() == 1 );
        TS_ASSERT( manager->get_subordinates()[0] == empl );
        TS_ASSERT( ceo->get_subordinates().size() == 1 );
        TS_ASSERT( ceo->get_subordinates()[0] == manager );
    }

    void test_employ_with_neighborship() {
        auto ceo = CM::Employee::New(mk_string(""), mk_string(""));
        auto manager = CM::Employee::New(mk_string(""), mk_string(""));
        auto consultant = CM::Employee::New(mk_string(""), mk_string(""));
        auto company = ceo->create_company(mk_string(""));
        manager->employ(ceo, mk_string("Manager"), mk_int(150));

        consultant->employ(ceo, mk_string("Consultant"), mk_int(300));
        TS_ASSERT( consultant->get_company() == company );
        TS_ASSERT( consultant->get_position() && *consultant->get_position() == "Consultant" );
        TS_ASSERT( consultant->get_salary() && *consultant->get_salary() == 300 );
        TS_ASSERT( consultant->get_supervisor() == ceo );
        TS_ASSERT( consultant->is_employed() );
        TS_ASSERT( consultant->get_subordinates().size() == 0 );
        TS_ASSERT( ceo->get_subordinates().size() == 2 );
        TS_ASSERT( manager->get_subordinates().size() == 0 );
        TS_ASSERT( consultant->get_subordinates().size() == 0 );
        TS_ASSERT( ceo->get_subordinates()[0] == manager );
        TS_ASSERT( ceo->get_subordinates()[1] == consultant );
    }

    void test_ceo_leaves_empty_company() {
        auto e = CM::Employee::New(mk_string(""), mk_string(""));
        auto company = e->create_company(mk_string(""));
        e->leave_company();
        TS_ASSERT( ! e->get_company() );
        TS_ASSERT( ! e->get_position() );
        TS_ASSERT( ! e->is_employed() );
        TS_ASSERT( ! company->get_director() );
    }

    void test_ceo_leaves_non_empty_company() {
        auto ceo = CM::Employee::New(mk_string(""), mk_string(""));
        auto mgr1 = CM::Employee::New(mk_string(""), mk_string(""));
        auto mgr2 = CM::Employee::New(mk_string(""), mk_string(""));
        auto empl1 = CM::Employee::New(mk_string(""), mk_string(""));
        auto empl2 = CM::Employee::New(mk_string(""), mk_string(""));
        auto company = ceo->create_company(mk_string(""));

        mgr1->employ(ceo, mk_string("Manager"), mk_int(150));
        mgr2->employ(ceo, mk_string("Manager"), mk_int(150));
        empl1->employ(mgr1, mk_string("Worker"), mk_int(150));
        empl2->employ(mgr1, mk_string("Worker"), mk_int(150));

        ceo->leave_company();
        TS_ASSERT( ! ceo->is_employed() );
        TS_ASSERT( ! mgr1->is_employed() );
        TS_ASSERT( ! mgr2->is_employed() );
        TS_ASSERT( ! empl1->is_employed() );
        TS_ASSERT( ! empl2->is_employed() );
        TS_ASSERT( ! ceo->get_company() );
        TS_ASSERT( ! mgr1->get_company() );
        TS_ASSERT( ! mgr2->get_company() );
        TS_ASSERT( ! empl1->get_company() );
        TS_ASSERT( ! empl2->get_company() );
    }

    void test_manager_leaves_company() {
        auto ceo = CM::Employee::New(mk_string(""), mk_string(""));
        auto mgr1 = CM::Employee::New(mk_string(""), mk_string(""));
        auto mgr2 = CM::Employee::New(mk_string(""), mk_string(""));
        auto empl1 = CM::Employee::New(mk_string(""), mk_string(""));
        auto empl2 = CM::Employee::New(mk_string(""), mk_string(""));
        auto company = ceo->create_company(mk_string(""));

        mgr1->employ(ceo, mk_string("Manager"), mk_int(150));
        mgr2->employ(ceo, mk_string("Manager"), mk_int(150));
        empl1->employ(mgr1, mk_string("Worker"), mk_int(150));
        empl2->employ(mgr1, mk_string("Worker"), mk_int(150));

        mgr1->leave_company();
        TS_ASSERT( ! mgr1->is_employed() );
        TS_ASSERT( empl1->is_employed() );
        TS_ASSERT( empl2->is_employed() );
        TS_ASSERT( empl1->get_supervisor() == ceo );
        TS_ASSERT( empl2->get_supervisor() == ceo );
        TS_ASSERT( ceo->get_subordinates().size() == 3 );
        TS_ASSERT( ceo->get_subordinates()[0] == mgr2 );
        TS_ASSERT( ceo->get_subordinates()[1] == empl1 );
        TS_ASSERT( ceo->get_subordinates()[2] == empl2 );
    }
};


#endif //LAB3_TESTMODELS_H
