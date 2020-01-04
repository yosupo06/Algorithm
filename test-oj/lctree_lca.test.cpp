#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "base.h"
#include "util/fast_io.h"
#include "datastructure/linkcuttree.h"

struct Node {
    using D = bool;
    static D e_d() { return false; }
    static D op_dd(const D& l, const D& r) { return false; }
    static D rev(const D& x) { return false; }
};

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    V<LCNode<Node>> lct(n);
    for (int i = 1; i < n; i++) {
        int p;
        sc.read(p);
        lct[i].link(&(lct[p]));
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        sc.read(u, v);
        auto lca_id = int(lct[u].lca(&(lct[v])) - &(lct[0]));
        pr.writeln(lca_id);
    }
    return 0;
}
