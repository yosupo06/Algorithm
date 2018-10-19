#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "graph/mincostflow.h"

TEST(MCFTest, IssueNegative) {
    struct E {
        int to, cap, dist, rev;
    };
    VV<E> g;
    VV<E> elist;
    auto add_edge = [&](int from, int to, int cap, int dist) {
        elist[from].push_back(E{to, cap, dist, -1});
        g[from].push_back(E{to, cap, dist, int(g[to].size())});
        g[to].push_back(E{from, 0, -dist, int(g[from].size())-1});
    };

    int n = 3;
    int s = 1;
    int t = 0;
    g = VV<E>(n); elist = VV<E>(n);
    add_edge(1, 0, 86, 58);
    add_edge(1, 0, 82, 65);
    add_edge(2, 1, 79, 100);
    add_edge(2, 1, 90, 42);
    
    auto res = get_mcf<int, int>(g, s, t, rand_int(0, 1));
    res.max_flow(TEN(9));

    int sm = (res.dual[t] - res.dual[s]) * res.cap_flow;
    for (int i = 0; i < n; i++) {
        for (auto e: elist[i]) {
            if (!e.cap || res.dual[i] == decltype(res)::INF) continue;
            sm -= max(0, (res.dual[e.to] - res.dual[i]) - e.dist) * e.cap;
        }
    }
    EXPECT_EQ(res.flow, sm);
}

TEST(MCFTest, ManyRandomSmall) {
    struct E {
        int to, cap, dist, rev;
    };
    VV<E> g;
    auto add_edge = [&](int from, int to, int cap, int dist) {
        g[from].push_back(E{to, cap, dist, int(g[to].size())});
        g[to].push_back(E{from, 0, -dist, int(g[from].size())-1});
    };


    auto f = [&]() {
        int n = rand_int(2, 4);
        int m = rand_int(0, 7);
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
        auto res = get_mcf<int, int>(g, s, t, rand_int(0, 1));
        res.max_flow(TEN(9));

        int sm = (res.dual[t] - res.dual[s]) * res.cap_flow;
        for (int i = 0; i < n; i++) {
            for (auto e: elist[i]) {
                if (!e.cap || res.dual[i] == decltype(res)::INF) continue;
                sm -= max(0, (res.dual[e.to] - res.dual[i]) - e.dist) * e.cap;
            }
        }
        EXPECT_EQ(res.flow, sm);
    };
    for (int i = 0; i < 10000; i++) {
        f();
    }
}

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

        auto res = get_mcf<int, int>(g, s, t, rand_int(0, 1));
        res.max_flow(TEN(9));

        int sm = (res.dual[t] - res.dual[s]) * res.cap_flow;
        for (int i = 0; i < n; i++) {
            for (auto e: elist[i]) {
                if (!e.cap || res.dual[i] == decltype(res)::INF) continue;
                sm -= max(0, (res.dual[e.to] - res.dual[i]) - e.dist) * e.cap;
            }
        }
        EXPECT_EQ(res.flow, sm);
    };
    for (int i = 0; i < 300; i++) {
        f();
    }
}

TEST(MCFTest, ManyRandomDouble) {
    using D = double;
    struct E {
        int to, cap;
        D dist;
        int rev;
    };
    VV<E> g;
    auto add_edge = [&](int from, int to, int cap, D dist) {
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
            D d = rand_double(0, 100);
            add_edge(x, y, c, d);
            elist[x].push_back(E{y, c, d, -1});
        }

        auto res = get_mcf<int, double>(g, s, t, rand_int(0, 1));
        res.max_flow(TEN(9));

        D sm = (res.dual[t] - res.dual[s]) * res.cap_flow;
        for (int i = 0; i < n; i++) {
            for (auto e: elist[i]) {
                sm -= max(D(0), (res.dual[e.to] - res.dual[i]) - e.dist) * e.cap;
            }
        }
        EXPECT_NEAR(res.flow, sm, 1e-6);
    };
    for (int i = 0; i < 300; i++) {
        f();
    }
}
