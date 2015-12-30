template<int S>
struct SparseRMQ {
    static const int N = 1<<S;
    int d[S][N];
    void init() {
        int l = 1;
        for (int s = 1; s < S; s++) {
            for (int i = 0; i < N - l; i++) {
                d[s][i] = max(d[s-1][i], d[s-1][i + l]);
            }
            l <<= 1;
        }
    }
    int query(int l, int r) {
        assert(l <= r);
        if (l == r) return -1;
        int u = bsr(r-l);
        return max(d[u][l], d[u][r-(1<<u)]);
    }
};

template<int S>
struct SparseLMRMQ {
    static const int N = 1<<S;
    static const int T = 5;
    static const int B = 1<<T;
    SparseRMQ<S-T> sq;
    int d[N];
    void init() {
        for (int i = 0; i < N/B; i++) {
            int res = -1;
            for (int j = 0; j < B; j++) {
                res = max(res, d[i*B+j]);
            }
            sq.d[0][i] = res;
        }
        sq.init();
    }
    int query(int l, int r) {
        int lb = (l+B-1)/B, rb = r/B;
        int res = -1;
        if (lb > rb) {
            for (int i = l; i < r; i++) {
                res = max(res, d[i]);
            }
            return res;
        }

        while (l % B) {
            res = max(res, d[l]);
            l++;
        }
        while (r % B) {
            r--;
            res = max(res, d[r]);
        }
        res = max(res, sq.query(lb, rb));
        return res;
    }
};


template<int S>
struct NazoTable {
    static const int N = 1<<S;
    int d[S][N];
    void init() {
        for (int s = 1; s < S; s++) {
            int u = (1<<s);
            for (int i = 0; i < N/(u*2); i++) {
                int base = i*(u*2) + u;
                int res = -1;
                for (int j = 1; j <= u; j++) {
                    res = max(res, d[0][base-j]);
                    d[s][base-j] = res;
                }
                res = -1;
                for (int j = 0; j < u; j++) {
                    res = max(res, d[0][base+j]);
                    d[s][base+j] = res;
                }
            }
        }
    }
    int query(int l, int r) {
        r--;
        if (l > r) return -1;
        if (l == r) return d[0][l];
        int u = bsr(l^r);
        return max(d[u][l], d[u][r]);
    }
};