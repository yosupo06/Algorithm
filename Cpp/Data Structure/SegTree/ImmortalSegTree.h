struct Tree {

    struct Node {
        Node *l, *r;
        int sz;
        bool f;
        array<int, 3> d;
        Node(int li, int ri) {
            sz = ri-li;
            d.fill(0);
            if (ri-li == 1) return;
            int md = (li+ri)/2;
            l = new Node(li, md);
            r = new Node(md, ri);
        }
    } *n;

    typedef Node* NP;

    Tree() {
        n = NULL;
    }
    Tree(NP u) {
        n = new Node(*u);
    }
    Tree(int li, int ri) {
        n = new Node(li, ri);
    }

    NP set(NP x, int k) {
        x = new Node(*x);
        if (x->sz == 1) {
            x->f = true;
            x->d.fill(1);
            return x;
        }
        if (k < x->l->sz) {
            x->l = set(x->l, k);
        } else {
            x->r = set(x->r, k- x->l->sz);
        }
        auto &ld = x->l->d, &md = x->d, &rd = x->r->d;
        md[0] = (ld[0] == x->l->sz) ? ld[0]+rd[0] : ld[0];
        md[2] = (rd[2] == x->r->sz) ? ld[2]+rd[2] : rd[2];
        md[1] = max(max(ld[1], rd[1]), ld[2]+rd[0]);
        return x;
    }
    
    array<int, 3> get(NP x, int l, int r) {
        array<int, 3> md;
        if (x->sz <= l || r <= 0) {
            md.fill(0);
            return md;
        }
        if (l <= 0 && x->sz <= r) return x->d;
        if (x->sz == 1) return x->d;
        array<int, 3> ld = get(x->l, l, r);
        array<int, 3> rd = get(x->r, l- x->l->sz, r- x->l->sz);
        md[0] = (ld[0] == x->l->sz) ? ld[0]+rd[0] : ld[0];
        md[2] = (rd[2] == x->r->sz) ? ld[2]+rd[2] : rd[2];
        md[1] = max(max(ld[1], rd[1]), ld[2]+rd[0]);    
        return md;
    }
    Tree set(int k) {
        return Tree(set(n, k));
    }
    array<int, 3> get(int l, int r) {
        return get(n, l, r);
    }
};

struct Tree {

    struct Node {
        Node *l, *r;
        int sz;
        uint d;
        ll hash[4];
        Node(int li, int ri) {
            sz = ri-li;
            d = 0;
            if (ri-li == 1) return;
            int md = (li+ri)/2;
            l = new Node(li, md);
            r = new Node(md, ri);
        }
    } *n;

    typedef Node* NP;

    Tree() {
        n = NULL;
    }
    Tree(NP u) {
        n = new Node(*u);
    }
    Tree(int li, int ri) {
        n = new Node(li, ri);
    }

    static pair<NP, bool> add(NP x, int k) {
        x = new Node(*x);
        if (x->sz == 1) {
            x->d += 1;
            fill_n(x->hash, 4, x->d);
            x->d %= 2;
            return {x, !x->d};
        }
        bool f = true, res = false;
        if (k < x->l->sz) {
            auto u = add(x->l, k);
            x->l = u.first;
            f &= u.second;
        }
        if (f) {
            k = max(k, x->l->sz);
            auto u = add(x->r, k - x->l->sz);
            x->r = u.first;
            res |= u.second;
        }
        for (int i = 0; i < 4; i++) {
            x->hash[i] = (x->l->hash[i] + x->r->hash[i] * PM[i][x->l->sz]) % HMD[i];
        }
        return {x, res};
    }
    static bool equal(NP l, NP r) {
        assert(l->sz == r->sz);
        if (l->sz == 1) {
            return l->d == r->d;
        }
        bool f = true;
        for (int i = 0; i < 4; i++) {
            if (l->hash[i] != r->hash[i]) {
                f = false;
            }
        }
        if (f) return true;
        return equal(l->l, r->l) && equal(l->r, r->r);
    }
    static bool comp(NP l, NP r) {
        assert(l->sz == r->sz);
        if (l->sz == 1) {
            return l->d < r->d;
        }
        if (!equal(l->r, r->r)) {
            return comp(l->r, r->r);
        }
        return comp(l->l, r->l);
    }
    static void print(NP x) {
        if (x->sz == 1) {
            printf("%d", x->d);
            return;
        }
        print(x->l);
        print(x->r);
    }
    Tree add(int k) {
        return Tree(add(n, k).first);
    }
    void print() {
        print(n);
    }
    bool operator<(const Tree &l) const {
        return comp(n, l.n);
    }
};
