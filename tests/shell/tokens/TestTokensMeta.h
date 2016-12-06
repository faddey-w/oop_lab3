#ifndef LAB3_TESTTOKENSMETA_H
#define LAB3_TESTTOKENSMETA_H

#include <cxxtest/TestSuite.h>
#include <src/shell/parser/tokens/meta.hpp>

class TestTokensMeta: public CxxTest::TestSuite {
public:
    void test_type_uniqueness() {
        for(int i = 0; i < TokenMeta::objects.size(); i++) {
            for(int j = i+1; j < TokenMeta::objects.size(); j++) {
                TokenMeta *meta1 = TokenMeta::objects[i];
                TokenMeta *meta2 = TokenMeta::objects[j];
                TS_ASSERT(meta1->get_type() != meta2->get_type());
            }
        }
    }
};

#endif //LAB3_TESTTOKENSMETA_H
