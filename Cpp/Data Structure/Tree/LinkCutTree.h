/*
Link-Cut Tree
evertが付いている
*/
typedef long long ll;
struct LCNode {
    typedef LCNode* NP;
    static LCNode last_d;
    static NP last;
    NP p, l, r;
    int sz;
    bool rev;
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

    void link(NP r) {
        assert(this != r);
        expose();
        r->expose();
        assert(l == last);
        p = r;
    }

    void cut() {
        expose();
        l->p = NULL;
        l = last;
        update();
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

    typedef int D;
    D up, down;
    D sup, sdown;
    LCNode(bool f) :p(nullptr), l(last), r(last), sz(1) {
        if (f) {
            up = down = sup = sdown = 0;
        } else {
            up = down = sup = sdown = 1;
        }
    }
    LCNode() : l(nullptr), r(nullptr), sz(0) {}
    void revdata() {
        assert(this != last);
        swap(l, r);
        swap(up, down);
        swap(sup, sdown);
        rev ^= true;
    }
    NP update() {
        assert(this != last);
        sz = 1+l->sz+r->sz;
        sup = up; sdown = down;
        if (l->sz) {
            sup += l->sup;
            sdown += l->sdown;
        }
        if (r->sz) {
            sup += r->sup;
            sdown += r->sdown;
        }
        return this;
    }

    D get() {
        expose();
        return sup;
    }
    void set(D upd, D downd) {
        expose();
        up = upd; down = downd;
        update();
    }
};
LCNode LCNode::last_d = LCNode();
LCNode::NP LCNode::last = &last_d;