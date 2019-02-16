#include "gtest/gtest.h"
#include "algotest/math/fft_test.h"
#include "algotest/math/nft_test.h"

using namespace algotest;

#include "base.h"
#include "math/modint.h"
#include "math/fft.h"

struct DoubleFFTTester : public FFTTesterBase {
    V<ll> multiply(V<ll> _a, V<ll> _b) final {
        V<D> a, b;
        for (auto d: _a) a.push_back(d);
        for (auto d: _b) b.push_back(d);
        auto c = ::multiply(a, b);
        V<ll> _c;
        for (auto d: c) _c.push_back(ll(round(d)));
        return _c;
    }
};

struct ComplexFFTTester : public FFTTesterBase {
    V<ll> multiply(V<ll> _a, V<ll> _b) final {
            V<Pc> a, b;
            for (auto d: _a) a.push_back(Pc(d));
            for (auto d: _b) b.push_back(Pc(d));
            auto c = ::multiply(a, b);
            V<ll> _c;
            for (auto d: c) _c.push_back(ll(round(d.real())));
            return _c;
    }
};

struct NFTByFFTTester : public NFTTesterBase {
    using Mint = ModInt<NFTTesterBase::kMod>;
    V<ll> multiply(V<ll> _a, V<ll> _b) final {
        V<Mint> a, b;
        for (auto d : _a) a.push_back(Mint(d));
        for (auto d : _b) b.push_back(Mint(d));
        V<Mint> c = ::multiply(a, b);
        V<ll> _c;
        for (auto d : c) _c.push_back(d.v);
        return _c;
    }
};


using FFTTypes = ::testing::Types<DoubleFFTTester, ComplexFFTTester>;
using NFTTypes = ::testing::Types<NFTByFFTTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyFFT, FFTTest, FFTTypes);
INSTANTIATE_TYPED_TEST_CASE_P(MyNFT, NFTTest, NFTTypes);
