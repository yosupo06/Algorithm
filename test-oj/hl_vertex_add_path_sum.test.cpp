#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "base.h"
#include "datastructure/segtree.h"
#include "tree/hl.h"
#include "util/fast_io.h"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    V<ll> a(n);
    for (int i = 0; i < n; i++) {
        sc.read(a[i]);
    }
    struct E {
        int to;
    };
    VV<E> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        sc.read(u, v);
        g[u].push_back({v});
        g[v].push_back({u});
    }
    auto hl = get_hl(g, 0);
    auto seg =
        get_simple_seg(V<ll>(n, 0), 0LL, [&](ll x, ll y) { return x + y; });
    for (int i = 0; i < n; i++) {
        seg.set(hl.ord(i), a[i]);
    }
    for (int i = 0; i < q; i++) {
        int t;
        sc.read(t);
        if (t == 0) {
            int p;
            ll x;
            sc.read(p, x);
            seg.set(hl.ord(p), seg.single(hl.ord(p)) + x);
        } else {
            int u, v;
            sc.read(u, v);
            int l = hl.lca(u, v);
            ll sm = seg.single(hl.ord(l));
            hl.get_path(l, u, [&](int x, int y) { sm += seg.sum(x, y + 1); });
            hl.get_path(l, v, [&](int x, int y) { sm += seg.sum(x, y + 1); });
            pr.writeln(sm);
        }
    }
    return 0;
}
