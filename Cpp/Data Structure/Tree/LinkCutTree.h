//木の根を変える、LCAを求めるに対応したLCTree 一番Basic
typedef long long ll;
struct LCNode {
    typedef LCNode* NP;
    typedef int D;
    static const int INF = 1LL<<25;
    static LCNode last_d;
    static NP last;
    NP p, l, r;
    int sz;
    D id;
    bool rev;
    LCNode(D v) :p(NULL), l(last), r(last), sz(1), id(v) {}
    LCNode() : l(NULL), r(NULL), sz(0) {}
    inline int pos() {
        if (p) {
            if (p->l == this) return -1;
            if (p->r == this) return 1;
        }
        return 0;
    }
    void rot() {
        NP qq = p->p;
        int pps = p->pos();
        if (p->l == this) {
            p->l = r; r->p = p;
            r = p; p->p = this;
        } else {
            p->r = l; l->p = p;
            l = p; p->p = this;
        }
        p->update(); update();
        p = qq;
        if (!pps) return;
        if (pps == -1) {
            qq->l = this;
        } else {
            qq->r = this;
        }
        qq->update();
    }
    void splay() {
        assert(this != last);
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
        if (pos()) {
            p->supush();
        }
        push();
    }
    void push() {
        int lsz = l->sz, rsz = r->sz;
        if (rev) {
            if (lsz) {
                l->revdata();
            }
            if (rsz) {
                r->revdata();
            }
            rev = false;
        }
    }
    void revdata() {
        assert(this != last);
        swap(l, r);
        rev ^= true;
    }
    NP update() {
        assert(this != last);
        sz = 1+l->sz+r->sz;
        return this;
    }

    NP root() {
        expose();
        NP u = this;
        while (u->l != last) {
            u = u->l;
        }
        u->splay();
        return u;
    }

    void evert() {
        expose();
        revdata();
    }

    D lca(LCNode &r) {
        r.expose();
        expose();
        NP u = &r;
        while (u->pos()) {
            u = u->p;
        }
        if (u == this) return r.id;
        NP x = last;
        while (u) {
            if (!u->pos()) x = u->p;
            u = u->p;
        }
        if (u == this) return x->id;
        return -1;
    }
};
LCNode LCNode::last_d = LCNode();
LCNode::NP LCNode::last = &last_d;