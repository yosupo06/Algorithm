template<class T>
struct SparseTable {
    static T op(T a, T b) { return min(a,b); }
    int lg;
    VV<T> d;
    SparseTable() {}
    SparseTable(const V<T> &v) {
        int n = int(v.size());
        if (n == 0) return;
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
    T query(int l, int r, T e) const {
        assert(l <= r);
        if (l == r) return e;
        int u = bsr(uint(r-l));
        return op(d[u][l], d[u][r-(1<<u)]);
    }
};

template<class T>
struct LowMemorySparseTable {
    static T op(T a, T b) { return SparseTable<T>::op(a,b); }

    static constexpr int B = 16;
    SparseTable<T> st;
    V<T> d;
    LowMemorySparseTable() {}
    LowMemorySparseTable(const V<T> &v) {
        int n = int(v.size());
        d = v;
        V<T> cv(n/B);
        for (int i = 0; i < n/B; i++) {
            T res = d[i*B];
            for (int j = 1; j < B; j++) {
                res = op(res, d[i*B+j]);
            }
            cv[i] = res;
        }
        st = SparseTable<T>(cv);
    }
    T query(int l, int r, T e) const {
        assert(l <= r);
        if (l == r) return e;
        int lb = (l+B-1)/B, rb = r/B;
        T res = e;
        if (lb >= rb) {
            for (int i = l; i < r; i++) {
                res = op(res, d[i]);
            }
            return res;
        }

        while (l % B) {
            res = op(res, d[l]);
            l++;
        }
        while (r % B) {
            r--;
            res = op(res, d[r]);
        }
        res = op(res, st.query(lb, rb, e));
        return res;
    }    
};
