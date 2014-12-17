template <int N>
struct RangeMinQuery {
    static const int S = 1<<N;
    static const ll INF = 1LL<<62;
    ll seg[2*S];

    void init() {
        fill_n(seg, 2*S, INF);
    }

    void init(int n, ll x[]) {
        init();
        for (int i = 0; i < n; i++) {
            seg[i+S] = x[i];
        }
        for (int i = S-1; i >= 0; i--) {
            seg[i] = min(seg[i*2], seg[i*2+1]);
        }
    }

    void set(int i, D x) {
        i += S;
        seg[i] = x;
        while (i) {
            i /= 2;
            seg[i] = min(seg[i*2], seg[i*2+1]);
        }
    }

    ll get(int a, int b, int k = 1, int l = 0, int r = S) {
        if (r <= a || b <= l) return INF;
        if (a <= l && r <= b) return seg[k];
        int md = (l+r)/2;
        ll dl = get(a, b, k*2, l, md);
        ll dr = get(a, b, k*2+1, md, r);
        return min(dl, dr);
    }
};
