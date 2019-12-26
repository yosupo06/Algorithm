#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"

#include "base.h"
#include "util/fast_io.h"
#include "graph/maxclique.h"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int n, m;
    sc.read(n, m);
    VV<int> graph(n, V<int>(n, 1));
    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        sc.read(a, b);
        graph[a][b] = graph[b][a] = 0;
    }

    struct E {
        int to;
    };
    VV<E> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) g[i].push_back({j});
        }
    }

    auto answer = MaxClique<40, E>(g).clique;

    int x = int(answer.size());
    pr.writeln(x);
    for (int i = 0; i < x; i++) {
        pr.write(answer[i]);
        if (i != x - 1) pr.write(" ");
    }
    pr.writeln();
}
