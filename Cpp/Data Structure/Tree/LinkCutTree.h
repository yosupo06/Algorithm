/**
 * Link-Cut Tree
 *
 * 機能としては、link、cut、evert、parent, rootを実装済み
 * 辺に値を持たせたい場合は頂点倍加
 */
struct LCNode {
    typedef LCNode* NP;

    typedef int D;
    struct Node {
        bool type;
        bool esz;
        bool up, down;
        bool ups, downs;
        bool ulz, dlz;
    } n;
    LCNode() : l(nullptr), r(nullptr), sz(0), rev(false) {
        n.type = false;
        n.esz = n.up = n.down = n.ups = n.downs = n.ulz = n.dlz = false;

    }
    LCNode(bool t) : p(nullptr), l(last), r(last), sz(1), rev(false) {
        n.type = n.esz = t;
        n.up = n.down = n.ups = n.downs = false;
        n.ulz = n.dlz = false;
    }

    NP update() {
        assert(this != last);
        sz = 1+l->sz+r->sz;
        n.esz = l->n.esz | r->n.esz;
        if (n.type) {
            n.esz = true;
        }
        n.ups = n.up;
        n.downs = n.down;
        if (l->sz) {
            n.ups |= l->n.ups;
            n.downs |= l->n.downs;
        }
        if (r->sz) {
            n.ups |= r->n.ups;
            n.downs |= r->n.downs;
        }
        return this;
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
        if (n.ulz) {
            if (lsz) {
                l->ulzdata();
            }
            if (rsz) {
                r->ulzdata();
            }
            n.ulz = false;
        }
        if (n.dlz) {
            if (lsz) {
                l->dlzdata();
            }
            if (rsz) {
                r->dlzdata();
            }
            n.dlz = false;
        }
    }
    void revdata() {
        assert(this != last);
        swap(l, r);
        swap(n.up, n.down);
        swap(n.ups, n.downs);
        swap(n.ulz, n.dlz);
        rev ^= true;
    }
    void ulzdata() {
        if (!n.esz) return;
        if (n.type) {
            n.up = true;
        }
        n.ups = true;
        n.ulz = true;
    }
    void dlzdata() {
        if (!n.esz) return;
        if (n.type) {
            n.down = true;
        }
        n.downs = true;
        n.dlz = true;
    }

    //ここから
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
    /**
     * splayする前に一括でその頂点のパス木の根までをpushする
     * 唯一stack overflowしうる関数なので注意すること
     */
    void supush() {
        if (pos()) {
            p->supush();
        }
        push();
    }
    //ここまでは絶対必要

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
            u->push();
        }
        u->expose();
        return u;
    }

    NP parent() {
        expose();
        NP u = this->l;
        if (u == last) return nullptr;
        u->push();
        while (u->r != last) {
            u = u->r;
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
LCNode LCNode::last_d = LCNode();
LCNode::NP LCNode::last = &last_d;
