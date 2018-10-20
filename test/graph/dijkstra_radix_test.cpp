#include "algotest/graph/dijkstra_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "datastructure/radixheap.h"
#define priority_queue RadixHeap
#include "graph/dijkstra.h"

struct DijkstraRadixTester : public DijkstraTesterBase {
    ll min_dist(VV<DijkstraEdge> g, int s, int t) final {
        auto u = mindist<ull>(g, s).dist[t];
        if (u == numeric_limits<ull>::max()) return numeric_limits<ll>::max();
        return u;
    }
};

using DijkstraRadixTypes = ::testing::Types<DijkstraRadixTester>;
INSTANTIATE_TYPED_TEST_CASE_P(Dijkstra, DijkstraTest, DijkstraRadixTypes);
