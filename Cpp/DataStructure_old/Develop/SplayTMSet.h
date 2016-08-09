struct Tree {
    using D = int;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last, la;
    struct Node {
        NP p, l, r;
        int sz;
        D v;
        Node(D v) :p(nullptr), l(last), r(last), sz(1), v(v) {}
        Node(NP p, NP l, NP r, int sz = 0) : p(p), l(l), r(r), sz(sz) {}
        bool is_root() {
            return p == nullptr;
        }
        void rotr() {
            NP q = p, qq = q->p;
            q->l = r; r->p = q;
            r = q; q->p = this;
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void rotl() {
            NP q = p, qq = q->p;
            q->r = l; l->p = q;
            l = q; q->p = this;
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void splay() {
            assert(this != last);
            while (!is_root()) {
                NP q = p;
                if (q->is_root()) {
                    if (q->l == this) rotr();
                    else rotl();
                    continue;
                }
                NP r = q->p;
                if (r->l == q) {
                    if (q->l == this) {q->rotr(); rotr();}
                    else {rotl(); rotr();}
                } else {
                    if (q->r == this) {q->rotl(); rotl();}
                    else {rotr(); rotl();}
                }
            }
        }
        void push() {
 
        }
        NP update() {
            if (this == last) return this;
            sz = 1+l->sz+r->sz;
            return this;
        }
    } *n;
    static NP merge(NP l, NP r) {
        if (l == last) {
            return r;
        }
        while (l->r != last) {
            l = l->r;
        }
        l->splay();
        l->r = r;
        r->p = l;
        return l->update();
    }
    static pair<NP, NP> split(NP x, int k) {
        assert(0 <= k && k <= x->sz);
        if (k == x->sz) {
            return {x, last};
        }
        while (k != x->l->sz) {
            if (k < x->l->sz) {
                x = x->l;
            } else {
                k -= x->l->sz+1;
                x = x->r;
            }
        }

        x->splay();
        NP l = x->l;
        l->p = NULL;
        x->l = last;
        return {l, x->update()};
    }
 
    Tree() : n(last) {}
    Tree(NP n) : n(n) {}
    int sz() {
        return n->sz;
    }
    void insert(int k, D v) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(v)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, split(u.second, 1).second);
    }
    int getc(int k) {
        auto u = split(n, k);
        int res = u.second->v;
        n = merge(u.first, u.second);
        return res;
    }
};
Tree::Node Tree::last_d = Tree::Node(NULL, NULL, NULL, 0);
Tree::NP Tree::last = &last_d;
Tree::NP Tree::la;
