struct LCTree {
    typedef int D;
    static const int INF = 1LL<<25;
    struct Node;
    typedef Node* NP;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz;
        int v, sm, lz;
        int lsm, rsm, ma, mv;
        bool rev;
        Node(D v) :p(NULL), l(last), r(last), sz(1),
            v(v), sm(v), lz(INF), rev(false),
            lsm(max(v, 0)), rsm(max(v, 0)), ma(max(v, 0)), mv(v) {}
        Node(NP l, NP r) : l(l), r(r), sz(0), mv(-INF) {}
        inline int pos() {
            if (p && p->l == this) return -1;
            if (p && p->r == this) return 1;
            return 0;
        }
        void rot() {
            NP q = p, qq = q->p;
            int qp = q->pos();
            if (q->l == this) {
                q->l = r; r->p = q;
                r = q; q->p = this;
            } else {
                q->r = l; l->p = q;
                l = q; q->p = this;
            }
            q->update(); update();
            p = qq;
            if (!qp) return;
            if (qp == -1) {
                qq->l = this;
            } else {
                qq->r = this;
            }
            qq->update();
        }
        void splay() {
            supush();
            while (pos()) {
                int u = pos()*p->pos();
                if (!u) {
                    rot();
                } else if (u == 1) {
                    p->rot(); rot();
                } else {
                    rot(); rot();
                }
            }
        }
        void expose() {
            NP u = this;
            while (u) {
                u->splay();
                u = u->p;
            }
            u = this;
            while (u->p) {
                u->p->r = u;
                u = u->p;
                u->update();
            }
            splay();
        }
        void push() {
            if (rev) {
                swap(l, r);
                if (l->sz) {
                    l->rev ^= true;
                    swap(l->lsm, l->rsm);
                }
                if (r->sz) {
                    r->rev ^= true;
                    swap(r->lsm, r->rsm);
                }
                rev = false;
            }
 
            if (lz != INF) {
                if (l->sz) {
                    l->updata(lz);
                }
                if (r->sz) {
                    r->updata(lz);
                }
                lz = INF;
            }
        }
        void supush() {
            if (pos()) {
                p->supush();
            }
            push();
        }
        void updata(D d) {
            v = d;
            sm = sz*d;
            lz = d;
            lsm = rsm = ma = max(0, sm);
            mv = d;
        }
        NP update() {
            if (this == last) return this;
            sz = 1+l->sz+r->sz;
            sm = v + l->sm + r->sm;
            lsm = max(l->lsm, l->sm+v+r->lsm);
            rsm = max(r->rsm, r->sm+v+l->rsm);
            ma = max(l->ma, r->ma);
            ma = max(ma, l->rsm+v+r->lsm);
            mv = max(l->mv, r->mv);
            mv = max(mv, v);
            return this;
        }
    } *n;
    LCTree() : n(last) {}
    LCTree(NP n) : n(n) {}
    LCTree(D d) : n(new Node(d)) {}
    int sz() {
        return n->sz;
    }
    void event() {
        n->expose();
        n->r = last;
        n->rev = true;
        swap(n->lsm, n->rsm);
    }
    void link(LCTree r) {
        n->expose();
        r.n->expose();
        assert(n->l == last);
        n->p = r.n;
    }
 
    void set(int x) {
        n->expose();
        n->r = last;
        n->update();
        n->updata(x);
    }
    int get() {
        n->expose();
        n->r = last;
        n->update();
        if (n->mv < 0) return n->mv;
        return n->ma;
    }
};
LCTree::Node LCTree::last_d = LCTree::Node((NP)NULL, NULL);
LCTree::NP LCTree::last = &last_d;