template<int N>
struct SparseRMQ {
    constexpr static int S = static_ceil_log2(N);
    int d[S][N];
    void init() {
        printf("%d %d\n", N, S);
        int l = 1;
        for (int s = 1; s < S; s++) {
            //l == 2^(s-1)
            for (int i = 0; i < N - l; i++) {
                d[s][i] = min(d[s-1][i], d[s-1][i + l]);
            }
            l <<= 1;
        }
    }
    auto query(int l, int r) {
        assert(l <= r);
        if (l == r) return numeric_limits<int>::max();
        if (r - l == 1) return d[0][l];
        int u = ceil_log2(r-l)-1;
        return min(d[u][l], d[u][r-(1<<u)]);
    }
};

template<int N>
struct SparseLMRMQ {
    constexpr static int S = 32; //メモリ消費量が減ります 2^iにしないと速度が破滅するので注意
    SparseRMQ<N/S> sq;
    int d[N];
    void init() {
        for (int i = 0; i < N/S; i++) {
            int res = numeric_limits<int>::max();
            for (int j = 0; j < S; j++) {
                res = min(res, d[i*S+j]);
            }
            sq.d[0][i] = res;
        }
        sq.init();
    }
    auto query(int l, int r) {
        int lb = (l+S-1)/S, rb = r/S;
        int res = numeric_limits<int>::max();
        if (lb > rb) {
            for (int i = l; i < r; i++) {
                res = min(res, d[i]);
            }
            return res;
        }

        while (l % S) {
            res = min(res, d[l]);
            l++;
        }
        while (r % S) {
            r--;
            res = min(res, d[r]);
        }
        res = min(res, sq.query(lb, rb));
        return res;
    }
};

template<int S>
struct NazoTable {
    constexpr static int N = 1<<S;
    int d[S][N];
    void init() {
        for (int s = 1; s < S; s++) {
            int u = (1<<s);
            for (int i = 0; i < N/(u*2); i++) {
                int base = i*(u*2) + u;
                int res = numeric_limits<int>::max();
                for (int j = 1; j <= u; j++) {
                    res = min(res, d[0][base-j]);
                    d[s][base-j] = res;
                }
                res = numeric_limits<int>::max();
                for (int j = 0; j < u; j++) {
                    res = min(res, d[0][base+j]);
                    d[s][base+j] = res;
                }
            }
        }
    }
    auto query(int l, int r) {
        r--;
        if (l > r) return numeric_limits<int>::max();
        if (l == r) return d[0][l];
        int u = bsr(l^r);
        assert(0 <= u && u < S);
        return min(d[u][l], d[u][r]);
    }
};