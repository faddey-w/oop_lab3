#ifndef LAB3_TESTFUNCTIONCALL_H
#define LAB3_TESTFUNCTIONCALL_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/grammar/FunctionCall.hpp>
#include <src/shell/parser/grammar/Variable.hpp>


class TestFunctionCall: public CxxTest::TestSuite {
    ExprPtr subexpr;
    std::shared_ptr<FunctionCall> func_call;

public:

    void setUp() {
        subexpr.reset(new Variable("subexpr"));
        func_call.reset(new FunctionCall("myfunc"));
    }

    void test_add_argument() {
        const auto& args = func_call->get_args();

        // add argument "arg1"
        TS_ASSERT(func_call->add_argument("arg1", subexpr));
        TS_ASSERT_EQUALS(args.size(), 1);
        TS_ASSERT_EQUALS(args.count("arg1"), 1);

        // add another argument - "arg2"
        TS_ASSERT(func_call->add_argument("arg2", subexpr));
        TS_ASSERT_EQUALS(args.size(), 2);
        TS_ASSERT_EQUALS(args.count("arg1"), 1);
        TS_ASSERT_EQUALS(args.count("arg2"), 1);

        // add "arg1" again -> fail
        TS_ASSERT(!func_call->add_argument("arg1", subexpr));
    }

};


#endif //LAB3_TESTFUNCTIONCALL_H
