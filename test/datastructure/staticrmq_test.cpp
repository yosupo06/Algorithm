#include "gtest/gtest.h"
#include "algotest/datastructure/staticrmq_test.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "datastructure/sparsetable.h"
#include "datastructure/disjointtable.h"

struct minf {
    int operator()(int a, int b) const { return min(a, b); }
};

struct SparseTableTester : public StaticRMQTesterBase {
    SparseTable<int, minf> table;

    void setup(V<int> a) final {
        table = get_sparse_table(a, int(TEN(9) + TEN(6)), minf());
    }
    int range_min(int l, int r) final {
        return table.query(l, r);
    }
};

struct DisjointTester : public StaticRMQTesterBase {
    DisjointTable<int, minf> table;

    void setup(V<int> a) final {
        table = get_disjoint_table(a, int(TEN(9) + TEN(6)), minf());
    }
    int range_min(int l, int r) final {
        return table.query(l, r);
    }
};

using StaticRMQTypes = ::testing::Types<SparseTableTester, DisjointTester>;
INSTANTIATE_TYPED_TEST_CASE_P(StaticRMQ, StaticRMQTest, StaticRMQTypes);
