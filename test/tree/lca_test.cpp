#include "gtest/gtest.h"
#include "algotest/tree/lca_test.h"

using namespace algotest;

#include "base.h"
#include "graph/lca.h"

struct LCATester : public LCATesterBase {
    LCA lca;

    void setup(VV<LCAEdge> g, int r) final {
        lca = get_lca(g, r);
    }

    int query(int u, int v) final {
        return lca.query(u, v);
    }
};

using LCATypes = ::testing::Types<LCATester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyLCA, LCATest, LCATypes);
