#ifndef LAB3_UTILS_H
#define LAB3_UTILS_H

#include <cxxtest/TestSuite.h>


#define ASSERT_EXPECTED_ERROR(expr, message) \
    TS_ASSERT_THROWS_EQUALS(expr, const std::runtime_error &e, e.what(), message)

#endif //LAB3_UTILS_H
