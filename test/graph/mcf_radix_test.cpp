#include "algotest/graph/mincostflow_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "datastructure/radixheap.h"
#define priority_queue RadixHeap
#include "graph/mincostflow.h"

class MCFRadixTester : MinCostFlowTesterBase {
  public:
    ll max_flow_min_cost(VV<MinCostFlowEdge> _g, int s, int t) final {
        int n = int(_g.size());
        struct E {
            int to, rev, cap;
            ll dist;
        };
        VV<E> g(n);
        auto add_edge = [&](int from, int to, int cap, ll dist) {
            g[from].push_back(E{to, int(g[to].size()), cap, dist});
            g[to].push_back(E{from, int(g[from].size()) - 1, 0, -dist});
        };
        for (int i = 0; i < n; i++) {
            for (auto e : _g[i]) {
                add_edge(i, e.to, e.cap, e.cost);
            }
        }
        auto res = get_mcf<int, ll>(g, s, t, false);
        res.max_flow(1000000000);

        return res.flow;
    }
};

using MCFRadixTypes = ::testing::Types<MCFRadixTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MCF, MinCostFlowTest, MCFRadixTypes);
