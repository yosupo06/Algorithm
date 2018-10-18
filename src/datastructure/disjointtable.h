template<class D, class OP>
struct DisjointTable {
    OP op;
    D e;
    int lg;
    VV<D> data;
    DisjointTable(V<D> v, OP _op, D _e) : op(_op), e(_e) {
        lg = 1;
        while ((1<<lg) < int(v.size())) lg++;
        int n = 1<<lg;
        v.resize(n, e);
        data = VV<D>(lg, V<D>(n));
        data[0] = v;
        for (int h = 1; h < lg; h++) {
            int u = (1<<h);
            for (int i = 0; i < n / (2 * u); i++) {
                int base = i * (2 * u) + u;
                D res;
                res = e;
                for (int j = base-1; j >= base-u; j--) {
                    res = op(v[j], res);
                    data[h][j] = res;
                }
                res = e;
                for (int j = base; j < base+u; j++) {
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
        int u = bsr(uint(l^r));
        return op(data[u][l], data[u][r]);
    }
};
template<class D, class OP>
NazoTable<D, OP> get_nazo(V<D> v, OP op, D e) {
    return NazoTable<D, OP>(v, op, e);
}
