#include "gtest/gtest.h"
#include "algotest/math/prime_test.h"

using namespace algotest;

#include "base.h"
#include "bitop.h"
#include "math/primitive.h"
#include "util/random.h"
#include "math/prime.h"

struct PrimeTester : public PrimeTesterBase {
    bool is_prime(ll x) final {
        return ::is_prime(x);
    }
    V<ll> factor(ll x) final {
        return pollard(x);
    }
};

using PrimeTypes = ::testing::Types<PrimeTester>;
INSTANTIATE_TYPED_TEST_CASE_P(MyPrime, PrimeTest, PrimeTypes);
