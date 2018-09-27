#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "math.h"
#include "prime.h"

bool eq_v(V<ll> v, V<ll> w) {
    if (v.size() != w.size()) return false;
    sort(begin(v), end(v));
    sort(begin(w), end(w));
    int n = int(v.size());
    for (int i = 0; i < n; i++) {
        if (v[i] != w[i]) return false;
    }
    return true;
}

TEST(PrimeYosupo, Usage) {
    ASSERT_FALSE(is_prime(0));
    ASSERT_FALSE(is_prime(1));
    ASSERT_TRUE(is_prime(2));
    ASSERT_TRUE(is_prime(3));
    ASSERT_FALSE(is_prime(4));
    ASSERT_TRUE(is_prime(5));
    ASSERT_TRUE(is_prime(TEN(9)+7));
    ASSERT_FALSE(is_prime((TEN(9)+7)*(TEN(9)+9)));

    ASSERT_TRUE(eq_v(pollard(12), {2, 2, 3}));
    ASSERT_TRUE(eq_v(pollard((TEN(9)+7)*(TEN(9)+9)), {TEN(9)+7, TEN(9)+9}));
}
