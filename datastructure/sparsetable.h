template<class T>
struct SparseTable {
    T op(T a, T b) { return min(a,b); }
    int lg;
    VV<T> d;
    SparseTable() {}
    SparseTable(const V<T> &v) {
        int n = int(v.size());
        lg = bsr(uint(n))+1;
        d = VV<T>(lg);
        d[0] = v;
        int l = 1;
        for (int s = 1; s < lg; s++) {
            d[s] = V<T>(n);
            for (int i = 0; i < n - l; i++) {
                d[s][i] = op(d[s-1][i], d[s-1][i+l]);
            }
            l <<= 1;
        }
    }
    T query(int l, int r, T e) {
        assert(l <= r);
        if (l == r) return e;
        int u = bsr(uint(r-l));
        return op(d[u][l], d[u][r-(1<<u)]);
    }
};
