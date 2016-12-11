#ifndef LAB3_TESTHIERARCHYTRAVERSING_H
#define LAB3_TESTHIERARCHYTRAVERSING_H

#include <vector>
#include <cxxtest/TestSuite.h>
#include <src/app/model/Employee.hpp>
#include <src/app/model/utils.h>
#include <src/app/model/hierarchy.h>


class TestHierarchyTraversing : public CxxTest::TestSuite {
public:

    void test_traverse_by_level() {
        auto ceo = CM::Employee::New(mk_string("ceo"), mk_string(""));
        auto mgr1 = CM::Employee::New(mk_string("mgr1"), mk_string(""));
        auto mgr2 = CM::Employee::New(mk_string("mgr2"), mk_string(""));
        auto empl1 = CM::Employee::New(mk_string("empl1"), mk_string(""));
        auto empl2 = CM::Employee::New(mk_string("empl2"), mk_string(""));
        ceo->create_company(mk_string(""));
        mgr1->employ(ceo, mk_string(""), mk_int(150));
        mgr2->employ(ceo, mk_string(""), mk_int(150));
        empl1->employ(mgr1, mk_string(""), mk_int(150));
        empl2->employ(mgr1, mk_string(""), mk_int(150));

        CM::ByLevel by_level(ceo);
        std::vector<std::string> result_names{};
        std::vector<int> result_depths{};
        while(by_level.has_next()) {
            result_names.push_back(*by_level.next()->get_first_name());
            result_depths.push_back(by_level.get_depth());
        }

        std::vector<std::string> expected_names{
            "ceo", "mgr1", "mgr2", "empl1", "empl2"
        };
        std::vector<int> expected_depths{
            0, 1, 1, 2, 2
        };

        TS_ASSERT(result_names.size() == expected_names.size());
        TS_ASSERT(result_depths.size() == expected_depths.size());
        for(int i = 0; i < result_names.size(); ++i) {
            TS_ASSERT(result_names[i] == expected_names[i]);
            TS_ASSERT(result_depths[i] == expected_depths[i]);
        }
    }

    void test_traverse_by_subordination() {
        auto ceo = CM::Employee::New(mk_string("ceo"), mk_string(""));
        auto mgr1 = CM::Employee::New(mk_string("mgr1"), mk_string(""));
        auto mgr2 = CM::Employee::New(mk_string("mgr2"), mk_string(""));
        auto empl1 = CM::Employee::New(mk_string("empl1"), mk_string(""));
        auto empl2 = CM::Employee::New(mk_string("empl2"), mk_string(""));
        ceo->create_company(mk_string(""));
        mgr1->employ(ceo, mk_string(""), mk_int(150));
        mgr2->employ(ceo, mk_string(""), mk_int(150));
        empl1->employ(mgr1, mk_string(""), mk_int(150));
        empl2->employ(mgr1, mk_string(""), mk_int(150));

        CM::BySubordination by_subordination(ceo);
        std::vector<std::string> result_names{};
        std::vector<int> result_depths{};
        while(by_subordination.has_next()) {
            result_names.push_back(*by_subordination.next()->get_first_name());
            result_depths.push_back(by_subordination.get_depth());
        }

        std::vector<std::string> expected_names{
            "ceo", "mgr1", "empl1", "empl2", "mgr2"
        };
        std::vector<int> expected_depths{
            0, 1, 2, 2, 1
        };

        TS_ASSERT(result_names.size() == expected_names.size());
        TS_ASSERT(result_depths.size() == expected_depths.size());
        for(int i = 0; i < result_names.size(); ++i) {
            TS_ASSERT(result_names[i] == expected_names[i]);
            TS_ASSERT(result_depths[i] == expected_depths[i]);
        }
    }

};


#endif //LAB3_TESTHIERARCHYTRAVERSING_H
