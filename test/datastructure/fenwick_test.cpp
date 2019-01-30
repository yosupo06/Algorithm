#include "algotest/datastructure/fenwick_test.h"
#include "gtest/gtest.h"

using namespace algotest;

#include "base.h"
#include "datastructure/fenwick.h"
#include "datastructure/segtree.h"

struct FenwickTester : public FenwickTesterBase {
    Fenwick<ll> fw;
    void setup(V<ll> a) final {
        int n = int(a.size());
        fw = Fenwick<ll>(n);
        for (int i = 0; i < n; i++) {
            fw.add(i, a[i]);
        }
    }
    void add(int k, ll x) final { fw.add(k, x); }
    ll sum(int l, int r) final { return fw.sum(l, r); }
};

struct OP {
    ll operator()(ll a, ll b) const { return a + b; }
};
struct SimpleSegTester : public FenwickTesterBase {
    SimpleSeg<ll, OP> seg = SimpleSeg<ll, OP>(V<ll>(), 0LL, OP());
    void setup(V<ll> a) final { seg = get_simple_seg(a, 0LL, OP()); }
    void add(int k, ll x) final { seg.set(k, seg.single(k) + x); }
    ll sum(int l, int r) final { return seg.sum(l, r); }
};

using FenwickTypes = ::testing::Types<FenwickTester, SimpleSegTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyFenwick, FenwickTest, FenwickTypes);
