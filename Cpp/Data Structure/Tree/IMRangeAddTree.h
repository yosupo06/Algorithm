struct STree {
    struct Node;
    static const int PLS = 13000000;
    static int pc;
    static Node pool[PLS];

    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        ll v, sm, lz;
        static NP make(NP x) {
            pool[pc] = *x;
            pc++;
            return &pool[pc-1];
        }
        static NP make(ll v) {
            pool[pc] = Node(v);
            pc++;
            return &pool[pc-1];
        }
        Node() {}
        Node(ll v) :l(last), r(last), sz(1), v(v), sm(0), lz(0) {}
        Node(NP l, NP r, int sz = 0) :l(l), r(r), sz(sz) {} 
        void push() {
            if (l->sz) {
                l = make(l);
                l->v += lz;
                l->sm += lz*l->sz;
                l->lz += lz;
            }
            if (r->sz) {
                r = make(r);
                r->v += lz;
                r->sm += lz*r->sz;
                r->lz += lz;
            }
            lz = 0;
        }
        NP update() {
            sz = 1+l->sz+r->sz;
            if (lz) push();
            sm = v;
            if (l->sz) {
                sm += l->sm;
            }
            if (r->sz) {
                sm += r->sm;
            }
            return this;
        }
        void add(int a, int b, ll x) {
            if (!sz || b <= 0 || sz <= a) return;
            if (a <= 0 && sz <= b) {
                v += x;
                sm += sz*x;
                lz += x;
                return;
            }
            push();
            l = make(l);
            r = make(r);
            l->add(a, b, x);
            if (a <= l->sz && l->sz < b) {
                v += x;
            }
            r->add(a- l->sz - 1, b- l->sz - 1, x);
            update();
        }
        ll sum(int a, int b) {
            if (!sz || b <= 0 || sz <= a) return 0;
            if (a <= 0 && sz <= b) return sm;
            push();
            ll res = 0;
            res += l->sum(a, b);
            if (a <= l->sz && l->sz < b) res += v;
            res += r->sum(a - l->sz - 1, b - l->sz - 1);
            return res;
        }
        void get(ll d[]) {
            if (!sz) return;
            push();
            l->get(d);
            d[l->sz] = v;
            r->get(d+l->sz+1);
        }
        void print() {
            if (!sz) return;
            printf("(");
            l->print();
            printf("-(%lld %lld %lld)-", v, sm, lz);
            r->print();
            printf(")");
        }
    } *n;


    static NP built(int l, int r, ll d[]) {
        if (l == r) return last;
        int md = (l+r)/2;
        NP x = Node::make(d[md]);
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
            l = Node::make(l);
            l->r = merge(l->r, r);
            return l->update();
        } else {
            r = Node::make(r);
            r->l = merge(l, r->l);
            return r->update();
        }
    }
    static pair<NP, NP> split(NP x, int k) {
        if (!x->sz) return {last, last};
        x->push();
        x = Node::make(x);
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
    STree(int sz, ll d[]) {
        n = built(0, sz, d);
    }
    int sz() {
        return n->sz;
    }

    STree merge(STree r) {
        return STree(merge(n, r.n));
    }
    pair<STree, STree> split(int k) {
        auto u = split(n, k);
        return pair<STree, STree>(STree(u.first), STree(u.second));
    }
    STree insert(int k, ll x) {
        auto u = split(n, k);
        return merge(merge(u.first, Node::make(x)), u.second);
    }
    STree erase(int k) {
        auto u = split(n, k);
        return merge(u.first, split(u.second, 1).second);
    }

    void get(ll d[]) {
        n->get(d);
    }
    void add(int l, int r, ll x) {
        n = Node::make(n);
        return n->add(l, r, x);
    }
    ll sum(int l, int r) {
        return n->sum(l, r);
    }
    void print() {
        n->print();
        printf("\n");
    }
};
STree::Node STree::last_d = STree::Node(NULL, NULL, 0);
STree::NP STree::last = &last_d;
STree::Node STree::pool[STree::PLS];
int STree::pc = 0;