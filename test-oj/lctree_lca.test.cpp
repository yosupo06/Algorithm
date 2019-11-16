#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "src/base.h"
#include "src/datastructure/linkcuttree.h"

struct Node {
    using D = ll;
    static D e_d() { return 0; }
    static D op_dd(const D& l, const D& r) { return l + r; }
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
