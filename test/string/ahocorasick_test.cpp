#include "gtest/gtest.h"
#include "algotest/string/ahocorasick_test.h"

using namespace algotest;

#include "base.h"
#include "string/ahocorasick.h"


struct AhoCorasickTester : public AhoCorasickTesterBase {
    VV<int> enumerate(string target, V<string> patterns) final {
        int m = int(patterns.size());
        auto tree = AhoTrie::make(patterns);
        VV<int> res(m);
        tree->match(target, [&](int id, int r) {
                res[id].push_back(r - int(patterns[id].size()));
        });
        return res;
    }
};

using AhoCorasickTypes = ::testing::Types<AhoCorasickTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyAhoCorasick, AhoCorasickTest, AhoCorasickTypes);
