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

template <class D, class OP> struct LowMemorySparseTable {
    static constexpr int B = 16;
    V<D> data;
    D e;
    OP op;
    SparseTable<D, OP> st;
    V<D> comp_arr(V<D> v) {
        int n = int(v.size());
        V<D> comp(n / B);
        for (int i = 0; i < n / B; i++) {
            D res = data[i * B];
            for (int j = 1; j < B; j++) {
                res = op(res, data[i * B + j]);
            }
            comp[i] = res;
        }
        return comp;
    }
    LowMemorySparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())
        : data(v), e(_e), op(_op), st(comp_arr(v), _e, _op) {}
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int lb = (l + B - 1) / B, rb = r / B;
        D res = e;
        if (lb >= rb) {
            for (int i = l; i < r; i++) {
                res = op(res, data[i]);
            }
            return res;
        }

        while (l % B) {
            res = op(res, data[l]);
            l++;
        }
        while (r % B) {
            r--;
            res = op(res, data[r]);
        }
        res = op(res, st.query(lb, rb));
        return res;
    }
};
template <class D, class OP>
LowMemorySparseTable<D, OP> get_low_memory_sparse_table(V<D> v, D e, OP op) {
    return LowMemorySparseTable<D, OP>(v, e, op);
}
