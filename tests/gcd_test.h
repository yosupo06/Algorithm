#include "gtest/gtest.h"

ll gcd2(ll a, ll b) {
    a = abs(a); b = abs(b);
    if (b == 0) return a;
    return gcd2(b, a%b);
}

TEST(GCDTest, GCDTest) {
    for (int i = -100; i < 100; i++) {
        for (int j = -100; j < 100; j++) {
            EXPECT_EQ(gcd(i, j), gcd2(i, j));
        }
    }
}
