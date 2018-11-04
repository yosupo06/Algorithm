#include "gtest/gtest.h"
#include "algotest/math/poly_test.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "math/modint.h"
#include "math/fft.h"
#include "math/poly.h"

struct PolyTester : public PolyTesterBase {
    using Mint = ModInt<PolyTesterBase::kMod>;
    using MPoly = Poly<Mint>;
    V<ll> add(V<ll> _a, V<ll> _b) final {
        V<Mint> a, b;
        for (auto d: _a) a.push_back(Mint(d));
        for (auto d: _b) b.push_back(Mint(d));
        auto c = (MPoly(a) + MPoly(b)).v;
        V<ll> _c;
        for (auto d: c) _c.push_back(d.v);
        return _c;
    }
    V<ll> sub(V<ll> _a, V<ll> _b) final {
        V<Mint> a, b;
        for (auto d: _a) a.push_back(Mint(d));
        for (auto d: _b) b.push_back(Mint(d));
        auto c = (MPoly(a) - MPoly(b)).v;
        V<ll> _c;
        for (auto d: c) _c.push_back(d.v);
        return _c;
    }
    V<ll> mul(V<ll> _a, V<ll> _b) final {
        V<Mint> a, b;
        for (auto d: _a) a.push_back(Mint(d));
        for (auto d: _b) b.push_back(Mint(d));
        auto c = (MPoly(a) * MPoly(b)).v;
        V<ll> _c;
        for (auto d: c) _c.push_back(d.v);
        return _c;
    }
};

using PolyTypes = ::testing::Types<PolyTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyPoly, PolyTest, PolyTypes);
