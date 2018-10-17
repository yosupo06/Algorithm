#include "gtest/gtest.h"
#include "algotest/math/nft_test.h"

using namespace algotest;

#include "base.h"
#include "math/modint.h"
#include "fft.h"


struct NFTTester : public NFTTesterBase {
    using Mint = ModInt<NFTTesterBase::kMod>;
    V<ll> multiply(V<ll> _a, V<ll> _b) final {
        V<Mint> a, b;
        for (auto d: _a) a.push_back(Mint(d));
        for (auto d: _b) b.push_back(Mint(d));
        V<Mint> c = ::multiply<NFTTesterBase::kG>(a, b);
        V<ll> _c;
        for (auto d: c) _c.push_back(d.v);
        return _c;
    }
};

struct NFTByFFTTester : public NFTTesterBase {
    using Mint = ModInt<NFTTesterBase::kMod>;
    V<ll> multiply(V<ll> _a, V<ll> _b) final {
            V<Mint> a, b;
            for (auto d: _a) a.push_back(Mint(d));
            for (auto d: _b) b.push_back(Mint(d));
            V<Mint> c = ::multiply(a, b);
            V<ll> _c;
            for (auto d: c) _c.push_back(d.v);
            return _c;
    }
};

using NFTTypes = ::testing::Types<NFTTester, NFTByFFTTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyNFT, NFTTest, NFTTypes);
