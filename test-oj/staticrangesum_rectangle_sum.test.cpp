#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "datastructure/staticrangesum.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    V<StaticRangeSum<ll, int>::P> ps(n);
    for (int i = 0; i < n; i++) {
        sc.read(ps[i].x, ps[i].y, ps[i].val);
    }
    auto srs = StaticRangeSum<ll, int>(ps);
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        sc.read(l, d, r, u);
        pr.writeln(srs.sum(l, d, r, u));
    }
    return 0;
}
