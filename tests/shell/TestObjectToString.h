#ifndef LAB3_TESTOBJECTTOSTRING_H
#define LAB3_TESTOBJECTTOSTRING_H

#include <memory>
#include <ios>
#include <cxxtest/TestSuite.h>
#include <src/shell/interpreter/Object.hpp>


class CustomType {
    int x;
    bool flag;
public:
    CustomType(int x, bool flag): x(x), flag(flag) {};

    friend std::ostream& operator<<(std::ostream& stream, const CustomType&);
};

std::ostream& operator<<(std::ostream& stream, const CustomType& obj) {
    return stream << "CustomType("
                  << obj.x << ", "
                  << (obj.flag ? "true": "false") << ")";
}


class TestObjectToString: public CxxTest::TestSuite {
public:

    void test_primitive_type() {
        std::shared_ptr<int> int_p(new int(10));
        Object::Ptr obj = Object::New<int>(int_p);
        std::string result = obj->to_string();
        TSM_ASSERT(result, result == "10");
    }

    void test_custom_type() {
        std::shared_ptr<CustomType> my_obj(new CustomType(10, false));
        Object::Ptr obj = Object::New<CustomType>(my_obj);
        std::string result = obj->to_string();
        TSM_ASSERT(result, result == "CustomType(10, false)");
    }

};


#endif //LAB3_TESTOBJECTTOSTRING_H
