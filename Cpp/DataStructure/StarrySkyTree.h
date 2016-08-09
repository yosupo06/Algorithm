template<class N>
struct SegTree {
    int sz;
    vector<N> n;
    SegTree(int sz) {
        sz = 1<<bsr(2*sz-1);
        this->sz = sz;
        n = vector<N>(2*sz);
        for (int i = sz-1; i >= 1; i--) {
            n[i] = N(n[2*i], n[2*i+1]);
        }
    }
    template<class Q>
    void query(int a, int b, Q &&q, int k, int sz) {
        if (a <= 0 and sz <= b) {
            q += n[k];
            return;
        }
        n[k].push(n[2*k], n[2*k+1]);
        if (a < sz/2) query(a, b, q, 2*k, sz/2);
        if (sz/2 < b) query(a-sz/2, b-sz/2, q, 2*k+1, sz/2);
        if (q.update()) n[k].update(n[2*k], n[2*k+1]);
    }
    template<class Q>
    Q query(int a, int b, Q &&q) {
        if (a < sz and 0 < b) query(a, b, q, 1, sz);
        return q;
    }
};

struct Node {
    ll ma, lz;
    Node() : ma(0), lz(0) {}
    Node(Node &l, Node &r) { update(l, r); }
    void update(const Node &l, const Node &r) {
        ma = max(l.ma, r.ma);
    }
    void push(Node &l, Node &r) {
        if (lz) {
            l.lzdata(lz);
            r.lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(ll x) {
        ma += x; lz += x;
    }
};

struct MaxQuery {
    ll ma = -TEN(18);
    static constexpr bool update() { return false; }
    void operator+=(Node &r) { ma = max(ma, r.ma); }
};

struct AddQuery {
    ll x;
    static constexpr bool update() { return true; }
    void operator+=(Node &n) { n.lzdata(x); }
};
