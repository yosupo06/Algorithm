template <class D, class OP> struct DisjointTable {
    D e;
    OP op;
    VV<D> data;
    DisjointTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int lg = 1;
        while ((1 << lg) < int(v.size())) lg++;
        int n = 1 << lg;
        v.resize(n, e);
        data = VV<D>(lg, V<D>(n));
        data[0] = v;
        for (int h = 1; h < lg; h++) {
            int u = (1 << h);
            for (int i = 0; i < n / (2 * u); i++) {
                int base = i * (2 * u) + u;
                D res;
                res = e;
                for (int j = base - 1; j >= base - u; j--) {
                    res = op(v[j], res);
                    data[h][j] = res;
                }
                res = e;
                for (int j = base; j < base + u; j++) {
                    res = op(res, v[j]);
                    data[h][j] = res;
                }
            }
        }
    }
    D query(int l, int r) {
        r--;
        if (l > r) return e;
        if (l == r) return data[0][l];
        int u = bsr(uint(l ^ r));
        return op(data[u][l], data[u][r]);
    }
};

template <class D, class OP>
DisjointTable<D, OP> get_disjoint_table(V<D> v, D e, OP op) {
    return DisjointTable<D, OP>(v, e, op);
}
