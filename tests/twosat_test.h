#include "gtest/gtest.h"

TEST(SATTest, ManyRandom) {
    for (int i = 0; i < 1000; i++) {
        int n = rand_int(1, 50);
        int m = rand_int(1, 100);
        V<bool> ans(n);
        auto sat = TwoSat(n);
        for (int i = 0; i < n; i++) {
            ans[i] = rand_int(0, 1) == 1;
        }
        struct N {int i; bool expect;};
        using A = array<N, 2>;
        V<A> conds;
        for (int i = 0; i < m; i++) {
            int x = rand_int(0, n-1);
            int y = rand_int(0, n-1);
            while (true) {
                bool f = rand_int(0, 1) == 1;
                bool g = rand_int(0, 1) == 1;
                if (ans[x] != f && ans[y] != g) continue;
                sat.add_cond(x, f, y, g);
                conds.push_back(A{{N{x, f}, N{y, g}}});
                break;
            }
        }
        EXPECT_TRUE(sat.exec());
        auto res = sat.res;
        for (auto cond: conds) {
            int x = cond[0].i;
            bool f = cond[0].expect;
            int y = cond[1].i;
            bool g = cond[1].expect;
            EXPECT_TRUE(res[x] == f || res[y] == g);
        }
    }
}
