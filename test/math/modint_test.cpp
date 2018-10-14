#include "gtest/gtest.h"
#include "base.h"
#include "math/modint.h"

TEST(ModIntYosupo, Usage) {
    const int MD = 13;
    using Mint = ModInt<MD>;

    Mint a = 5, b = 10;
    ASSERT_EQ((a+b).v, 2); // (100 + 10) % 107 == 3
    ASSERT_EQ((a-b).v, 8); // (100 - 10) % 107 == 90
    ASSERT_EQ((a*b).v, 11); // (100 - 10) % 107 == 90
    ASSERT_EQ((a/b).v, 7); // (100 - 10) % 107 == 90
    ASSERT_EQ(Mint(2).pow(4).v, 3);
}
