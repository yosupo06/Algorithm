#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "datastructure/fenwick2d.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    using P = pair<int, int>;
    V<P> ps(n);
    V<ll> w(n);
    for (int i = 0; i < n; i++) {
        sc.read(ps[i].first, ps[i].second, w[i]);
    }
    auto f2d = Fenwick2D<ll, int>(ps);
    for (int i = 0; i < n; i++) {
        f2d.add(ps[i], w[i]);
    }
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        sc.read(l, d, r, u);
        pr.writeln(f2d.sum({l, d}, {r, u}));
    }
    return 0;
}
