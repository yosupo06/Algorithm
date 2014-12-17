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
        Node(NP l, NP r, int sz = 0) :l(l), r(r), sz(sz) {} 
        void push() {
            if (l->sz) {
                l->v += lz;
                l->mi += lz;
                l->lz += lz;
            }
            if (r->sz) {
                r->v += lz;
                r->mi += lz;
                r->lz += lz;
            }
            lz = 0;
            update();
        }
        NP update() {
            sz = 1+l->sz+r->sz;
            if (lz) push();
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
        D getv(int a) {
            if (a == l->sz) return v;
            push();
            if (a < l->sz) {
                return l->getv(a);
            } else {
                return r->getv(a - l->sz - 1);
            }
        }
        void add(int a, int b, D x) {
            if (!sz || b <= 0 || sz <= a) return;
            if (a <= 0 && sz <= b) {
                v += x;
                mi += x;
                lz += x;
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
        void print() {
            if (!sz) return;
            printf("(");
            l->print();
            printf("-(%lld %lld %lld)-", v, mi, lz);
            r->print();
            printf(")");
        }
    } *n;


    static NP built(int l, int r, D d[]) {
        if (l == r) return last;
        int md = (l+r)/2;
        NP x = new Node(d[md]);
        x->l = built(l, md, d);
        x->r = built(md+1, r, d);
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
        if (xor128() % (l->sz + r->sz) < l->sz) {
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

    STree(NP n) : n(n) {}
    STree(int sz, D d[]) {
        n = built(0, sz, d);
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

    ll get(int l, int r) {
        return n->get(l, r);
    }
    ll getv(int l) {
        return n->getv(l);
    }
    void add(int l, int r, D x) {
        return n->add(l, r, x);
    }
    void print() {
        n->print();
        printf("\n");
    }
};
STree::Node STree::last_d = STree::Node(NULL, NULL, 0);
STree::NP STree::last = &last_d;