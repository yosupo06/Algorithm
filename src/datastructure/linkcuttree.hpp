template <class N> struct LCNode {
    using NP = LCNode*;
    using D = typename N::D;
    NP p = nullptr, l = nullptr, r = nullptr;
    int sz = 1;
    bool rev = false;
    D v = N::e_d(), sm = N::e_d();

    void single_set(D x) {
        v = x;
        update();
    }
    void single_add(D x) {
        v = N::op_dd(v, x);
        update();
    }

    void init_node(D _v) {
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
        sm = N::rev(sm);
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
    // 親としてnpを接続する
    void link(NP np) {
        evert();
        np->expose();
        p = np;
    }
    // 親から自分を切り離す
    void cut() {
        expose();
        assert(l);
        l->p = nullptr;
        l = nullptr;
        update();
    }
    void evert() {
        expose();
        revdata();
    }

    NP lca(NP n) {
        n->expose();
        expose();
        NP t = n;
        while (n->p != nullptr) {
            if (!n->pos()) t = n->p;
            n = n->p;
        }
        return (this == n) ? t : nullptr;
    }
};
