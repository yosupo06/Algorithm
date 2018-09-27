#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "graph/scc.h"

TEST(SCCYosupoTest, Usage) {
    struct E { int to; };

    // 3 -> (0, 1, 2) -> 4
    VV<E> g(5);
    g[0].push_back(E{1});
    g[1].push_back(E{2});
    g[2].push_back(E{0});
    g[3].push_back(E{1});
    g[0].push_back(E{4});

    auto scc = get_scc(g);

    // id[i] is i's scc number(it is topological order)
    ASSERT_EQ(scc.id, V<int>({1, 1, 1, 0, 2}));

    // groups[i] is vertexes s.t. those group is i
    ASSERT_EQ(scc.groups[0], V<int>({3}));
    ASSERT_EQ(set<int>(scc.groups[1].begin(), scc.groups[1].end()), set<int>({0, 1, 2}));
    ASSERT_EQ(scc.groups[2], V<int>({4}));
}

TEST(SCCYosupoTest, ManyRandom) {
    struct E {
        int to;
    };
    auto f = [&] {
        int n = rand_int(1, 50);
        int p = rand_int(1, 50);
        VV<E> g(n);
        VV<bool> naive(n, V<bool>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (rand_int(0, 99) < p) {
                    g[i].push_back(E{j});
                    naive[i][j] = true;
                }
            }
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (naive[i][k] && naive[k][j]) naive[i][j] = true;
                }
            }
        }
        auto scci = get_scc(g);

        for (int i = 0; i < n; i++) {
            int iid = scci.id[i];
            ASSERT_NE(find(begin(scci.groups[iid]), end(scci.groups[iid]), i), end(scci.groups[iid]));
            for (int j = i+1; j < n; j++) {
                bool same = scci.id[i] == scci.id[j];
                if (same) {
                    ASSERT_TRUE(naive[i][j] && naive[j][i]);
                } else {
                    ASSERT_TRUE(!naive[i][j] || !naive[j][i]);
                    if (scci.id[i] < scci.id[j]) {
                        ASSERT_FALSE(naive[j][i]);
                    } else {
                        ASSERT_FALSE(naive[i][j]);
                    }
                }
            }
        }
    };
    for (int ph = 0; ph < 100; ph++) f();
}
