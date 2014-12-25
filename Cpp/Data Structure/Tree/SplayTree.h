struct Tree {
    using D = int;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz;
        D v;
        Node(D v) :p(NULL), l(last), r(last), sz(1), v(v) {}
        Node(NP p, NP l, NP r, int sz = 0) : p(p), l(l), r(r), sz(sz) {}
        int pos() {
            if (p && p->l == this) return -1;
            if (p && p->r == this) return 1;
            return 0;
        }
        void rot() {
            NP q = p, qq = q->p;
            if (q->l == this) {
                q->l = r; r->p = q;
                r = q; q->p = this;
            } else {
                q->r = l; l->p = q;
                l = q; q->p = this;
            }
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void splay() {
            while (pos()) {
                if (!p->pos()) {
                    rot();
                } else if (p->pos() == pos()) {
                    p->rot(); rot();
                } else {
                    rot(); rot();
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
        if (r == last) {
            return l;
        }
        while (r->l != last) {
            r = r->l;
        }
        r->splay();
        r->l = l;
        l->p = r;
        return r->update();
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
    static NP built(int sz, ll d[]) {
        if (!sz) return last;
        int md = sz/2;
        NP x = new Node(d[md]);
        x->l = built(md, d);
        x->l->p = x;
        x->r = built(sz-(md+1), d+(md+1));
        x->r->p = x;
        return x->update();
    }
    Tree() : n(last) {}
    Tree(NP n) : n(n) {}
    Tree(int sz, ll d[]) {
        n = built(sz, d);
    }
    int sz() {
        return n->sz;
    }
    void insert(int k, D v) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(v)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, u.second->r);
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