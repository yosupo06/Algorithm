#include "gtest/gtest.h"

TEST(MCFTest, ManyRandom) {
    struct E {
        int to, cap, dist, rev;
    };
    VV<E> g;
    auto add_edge = [&](int from, int to, int cap, int dist) {
        g[from].push_back(E{to, cap, dist, int(g[to].size())});
        g[to].push_back(E{from, 0, -dist, int(g[from].size())-1});
    };


    auto f = [&]() {
        int n = rand_int(2, 20);
        int m = rand_int(0, 200);
        int s, t;
        while (true) {
            s = rand_int(0, n-1);
            t = rand_int(0, n-1);
            if (s != t) break;
        }
        g = VV<E>(n);
        auto elist = VV<E>(n);

        for (int i = 0; i < m; i++) {
            int x, y;
            while (true) {
                x = rand_int(0, n-1);
                y = rand_int(0, n-1);
                if (x == y) continue;
                break;
            }
            int c = rand_int(0, 100);
            int d = rand_int(0, 100);
            add_edge(x, y, c, d);
            elist[x].push_back(E{y, c, d, -1});
        }

        auto res = min_cost_flow<int, int>(g, s, t, false);
        res.max_flow(TEN(9));

        int sm = (res.dual[t] - res.dual[s]) * res.cap_flow;
        for (int i = 0; i < n; i++) {
            for (auto e: elist[i]) {
                sm -= max(0, (res.dual[e.to] - res.dual[i]) - e.dist) * e.cap;
            }
        }
        EXPECT_EQ(res.flow, sm);
    };
    for (int i = 0; i < 100; i++) {
        f();
    }
}
