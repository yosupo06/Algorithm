#define PROBLEM "https://judge.yosupo.jp/problem/tree_decomposition_width_2"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "graph/treedecomp.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    string s;
    sc.read(s, s);
    int n, m;
    sc.read(n, m);
    VV<SimpleEdge> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        sc.read(a, b); a--; b--;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    auto td = decomp_width2(g);
    int K = int(td.bags.size());
    if (K == 0) {
        pr.writeln(-1);
        return 0;
    }
    pr.writeln("s", "td", K, 2, n);

    for (int i = 0; i < K; i++) {
        pr.write("b", i + 1);
        for (int j: td.bags[i]) {
            pr.write(' ');
            pr.write(j + 1);
        }
        pr.writeln();
    }
    for (int i = 0; i < K; i++) {
        for (auto e: td.tr[i]) {
            int j = e.to;
            if (i < j) {
                pr.writeln(i + 1, j + 1);
            }
        }
    }
    return 0;
}
