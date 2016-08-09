/*
RBSTで書かれたStarry Sky Tree
*/

struct STree {
    using D = ll;
    const static D INF = 1LL<<55;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        D v, mi, lz;
        Node(D v) :l(last), r(last), sz(1), v(v), mi(v), lz(0) {}
        Node() :l(nullptr), r(nullptr), sz(0) {} //last用
        void push() {
            assert(this != last);
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
        void lzdata(D d) {
            v += d;
            mi += d;
            lz += d;
        }
        NP update() {
            assert(this != last);
            sz = 1+l->sz+r->sz;
            assert(!lz);
            mi = v;
            if (l->sz) {
                mi = min(mi, l->mi);
            }
            if (r->sz) {
                mi = min(mi, r->mi);
            }
            return this;
        }
        D get(int a, int b) {
            if (!sz || b <= 0 || sz <= a) return INF;
            if (a <= 0 && sz <= b) return mi;
            push();
            D res = INF;
            if (a <= l->sz && l->sz < b) res = min(res, v);
            res = min(res, l->get(a, b));
            res = min(res, r->get(a- l->sz - 1, b- l->sz - 1));
            return res;
        }
        void add(int a, int b, D x) {
            if (!sz || b <= 0 || sz <= a) return;
            if (a <= 0 && sz <= b) {
                lzdata(x);
                return;
            }
            push();
            l->add(a, b, x);
            if (a <= l->sz && l->sz < b) {
                v += x;
            }
            r->add(a- l->sz - 1, b- l->sz - 1, x);
            update();
        }
    } *n;


    static NP built(int sz, D d[]) {
        if (!sz) return last;
        int md = sz/2;
        NP x = new Node(d[md]);
        x->l = built(md, d);
        x->r = built(sz-(md+1), d+(md+1));
        return x->update();
    }

    static uint xor128(){
        static uint x=123456789,y=362436069,z=521288629,w=88675123;
        uint t;
        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
    }
    static NP merge(NP l, NP r) {
        if (!l->sz) return r;
        if (!r->sz) return l; 
        l->push(); r->push();
        if ((int)(xor128() % (l->sz + r->sz)) < l->sz) {
            l->r = merge(l->r, r);
            return l->update();
        } else {
            r->l = merge(l, r->l);
            return r->update();
        }
    }
    static pair<NP, NP> split(NP x, int k) {
        if (!x->sz) return {last, last};
        x->push();
        if (k <= x->l->sz) {
            auto y = split(x->l, k);
            x->l = y.second;
            y.second = x->update();
            return y;
        } else {
            auto y = split(x->r, k- x->l->sz -1);
            x->r = y.first;
            y.first = x->update();
            return y;
        }
    }
    STree() : n(last) {}
    STree(NP n) : n(n) {}
    STree(D d) : n(new Node(d)) {}
    STree(int sz, D d[]) {
        n = built(sz, d);
    }
    int sz() {
        return n->sz;
    }
    void merge(STree r) {
        n = merge(n, r.n);
    }
    STree split(int k) {
        auto u = split(n, k);
        n = u.first;
        return STree(u.second);
    }
    void insert(int k, D x) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(x)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, split(u.second, 1).second);
    }
    void add(int l, int r, D x) {
        return n->add(l, r, x);
    }
    D get(int l, int r) {
        return n->get(l, r);
    }
};
STree::Node STree::last_d = STree::Node();
STree::NP STree::last = &last_d;