/**
 * Link-Cut Tree
 *
 * 機能としては、link、cut、evert、parent, rootを実装済み
 * 辺に値を持たせたい場合は頂点倍加
 */
struct LCNode {
    using NP = LCNode*;
    static NP last;

    ll tsz, tszsm;
    ll tsm;
    ll d;
    ll dsm;
    ll lsm, rsm;
    NP init_last() {
        sz = 0;
        tsz = tszsm = tsm = d = dsm = lsm = rsm = 0;
        return this;
    }
    void init_node(int d) {
        sz = 1;
        rev = false;
        tsz = 0;
        tszsm = 0;
        tsm = 0;
        this->d = d;
        dsm = d;
        lsm = rsm = 0;
    }
    void update() {
        int lsz = (l != last) ? l->sz : 0, rsz = (r != last) ? r->sz : 0;
        sz = 1 + l->sz + r->sz;
        tszsm = tsz + l->tszsm + r->tszsm;
        dsm = d + l->dsm + r->dsm;
        lsm = l->lsm + l->dsm * tsz + tsm + (l->dsm + d) * r->tszsm + r->lsm;
        rsm = r->rsm + r->dsm * tsz + tsm + (r->dsm + d) * l->tszsm + l->rsm;
    }
    void cngchsz(int x) {
        tsz += x;
        tszsm += x;
    }
    void addch(NP b) {
        assert(b == last || b->p == this);
        cngchsz(b->tszsm);
        tsm += b->lsm + (d) * b->tszsm;
    }
    void delch(NP b) {
        assert(b == last || b->p == this);
        cngchsz(-b->tszsm);
        tsm -= b->lsm + (d) * b->tszsm;
    }
    void push() {
        if (rev) {
            if (l != last) {
                l->revdata();
            }
            if (r != last) {
                r->revdata();
            }
            rev = false;
        }
    }
    void revdata() {
        swap(l, r);
        swap(lsm, rsm);
        rev ^= true;
    }

    NP get(int x) {
        push();
        int rszsm = (r != last) ? r->tszsm : 0;
        if (r != last && x <= rszsm) return r->get(x);
        if (x <= tsz + rszsm) {
            splay();
            return this;
        }
        if (l != last) return l->get(x - (tsz + rszsm));
        return nullptr;
    }

    //ここから
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
        if (pps == -1) {
            q->l = this;
        }
        if (pps == 1) {
            q->r = this;
        }
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
        for (NP u = this; u; u = u->p) {
            u->splay();
        }
        for (NP u = this, ur = last; u; u = u->p) {
            NP tmp = u->r;
            u->r = last;
            u->update();
            u->addch(tmp);
            u->delch(ur);
            u->r = ur;
            u->update();
            ur = u;
        }
        splay();
    }
    void supush() {
        if (pos()) {
            p->supush();
        }
        push();
    }
    //ここまでは絶対必要

    void link(NP r) {
        expose();
        r->expose();
        p = r;
        r->addch(this);
    }

    NP parent() {
        expose();
        NP u = this->l;
        if (u == last) return last;
        u->push();
        while (u->r) {
            u = u->r;
            u->push();
        }
        u->expose();
        return u;
    }

    void cut() {
        NP u = parent();
        assert(u != last);
        assert(u->r == last);
        u->delch(this);
        this->p = nullptr;
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
LCNode::NP LCNode::last = (new LCNode())->init_last();
