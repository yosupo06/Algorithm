#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "src/base.h"
#include "src/util/fast_io.h"
#include "src/tree/hl.h"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    struct E { int to; };
    VV<E> g(n);
    for (int i = 1; i < n; i++) {
        int p;
        sc.read(p);
        g[p].push_back({i});
        g[i].push_back({p});
    }
    auto hl = get_hl(g, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        sc.read(u, v);
        auto lca_id = hl.lca(u, v);
        pr.writeln(lca_id);
    }
    return 0;
}
