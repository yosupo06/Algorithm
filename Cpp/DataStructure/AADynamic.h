struct AA {
    using NP = AA*;

    int ma, lz;

    NP l, r;
    int sz; int lv;
    bool isL; // is last
    AA(int sz, int lz) : l(nullptr), r(nullptr), sz(sz), lv(0), isL(true) {
        this->ma = this->lz = lz;
    }
    AA(NP l, NP r, int lv) : l(l), r(r), lv(lv), isL(false) {
        lz = 0;
        update();
    }
    void update() {
        assert(!lz);
        sz = l->sz + r->sz;

        ma = max(l->ma, r->ma);
    }
    void push() {
        if (lz) {
            if (l->sz) {
                l->lzdata(lz);
            }
            if (r->sz) {
                r->lzdata(lz);
            }
            lz = 0;
        }
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }
    static NP skew(NP n) {
        if (n->l == nullptr || n->lv != n->l->lv) return n;
        NP L = n->l;
        n->l = L->r;
        n->update();
        L->r = n;
        L->update();
        return L;
    }
    static NP pull(NP n) {
        if (n->r == nullptr || n->lv != n->r->lv) return n;
        if (n->r->r == nullptr || n->lv != n->r->r->lv) return n;
        NP R = n->r;
        n->r = R->l;
        n->update();
        R->l = n;
        R->lv++;
        R->update();
        return R;
    }
    static NP inscut(NP n, int k) {
        if (k == 0 || k == n->sz) return n;
        if (n->isL) {
            NP nn = new AA(new AA(k, n->lz), new AA(n->sz - k, n->lz), 1);
            delete n;
            return nn;
        }
        n->push();
        if (k <= n->l->sz) {
            n->l = inscut(n->l, k);
            n->update();
            return pull(skew(n));
        } else {
            n->r = inscut(n->r, k - n->l->sz);
            n->update();
            return pull(skew(n));
        }
    }
    static void add(NP n, int a, int b, int x) {
        if (b <= 0 || n->sz <= a) return;
        if (a <= 0 && n->sz <= b) {
            n->lzdata(x);
            return;
        }
        n->push();
        add(n->l, a, b, x);
        add(n->r, a - n->l->sz, b - n->l->sz, x);
        n->update();
    }

    static int sea(NP n, int k) {
        if (n->ma < k) return -1;
        if (n->isL) {
            return n->sz - 1;
        }
        n->push();
        if (k <= n->r->ma) {
            return n->l->sz + sea(n->r, k);
        } else {
            return sea(n->l, k);
        }
    }
};
