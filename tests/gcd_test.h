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

TEST(XGCDTest, XGCDTest) {
    for (int i = -100; i < 100; i++) {
        for (int j = -100; j < 100; j++) {
            auto u = ext_gcd(i, j);
            EXPECT_EQ(u.g, gcd(i, j));
            EXPECT_EQ(u.x * i + u.y * j, u.g);
        }
    }
}
