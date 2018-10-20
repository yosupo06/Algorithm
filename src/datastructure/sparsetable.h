template <class D, class OP> struct SparseTable {
    D e;
    OP op;
    VV<D> data;
    SparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int n = int(v.size());
        if (n == 0) return;
        int lg = bsr(uint(n)) + 1;
        data = VV<D>(lg);
        data[0] = v;
        int l = 1;
        for (int s = 1; s < lg; s++) {
            data[s] = V<D>(n);
            for (int i = 0; i < n - l; i++) {
                data[s][i] = op(data[s - 1][i], data[s - 1][i + l]);
            }
            l <<= 1;
        }
    }
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int u = bsr(uint(r - l));
        return op(data[u][l], data[u][r - (1 << u)]);
    }
};
template <class D, class OP>
SparseTable<D, OP> get_sparse_table(V<D> v, D e, OP op) {
    return SparseTable<D, OP>(v, e, op);
}
