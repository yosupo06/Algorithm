#include "gtest/gtest.h"

TEST(MFTest, ManyRandom) {
    struct E {
        int to, cap, rev;
    };
    VV<E> g;
    auto add_edge = [&](int from, int to, int cap) {
        g[from].push_back(E{to, cap, int(g[to].size())});
        g[to].push_back(E{from, 0, int(g[from].size())-1});
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
            add_edge(x, y, c);            
            elist[x].push_back(E{y, c, -1});
        }

        auto res = max_flow<int, 0>(g, s, t);
        EXPECT_EQ(res.dual[s], false);
        EXPECT_EQ(res.dual[t], true);

        int sm = 0;
        for (int i = 0; i < n; i++) {
            for (auto e: elist[i]) {
                if (res.dual[i] == false && res.dual[e.to] == true) {
                    sm += e.cap;
                }
            }
        }
        EXPECT_EQ(res.flow, sm);
    };
    for (int i = 0; i < 100; i++) {
        f();
    }
}
