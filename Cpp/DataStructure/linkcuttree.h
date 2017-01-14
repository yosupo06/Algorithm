struct LCNode {
    using NP = LCNode*;
    static NP last;
    ll d, dsm, ma;
    ll lz;
    NP init_last() {
        sz = 0; // Important
        lz = 0; // Important
        d = dsm = ma = 0;
        return this;
    }
    void init_node(int d) {
        sz = 1; rev = false; // Important
        lz = 0; // Important
        this->d = dsm = ma = d;
    }
    void update() {
        sz = 1 + l->sz + r->sz; // Important
        dsm = d + l->dsm + r->dsm;
        ma = max(d, max(l->ma, r->ma));
    }
    void push() {
        assert(this != last);
        if (rev) { // Important
            if (l != last) {
                l->revdata();
            }
            if (r != last) {
                r->revdata();
            }
            rev = false;
        }
        if (lz) {
            if (l != last) {
                l->lzdata(lz);
            }
            if (r != last) {
                r->lzdata(lz);
            }
            lz = 0;
        }
    }
    void revdata() {
        rev ^= true; swap(l, r); // Important
    }
    void lzdata(ll x) {
        d += x;
        dsm += x;
        ma += x;
        lz += x;
    }
    
    NP p, l, r;
    int sz;
    bool rev;
    LCNode() : p(nullptr), l(last), r(last) {}
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
        p->update(); update();
        p = q;
        if (q) q->update();
    }
    void splay() {
        supush();
        int ps;
        while ((ps = pos())) {
            int pps = p->pos();
            if (!pps) {
                rot();
            } else if (ps == pps) {
                p->rot(); rot();
            } else {
                rot(); rot();
            }
        }
    }
    void expose() {
        assert(this != last);
        NP u = this, ur = last;
        do {
            u->splay();
            u->r = ur;
            u->update();
            ur = u;
        } while ((u = u->p));
        splay();
    }
    void supush() {
        if (pos()) p->supush();
        push();
    }
    void link(NP r) {
        evert(); r->expose();
        p = r;
    }
    void cut() {
        expose();
        l->p = NULL;
        l = last;
        update();
    }
    void evert() {
        expose(); revdata();
    }

    //tree func
    NP parent() {
        expose();
        NP u = this->l;
        if (u == last) return last;
        u->push();
        while (u->r != last) {
            u = u->r;
            u->push();
        }
        u->expose();
        return u;
    }

    NP root() {
        expose();
        NP u = this;
        while (u->l != last) {
            u = u->l;
            u->push();
        }
        u->expose();
        return u;
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
LCNode::NP LCNode::last = (new LCNode())->init_last();
