template<class N>
struct SegTree {
    int lg, sz;
    vector<N> n;
    SegTree() {}
    SegTree(int sz) {
        assert(sz >= 1);
        lg = bsr(uint(2*sz-1));
        sz = 1<<lg;
        this->sz = sz;
        n = vector<N>(2*sz);
        for (int i = 2*sz-1; i >= sz; i--) {
            n[i] = N();
        }
        for (int i = sz-1; i >= 1; i--) {
            n[i] = N(n[2*i], n[2*i+1]);
        }
    }
    void all_update() {
        for (int i = 1; i <= sz-1; i++) {
            n[i].push();
        }
        for (int i = sz-1; i >= 1; i--) {
            n[i].update(n[2*i], n[2*i+1]);
        }
    }
    template<class Q>
    Q single(int idx, Q q) {
        if (idx < 0 || sz <= idx) return q;
        idx += sz;
        for (int i = lg; i >= 1; i--) {
            int k = idx>>i;
            n[k].push(n[2*k], n[2*k+1]);
        }
        q += n[idx];
        if (q.update()) {
            for (int i = 1; i <= lg; i++) {
                int k = idx>>i;
                n[k].update(n[2*k], n[2*k+1]);
            }
        }
        return q;
    }
    template<class Q>
    void query(int a, int b, Q &q, int k, int sz) {
        if (a <= 0 && sz <= b) {
            q += n[k];
            return;
        }
        n[k].push(n[2*k], n[2*k+1]);
        if (a < sz/2) query(a, b, q, 2*k, sz/2);
        if (sz/2 < b) query(a-sz/2, b-sz/2, q, 2*k+1, sz/2);
        if (q.update()) n[k].update(n[2*k], n[2*k+1]);
    }
    template<class Q>
    Q query(int a, int b, Q q) {
        if (a < sz && 0 < b) query(a, b, q, 1, sz);
        return q;
    }
    struct NodeQuery {
        N n;
        static constexpr bool update() { return false; }
        void operator+=(N &r) { N nn; nn.update(n, r); n = nn; }
    };
};

struct Node {
    ll ma, lz;
    void init() {
        ma = lz = 0;
    }
    Node() { init(); } // leaf
    Node(Node &l, Node &r) { init(); update(l, r); }
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
    // query
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
};
