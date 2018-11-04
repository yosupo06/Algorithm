#include "algotest/graph/dijkstra_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "algotest/graph/scc_test.h"
#include "base.h"
#include "bitop.h"
#include "graph/scc.h"

using namespace algotest;

struct SCCTester : public SCCTesterBase {
    V<int> topological_order(VV<SCCEdge> g) final { return get_scc(g).id; }
};

using SCCTypes = ::testing::Types<SCCTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MySCC, SCCTest, SCCTypes);
