#include "algotest/graph/dijkstra_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "datastructure/radixheap.h"
#include "graph/dijkstra.h"

struct DijkstraTester : public DijkstraTesterBase {
    ll min_dist(VV<DijkstraEdge> g, int s, int t) final {
        return mindist<ll>(g, s).dist[t];
    }
};

using DijkstraTypes = ::testing::Types<DijkstraTester>;
INSTANTIATE_TYPED_TEST_CASE_P(Dijkstra, DijkstraTest, DijkstraTypes);
