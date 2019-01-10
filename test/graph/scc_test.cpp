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

struct KosarajuSCCTester : public SCCTesterBase {
    V<int> topological_order(VV<SCCEdge> g) final {
        int n = int(g.size());
        VV<SCCEdge> rg(n);
        for (int i = 0; i < n; i++) {
            for (auto e: g[i]) {
                rg[e.to].push_back({i});
            }
        }
        return get_kosaraju_scc(g, rg).id;
    }
};

struct BitsetSCCTester : public SCCTesterBase {
    using B = bitset<1000>;
    V<int> topological_order(VV<SCCEdge> _g) final {
        int n = int(_g.size());
        assert(n <= 1000);
        V<B> g(n), rg(n);
        for (int i = 0; i < n; i++) {
            for (auto e: _g[i]) {
                g[i].set(e.to);
                rg[e.to].set(i);
            }
        }
        return get_bitset_scc(g, rg).id;
    }
};


using SCCTypes = ::testing::Types<SCCTester, KosarajuSCCTester, BitsetSCCTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MySCC, SCCTest, SCCTypes);
