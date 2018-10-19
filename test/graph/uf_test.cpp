#include "gtest/gtest.h"
#include "algotest/graph/unionfind_test.h"

using namespace algotest;

#include "base.h"
#include "datastructure/unionfind.h"
#include "datastructure/quickfind.h"

struct UFTester : public UnionFindTesterBase {
    UnionFind uf;
    void setup(int n) final {
        uf = UnionFind(n);
    }
    void add(int u, int v) final {
        uf.merge(u, v);
    }
    bool is_connect(int u, int v) final {
        return uf.same(u, v);
    }
};

struct QFTester : public UnionFindTesterBase {
    QuickFind qf;
    void setup(int n) final {
        qf = QuickFind(n);
    }
    void add(int u, int v) final {
        qf.merge(u, v);
    }
    bool is_connect(int u, int v) final {
        return qf.same(u, v);
    }
};

using UFTypes = ::testing::Types<UFTester, QFTester>;
INSTANTIATE_TYPED_TEST_CASE_P(UF, UnionFindTest, UFTypes);
