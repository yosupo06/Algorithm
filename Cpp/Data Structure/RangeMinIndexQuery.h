template <int N>
struct RangeMinIndexQuery {
    typedef long long D;
    typedef pair<D, int> P;
    static const int S = 1<<N;
    P seg[S*2];

    void init() {
        fill_n(seg, S*2, P(numeric_limits<D>::max(), -1));
    }

    void set(int i, D x) {
        i += S - 1;
        seg[i].first = x;
        while (i) {
            i = (i - 1) / 2;
            T s1 = seg[i*2+1], s2 = seg[i*2+2];
            seg[i] = max(s1, s2);
        }
    }

    D get(int a, int b, int k = 0, int l = 0, int r = S) {
        if (a <= l && r <= b) return seg[k];
        if (r <= a || b <= l) return P(numeric_limits<D>::max(), -1);
        D vl = get(a, b, k*2+1, l, (l+r)/2);
        D vr = get(a, b, k*2+2, (l+r)/2, r);
        return min(vl, vr);
    }
};