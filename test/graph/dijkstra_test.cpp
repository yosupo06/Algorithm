#include "algotest/graph/dijkstra_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "datastructure/radixheap.h"
#include "graph/dijkstra.h"

struct DijkstraTester : public DijkstraTesterBase {
    ll min_dist(VV<DijkstraEdge> g, int s, int t) final {
        return get_mindist_pq<ll>(g, s).dist[t];
    }
};

struct DijkstraRadixTester : public DijkstraTesterBase {
    ll min_dist(VV<DijkstraEdge> g, int s, int t) final {
        ull u = get_mindist_radix<ull>(g, s).dist[t];
        if (u == numeric_limits<ull>::max()) return numeric_limits<ll>::max();
        return u;
    }
};

using DijkstraTypes = ::testing::Types<DijkstraTester, DijkstraRadixTester>;
INSTANTIATE_TYPED_TEST_CASE_P(Dijkstra, DijkstraTest, DijkstraTypes);
