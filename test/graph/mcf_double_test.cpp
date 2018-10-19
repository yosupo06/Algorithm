#include "gtest/gtest.h"
#include "algotest/graph/mincostflow_double_test.h"

using namespace algotest;

#include "base.h"
#include "graph/mincostflow.h"

class MCFDTester : MinCostFlowDoubleTesterBase {
  public:
    double max_flow_min_cost(VV<MinCostFlowDoubleEdge> _g, int s, int t) final {
        int n = int(_g.size());
        struct E {
            int to, cap; double dist; int rev;
        };
        VV<E> g(n);
        auto add_edge = [&](int from, int to, int cap, double dist) {
            g[from].push_back(E{to, cap, dist, int(g[to].size())});
            g[to].push_back(E{from, 0, -dist, int(g[from].size())-1});
        };
        for (int i = 0; i < n; i++) {
            for (auto e: _g[i]) {
                add_edge(i, e.to, e.cap, e.cost);
            }
        }
        auto res = get_mcf<int, double>(g, s, t, false);
        res.max_flow(1000000000);

        return res.flow;
    }
};



using MCFDTypes = ::testing::Types<MCFDTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MCFD, MinCostFlowDoubleTest, MCFDTypes);

