#include "gtest/gtest.h"
#include "algotest/math/gcd_test.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "math/math.h"

struct GCDTester : public GCDTesterBase {
    /// gcd(x, y)を返す (|x|, |y| <= 1e18)
    ll gcd(ll x, ll y) final {
        return ::gcd(x, y);
    }
    /// p.first * x + p.second * y = gcd(x, y)なるpairを返す (|x|, |y| <= 1e18)
    pair<ll, ll> ext_gcd(ll x, ll y) final {
        auto g = ::ext_gcd(x, y);
        return make_pair(g.x, g.y);
    }
};

using GCDTypes = ::testing::Types<GCDTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyGCD, GCDTest, GCDTypes);
