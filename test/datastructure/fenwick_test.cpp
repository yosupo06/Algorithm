#include "gtest/gtest.h"
#include "algotest/datastructure/fenwick_test.h"

using namespace algotest;

#include "base.h"
#include "datastructure/fenwick.h"

struct FenwickTester : public FenwickTesterBase {
    Fenwick<ll> fw;
    void setup(V<ll> a) final {
        int n = int(a.size());
        fw = Fenwick<ll>(n);
        for (int i = 0; i < n; i++) {
            fw.add(i, a[i]);
        }
    }
    void add(int k, ll x) final {
        fw.add(k, x);
    }
    ll sum(int l, int r) final {
        return fw.sum(l, r);
    }
};

using FenwickTypes = ::testing::Types<FenwickTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyWavelet, FenwickTest, FenwickTypes);
