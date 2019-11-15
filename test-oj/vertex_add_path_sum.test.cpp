#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "src/base.h"

template<class N>
struct LCNode {
    using NP = LCNode*;
    using D = typename N::D;
    NP p = nullptr, l = nullptr, r = nullptr;
    int sz = 1;
    bool rev = false;
    D v = N::e_d(), sm = N::e_d();

    void single_add(D x) {
        v = N::op_dd(v, x);
        update();
    }

    void init_node(D _v) {
        sz = 1;
        v = _v;
        sm = _v;
    }    
    void update() {
        sz = 1;
        if (l) sz += l->sz;
        if (r) sz += r->sz;
        sm = l ? N::op_dd(l->sm, v) : v;
        if (r) sm = N::op_dd(sm, r->sm);
    }
    void push() {
        if (rev) {
            if (l) l->revdata();
            if (r) r->revdata();
            rev = false;
        }
    }
    void revdata() {
        rev ^= true;
        swap(l, r);
    }

    inline int pos() {
        if (p) {
            if (p->l == this) return -1;
            if (p->r == this) return 1;
        }
        return 0;
    }
    void rot() {
        NP q = p->p;
        int pps = p->pos();
        if (pps == -1) q->l = this;
        if (pps == 1) q->r = this;
        if (p->l == this) {
            p->l = r;
            if (r) r->p = p;
            r = p;
        } else {
            p->r = l;
            if (l) l->p = p;
            l = p;
        }
        p->p = this;
        p->update();
        update();
        p = q;
        if (q) q->update();
    }
    void all_push() {
        if (pos()) p->all_push();
        push();
    }
    void splay() {
        all_push();
        int ps;
        while ((ps = pos())) {
            int pps = p->pos();
            if (!pps) {
                rot();
            } else if (ps == pps) {
                p->rot();
                rot();
            } else {
                rot();
                rot();
            }
        }
    }
    void expose() {
        NP u = this, ur = nullptr;
        do {
            u->splay();
            u->r = ur;
            u->update();
            ur = u;
        } while ((u = u->p));
        splay();
    }
    void link(NP np) {
        evert();
        np->expose();
        p = np;
    }
    void cut() {
        expose();
        l->p = l = nullptr;
        update();
    }
    void evert() {
        expose();
        revdata();
    }
};

struct Node {
    using D = ll;
    static D e_d() {
        return 0;
    }
    static D op_dd(const D& l, const D& r) {
        return l + r;
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
