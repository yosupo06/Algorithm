struct Tree {
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        int value;
        Node(int v) :l(last), r(last), sz(1), value(v) {}
        Node(NP l, NP r, int sz = 0) :l(l), r(r), sz(sz) {}
        void push() {

        }
        NP update() {
            sz = 1+l->sz+r->sz;
            return this;
        }
        int getc(int a) {
            if (a == l->sz) return value;
            if (a < l->sz) {
                return l->getc(a);
            } else {
                return r->getc(a- l->sz - 1);
            }
        }
    } *n;

    static NP built(int l, int r, ll d[]) {
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

    Tree(NP n) : n(n) {}
    Tree(int sz, ll d[]) {
        n = built(0, sz, d);
    }
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
    void insert(int k, int value) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(value)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, split(u.second, 1).second);
    }
    int getc(int l) {
        return n->getc(l);
    }
};
Tree::Node Tree::last_d = Tree::Node(NULL, NULL, 0);
Tree::NP Tree::last = &last_d;