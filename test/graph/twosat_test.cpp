#include "gtest/gtest.h"
#include "base.h"
#include "util/random.h"
#include "graph/scc.h"
#include "graph/twosat.h"

TEST(SATTest, ManyRandom) {
    for (int ph = 0; ph < 1000; ph++) {
        int n = global_gen.uniform(1, 50);
        int m = global_gen.uniform(1, 100);
        V<bool> ans(n);
        auto sat = TwoSat(n);
        for (int i = 0; i < n; i++) {
            ans[i] = global_gen.uniform(0, 1) == 1;
        }
        struct N {int i; bool expect;};
        using A = array<N, 2>;
        V<A> conds;
        for (int i = 0; i < m; i++) {
            int x = global_gen.uniform(0, n-1);
            int y = global_gen.uniform(0, n-1);
            while (true) {
                bool f = global_gen.uniform_bool();
                bool g = global_gen.uniform_bool();
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
