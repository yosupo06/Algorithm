#include "algotest/datastructure/staticrmq_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "datastructure/disjointtable.h"
#include "datastructure/sparsetable.h"

struct minf {
    int operator()(int a, int b) const { return min(a, b); }
};

struct SparseTableTester : public StaticRMQTesterBase {
    SparseTable<int, minf> table;

    void setup(V<int> a) final {
        table = get_sparse_table(a, int(TEN(9) + TEN(6)), minf());
    }
    int range_min(int l, int r) final { return table.query(l, r); }
};

struct LowMemorySparseTableTester : public StaticRMQTesterBase {
    LowMemorySparseTable<int, minf> table;

    void setup(V<int> a) final {
        table = get_low_memory_sparse_table(a, int(TEN(9) + TEN(6)), minf());
    }
    int range_min(int l, int r) final { return table.query(l, r); }
};

struct DisjointTester : public StaticRMQTesterBase {
    DisjointTable<int, minf> table;

    void setup(V<int> a) final {
        table = get_disjoint_table(a, int(TEN(9) + TEN(6)), minf());
    }
    int range_min(int l, int r) final { return table.query(l, r); }
};

auto minl = [](int a, int b) { return min(a, b); };

struct LambdaLowMemorySparseTableTester : public StaticRMQTesterBase {
    struct Table {
        LowMemorySparseTable<int, decltype(minl)> table;
        Table(V<int> a)
            : table(
                  get_low_memory_sparse_table(a, int(TEN(9) + TEN(6)), minl)) {}
    } * table;
    void setup(V<int> a) final { table = new Table(a); }
    int range_min(int l, int r) final { return table->table.query(l, r); }
};

using StaticRMQTypes = ::testing::Types<SparseTableTester,
                                        LowMemorySparseTableTester,
                                        DisjointTester,
                                        LambdaLowMemorySparseTableTester>;
INSTANTIATE_TYPED_TEST_CASE_P(StaticRMQ, StaticRMQTest, StaticRMQTypes);
