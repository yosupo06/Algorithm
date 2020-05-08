#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "datastructure/linkcuttree.hpp"

struct Node {
    using D = ll;
    static D e_d() {
        return 0;
    }
    static D op_dd(const D& l, const D& r) {
        return l + r;
    }
    static D rev(const D& x) {
        return x;
    }
};

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    V<LCNode<Node>> lct(n);
    for (int i = 0; i < n; i++) {
        ll a;
        sc.read(a);
        lct[i].init_node(a);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        sc.read(u, v);
        lct[u].link(&(lct[v]));
    }
    for (int i = 0; i < q; i++) {
        int t;
        sc.read(t);
        if (t == 0) {
            int p; ll x;
            sc.read(p, x);
            lct[p].expose();
            lct[p].single_add(x);
        } else {
            int u, v;
            sc.read(u, v);
            lct[u].evert();
            lct[v].expose();
            pr.writeln(lct[v].sm);
        }
    }
    return 0;
}
