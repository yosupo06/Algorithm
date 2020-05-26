#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "datastructure/unionfind.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    auto uf = UnionFind(n);
    for (int i = 0; i < q; i++) {
        int t, u, v;
        sc.read(t, u, v);
        if (t == 0) {
            uf.merge(u, v);
        } else {
            pr.writeln(uf.same(u, v) ? 1 : 0);
        }
    }
    return 0;
}
