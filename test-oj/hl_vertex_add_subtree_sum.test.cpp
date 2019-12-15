#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

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
    for (int i = 1; i < n; i++) {
        int p;
        sc.read(p);
        g[i].push_back({p});
        g[p].push_back({i});
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
            int u;
            sc.read(u);
            ll sm = seg.sum(hl.ord(u), hl.out[hl.ord(u)]);
            pr.writeln(sm);
        }
    }
    return 0;
}
