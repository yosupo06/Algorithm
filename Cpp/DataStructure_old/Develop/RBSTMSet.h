struct Tree {
    using D = ll;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        D v;
        Node(D v) :l(last), r(last), sz(1), v(v) {}
        Node() :l(nullptr), r(nullptr), sz(0) {}
        void push() {

        }
        NP update() {
            sz = 1+l->sz+r->sz;
            return this;
        }
        int lb(D a) {
            if (!sz) return 0;
            if (a <= v) return l->lb(a);
            return l->sz + 1 + r->lb(a);
        }
        int ub(D a) {
            if (!sz) return 0;
            if (v <= a) return l->sz + 1 + r->ub(a);
            return l->ub(a);
        }
        D get(int k) {
            if (k == l->sz) return v;
            if (k < l->sz) {
                return l->get(k);
            } else {
                return r->get(k- (l->sz+1));
            }
        }
    } *n;

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

    Tree() : n(last) {}
    Tree(NP n) : n(n) {}
    int sz() {
        return n->sz;
    }
    void merge(Tree r) {
        n = merge(n, r.n);
    }
    Tree split(int k) {
        auto u = split(n, k);
        n = u.first;
        return Tree(u.second);
    }
    void insert(D v) {
        auto u = split(n, lb(v));
        n = merge(merge(u.first, new Node(v)), u.second);
    }
    void erase(D v) {
        assert(count(v));
        auto u = split(n, lb(v));
        n = merge(u.first, split(u.second, 1).second);
    }
    int count(D v) {
        return ub(v) - lb(v);
    }
    int lb(D v) {
        return n->lb(v);
    }
    int ub(D v) {
        return n->ub(v);
    }
    D get(int k) {
        return n->get(k);
    }
};
Tree::Node Tree::last_d = Tree::Node();
Tree::NP Tree::last = &last_d;