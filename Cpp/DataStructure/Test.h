struct Node {
    int ma = 0, lz = 0;
    Node* l;
    Node* r;
    int sz;
    Node() {
        ma = 0; lz = 0;
    }
    Node(Node* l, Node* r) : l(l), r(r) {
        if (l and r) {
            sz = l->sz + r->sz;
            update();
            Node();
        } else {
            sz = 1;
        }
    }
    void update() {
        ma = max(l->ma, r->ma);
    }
    void push() {
        if (lz) {
            l->lzdata(lz);
            r->lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }
};

struct MaxQuery {
    int ma = -1;
    Query& operator+=(const Node &r) {
        ma = min(ma, r->ma);
        return this;
    }
};
struct AddQuery {
    int x;
    void operator()(Node &n) {
        n->lzdata(x);
    }
};
template<class N>
struct SegTree {
    vector<N> n;
    SegTree(int sz) {
        n = vector<N>(2*sz+1);
        for (int i = 2*sz; i >= sz; i--) {
            n[i] = Node(1);
        }
        for (int i = sz-1; i >= 1; i--) {
            n->l = 
        }
        for (int i = 0; i < sz; i++) {
            n[]
        }
    }
}

namespace SegTree {
    template<class N, class Q>
    Q get(const N &n, int a, int b, Q q) {
        if (b <= 0 or sz <= a) return q;
        if (a <= 0 and sz <= b) {
            return q+n;
        }
        push();
        q = get(n->l, a, b, q);
        q = get(n->r, a-sz/2, b-sz/2, q);
        return q;
    }
}

struct Node {
    using NP = Node*;

    int ma = 0, lz = 0;

    void update() {
        assert(!lz);
        ma = max(l->ma, r->ma);
    }
    void push() {
        if (lz) {
            l->lzdata(lz);
            r->lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }

    void add(int a, int b, int x) {
        if (b <= 0 or sz <= a) return;
        if (a <= 0 and sz <= b) {
            lzdata(x);
            return;
        }
        push();
        l->add(a, b, x);
        r->add(a - sz/2, b - sz/2, x);
        update();
    }
    int get(int a, int b) {
        if (b <= 0 or sz <= a) return -1;
        if (a <= 0 and sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));
    }

    NP l, r;
    int sz;
    Node(int sz) : sz(sz) {
        if (sz == 1) return;
        l = new Node(sz/2);
        r = new Node(sz - sz/2);
        update();
    }
};
