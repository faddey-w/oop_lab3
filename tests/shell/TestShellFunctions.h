#ifndef LAB3_TESTAPI_H
#define LAB3_TESTAPI_H

#include <cxxtest/TestSuite.h>
#include <memory>
#include <src/shell/interpreter/ApiCore.hpp>


struct Dummy {

    typedef std::shared_ptr<Dummy> Ptr;

    int x;
    std::string str;

    static Ptr Make(int x, const std::string& str) {
        return Ptr(new Dummy(x, str));
    }

    Dummy(int x, const std::string& str): x(x), str(str) {}
};


struct Dummy2 {
    typedef std::shared_ptr<Dummy2> Ptr;

    int x;

    static Ptr Make(int x) {
        return Ptr(new Dummy2(x));
    }

    Dummy2(int x): x(x) {}
};


void my_mutate(Dummy::Ptr dummy) {
    dummy->x += 1;
}
Dummy::Ptr my_no_args() {
    return Dummy::Ptr(new Dummy(10, "some string"));
}
Dummy::Ptr my_combine(Dummy::Ptr d1, Dummy::Ptr d2) {
    return Dummy::Ptr(new Dummy(d1->x + d2->x, d1->str + d2->str));
}
Dummy::Ptr my_two_types(Dummy::Ptr d1, Dummy2::Ptr d2) {
    return Dummy::Make(d1->x * d2->x, d1->str);
}



class TestShellExtensionApi : public CxxTest::TestSuite {
public:
    void test_function_without_return_works() {
        Function::Ptr mutate = Function::New<void(Dummy)>(my_mutate, {"arg1"});
        Object::Ptr dummy_obj = Object::New<Dummy>(Dummy::Make(100, "xyz"));
        Object::Ptr result = mutate->call(
            {{"arg1", dummy_obj}}
        );
        TS_ASSERT(result->has_type<void>());
        TS_ASSERT(dummy_obj->get<Dummy>()->x == 101);
    }

    void test_function_without_arguments_works() {
        Function::Ptr no_args = Function::New<Dummy()>(my_no_args, {});
        Object::Ptr result = no_args->call({});
        TS_ASSERT(result->has_type<Dummy>());
        TS_ASSERT(result->get<Dummy>()->x == 10);
        TS_ASSERT(result->get<Dummy>()->str == "some string");
    }

    void test_function_with_args_and_return_works() {
        Function::Ptr combine = Function::New<Dummy(Dummy, Dummy)>(my_combine, {"arg1", "arg2"});
        Object::Ptr dummy1_obj = Object::New<Dummy>(Dummy::Make(100, "xyz"));
        Object::Ptr dummy2_obj = Object::New<Dummy>(Dummy::Make(250, "asd"));
        Object::Ptr result = combine->call(
            {{"arg1", dummy1_obj}, {"arg2", dummy2_obj}}
        );
        TS_ASSERT(result->has_type<Dummy>());
        TS_ASSERT(result->get<Dummy>()->x == 350);
        TS_ASSERT(result->get<Dummy>()->str == "xyzasd");
    }

    void test_function_with_different_types_parameters_works() {
        Function::Ptr combine = Function::New<Dummy(Dummy, Dummy2)>(my_two_types, {"arg1", "arg2"});
        Object::Ptr dummy1_obj = Object::New<Dummy>(Dummy::Make(100, "xyz"));
        Object::Ptr dummy2_obj = Object::New<Dummy2>(Dummy2::Make(25));
        Object::Ptr result = combine->call(
            {{"arg1", dummy1_obj}, {"arg2", dummy2_obj}}
        );
        TS_ASSERT(result->has_type<Dummy>());
        TS_ASSERT(result->get<Dummy>()->x == 2500);
        TS_ASSERT(result->get<Dummy>()->str == "xyz");
    }

    void test_missing_parameter_raises_type_error() {
        Function::Ptr combine = Function::New<Dummy(Dummy, Dummy)>(my_combine, {"arg1", "arg2"});
        Object::Ptr dummy1_obj = Object::New<Dummy>(Dummy::Make(100, "xyz"));
        Object::Ptr dummy2_obj = Object::New<Dummy>(Dummy::Make(250, "asd"));
        TS_ASSERT_THROWS(combine->call(
            {{"arg1", dummy1_obj}}
        ), TypeError);
    }

    void test_wrong_parameter_name_raises_type_error() {
        Function::Ptr combine = Function::New<Dummy(Dummy, Dummy)>(my_combine, {"arg1", "arg2"});
        Object::Ptr dummy1_obj = Object::New<Dummy>(Dummy::Make(100, "xyz"));
        Object::Ptr dummy2_obj = Object::New<Dummy>(Dummy::Make(250, "asd"));
        TS_ASSERT_THROWS(combine->call(
            {{"arg1",  dummy1_obj},
             {"wrong", dummy1_obj}}
        ), TypeError);
    }

    void test_extra_parameter_raises_type_error() {
        Function::Ptr combine = Function::New<Dummy(Dummy, Dummy)>(my_combine, {"arg1", "arg2"});
        Object::Ptr dummy1_obj = Object::New<Dummy>(Dummy::Make(100, "xyz"));
        Object::Ptr dummy2_obj = Object::New<Dummy>(Dummy::Make(250, "asd"));
        TS_ASSERT_THROWS(combine->call(
            {{"arg1", dummy1_obj}, {"arg2", dummy2_obj}, {"extra", dummy1_obj}}
        ), TypeError);
    }

};


#endif //LAB3_TESTAPI_H
