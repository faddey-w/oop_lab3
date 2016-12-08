#ifndef LAB3_TESTDYNAMICTYPES_H
#define LAB3_TESTDYNAMICTYPES_H

#include <cxxtest/TestSuite.h>
#include <src/shell/interpreter/Object.hpp>

using std::shared_ptr;
using std::string;


class TestDynamicTypes : public CxxTest::TestSuite {
public:
    void test_api_works() {
        auto obj = Object::New<int>(shared_ptr<int>(new int(10)));
        TS_ASSERT(obj->has_same_type(*obj));
        TS_ASSERT(obj->has_type<int>());
        TS_ASSERT(!obj->has_type<std::string>());
        TS_ASSERT(*obj->get<int>() == 10);
        TS_ASSERT_THROWS(obj->get<float>(), TypeError);
    }

    void test_supports_empty_value() {
        auto empty_obj = Object::Empty();
        TS_ASSERT(empty_obj->has_type<void>());
        TS_ASSERT_THROWS(empty_obj->get<void>(), TypeError);
    }

    void test_api_works_with_const_objects() {
        const auto obj = Object::New<int>(shared_ptr<int>(new int(10)));
        TS_ASSERT(obj->has_same_type(*obj));
        TS_ASSERT(obj->has_type<int>());
        TS_ASSERT(!obj->has_type<std::string>());
        TS_ASSERT(*obj->get<int>() == 10);
        TS_ASSERT_THROWS(obj->get<float>(), TypeError);
    }

    void test_two_objects_with_same_type() {
        auto obj1 = Object::New<string>(shared_ptr<string>(new string("example1")));
        auto obj2 = Object::New<string>(shared_ptr<string>(new string("example2")));
        TS_ASSERT(obj1->has_same_type(*obj2));
        TS_ASSERT(obj2->has_same_type(*obj1));
    }

    void test_two_objects_with_different_types() {
        auto obj1 = Object::New<string>(shared_ptr<string>(new string("example1")));
        auto obj2 = Object::New<float>(shared_ptr<float>(new float(1.0)));
        TS_ASSERT(!obj1->has_same_type(*obj2));
        TS_ASSERT(!obj2->has_same_type(*obj1));
    }

};


#endif //LAB3_TESTDYNAMICTYPES_H
