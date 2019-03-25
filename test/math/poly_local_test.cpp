#include "gtest/gtest.h"
#include "base.h"
#include "util/ostream.h"
#include "random.h"
#include "math/modint.h"
#include "math/nft.h"
#include "math/poly.h"

const int Mod = 998244353;
using Mint = ModInt<Mod>;
template<> const Mint Mint::G = Mint(3);
using MPoly = Poly<Mint>;

MPoly exp_naive(MPoly po, int n) {
    assert(po.freq(0) == 0);
    MPoly res;
    MPoly fk({1});
    for(int k = 0; k < n; k++){
        res += fk;
        fk *= po;
        fk = fk.pre(n) / (k+1);
    }
    return res;
}

MPoly log_naive(MPoly po, int n) {
    assert(po.freq(0) == 1);
    MPoly res;
    MPoly g({1});
    for (int k = 1; k < n; k++) {
        g *= (MPoly({1}) - po);
        g = g.pre(n);
        res -= g / Mint(k);
    }
    return res;
}

TEST(PolyTest, ExpStressTest) {
    Random gen;
    for (int a_sz = 1; a_sz < 30; a_sz++) {
        for (int b_sz = 1; b_sz < 30; b_sz++) {
            V<Mint> v(a_sz);
            for (int i = 1; i < a_sz; i++) {
                v[i] = gen.uniform(0, Mod - 1);
            }
            auto po = MPoly(v);
            ASSERT_EQ(po.exp(b_sz).v, exp_naive(po, b_sz).v);
        }
    }
}

TEST(PolyTest, LogStressTest) {
    Random gen;
    for (int a_sz = 1; a_sz < 30; a_sz++) {
        for (int b_sz = 1; b_sz < 30; b_sz++) {
            V<Mint> v(a_sz);
            v[0] = 1;
            for (int i = 1; i < a_sz; i++) {
                v[i] = gen.uniform(0, Mod - 1);
            }
            auto po = MPoly(v);
            ASSERT_EQ(po.log(b_sz).v, log_naive(po, b_sz).v);
        }
    }
}
