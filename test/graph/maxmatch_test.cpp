#include "gtest/gtest.h"
#include "base.h"
#include "util/random.h"
#include "util/ostream.h"
#include "graph/maxmatching.h"

template<class E>
struct MaxMatchingNaive {
    int n;
    const VV<E>& g;
    V<int> mt;
    MaxMatchingNaive(const VV<E>& _g) : n(int(_g.size())), g(_g), mt(n, -1) {
        while (arg()) {};
    }
    bool arg() {
        V<int> ty(n), rt(n, -1), gr(n, -1), nw(n, -1);

        queue<int> q; // 偶点用のqueue
        for (int i = 0; i < n; i++) {
            if (mt[i] == -1) {
                rt[i] = gr[i] = i; // 木での根, 基点
                ty[i] = -1;
                q.push(i);
            }
        }

        // uからのパスを返す
        auto get_path = [&](int u) {
            V<int> v;
            while (rt[u] != u) {
                v.push_back(u);
                v.push_back(mt[u]);
                u = nw[mt[u]];
            }
            v.push_back(u);
            return v;
        };

        while (q.size()) {
            int a = q.front(); q.pop();
            for (auto e: g[a]) {
                int b = e.to;
                if (ty[b] == 1) continue; // 辺が無い or 奇点ならスルー
                if (ty[b] == -1 and gr[a] == gr[b]) continue; // 偶点でもgropが同じならスルー
                if (ty[b] == 0) {
                    // つなぐ
                    int c = mt[b];
                    nw[b] = a; nw[c] = -1;
                    rt[b] = rt[c] = rt[a];
                    gr[b] = b; gr[c] = c;
                    ty[b] = 1; ty[c] = -1;
                    q.push(c);
                    continue;
                }
                if (rt[a] != rt[b]) {
                    // パスを見つける
                    for (int c: {a, b}) {
                        auto v = get_path(c);
                        int m = int(v.size());
                        assert(m % 2 == 1);
                        for (int i = 1; i < m; i += 2) {
                            mt[v[i]] = v[i+1];
                            mt[v[i+1]] = v[i];
                        }
                    }
                    mt[a] = b; mt[b] = a;
                    return true;
                }
                // 潰す
                auto v1 = get_path(a);
                auto v2 = get_path(b);
                reverse(v1.begin(), v1.end());
                reverse(v2.begin(), v2.end());
                assert(v1[0] == v2[0]);
                int m = min(v1.size(), v2.size()), lca;
                for (int i = 1; i <= m; i++) {
                    if (i == m || v1[i] != v2[i]) {
                        lca = gr[v1[i-1]]; // LCA
                        break;
                    }
                }
                V<bool> used(n);
                for (int c: {a, b}) {
                    auto v = get_path(c);
                    for (int i = 0; gr[v[i]] != lca; i += 2) {
                        used[gr[v[i]]] = used[gr[v[i+1]]] = true;
                        if (ty[v[i+1]] == 1) {
                            ty[v[i+1]] = -1;
                            q.push(v[i+1]);
                        }
                        if (i) nw[v[i]] = v[i-1];
                    }
                }
                if (gr[a] != lca) nw[a] = b;
                if (gr[b] != lca) nw[b] = a;
                for (int i = 0; i < n; i++) {
                    if (ty[i] && used[gr[i]]) {
                        gr[i] = lca;
                    }
                }
            }
        }
        return false;
    }
};

int check_mt(const VV<int>& mp, const V<int>& mt) {
    int n = int(mt.size());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (mt[i] == -1) continue;
        if (mt[i] == i || mt[mt[i]] != i || !mp[i][mt[i]]) {
            cerr << mt << endl;
            cerr << (mt[i] == i) << " " << (mt[mt[i]] != i) << " " << mp[i][mt[i]] << endl;
            return -1;
        }
        ans++;
    }
    return ans / 2;
}

TEST(MatchingTest, ManyRandom) {
    Random gen;
    struct E {
        int to;
    };

    for (int ph = 0; ph < 100000; ph++) {
        int n = gen.uniform(2, 20);
        int m = gen.uniform(0, 30);
        VV<int> mp(n, V<int>(n));
        VV<E> g(n);

        for (int i = 0; i < m; i++) {
            int x, y;
            while (true) {
                x = gen.uniform(0, n-1);
                y = gen.uniform(0, n-1);
                if (x == y) continue;
                break;
            }
            if (mp[x][y]) continue;
            mp[x][y] = mp[y][x] = true;
            g[x].push_back({y});
            g[y].push_back({x});
        }

        auto res1 = MaxMatching<E>(g).mt;
        auto res2 = MaxMatchingNaive<E>(g).mt;

        int v1 = check_mt(mp, res1);
        int v2 = check_mt(mp, res2);

        if (v1 == -1) {
            for (int i = 0; i < n; i++) {
                for (E e: g[i]) {
                    int j = e.to;
                    if (i > j) continue;
                    cout << i << ", " << j << endl;
                }
            }
        }
        EXPECT_NE(v1, -1);
        EXPECT_NE(v2, -1);
        EXPECT_EQ(v1, v2);
    }
}
