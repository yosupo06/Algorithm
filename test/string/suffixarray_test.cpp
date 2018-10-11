#include "gtest/gtest.h"
#include "algotest/string/suffixarray_test.h"

using namespace algotest;

#include "base.h"
#include "string/suffixarray.h"


struct SuffixArrayTester : public SuffixArrayTesterBase {
    V<int> sa(string s) final {
        return sa_is(s);
    }
    V<int> lcp(string s, V<int> sa) final {
        return SA<string>(s, sa).lcp;
    }
};

using SuffixArrayTypes = ::testing::Types<SuffixArrayTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MySuffixArray, SuffixArrayTest, SuffixArrayTypes);
