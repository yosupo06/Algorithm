#include "gtest/gtest.h"
#include "algotest/graph/unionfind_test.h"

using namespace algotest;

#include "base.h"
#include "datastructure/unionfind.h"
#include "datastructure/quickfind.h"
#include "datastructure/smallfind.h"

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

struct SFTester : public UnionFindTesterBase {
    SmallFind<1000> sf;
    UFTester uf;
    bool mode;
    void setup(int n) final {
        mode = n < 1000;
        if (mode) sf = SmallFind<1000>();
        else uf.setup(n);
    }
    void add(int u, int v) final {
        if (mode) sf.merge(u, v);
        else uf.add(u, v);
    }
    bool is_connect(int u, int v) final {
        if (mode) return sf.same(u, v);
        else return uf.is_connect(u, v);
    }
};

using UFTypes = ::testing::Types<UFTester, QFTester, SFTester>;
INSTANTIATE_TYPED_TEST_CASE_P(UF, UnionFindTest, UFTypes);
