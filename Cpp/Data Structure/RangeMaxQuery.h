template <int N>
struct RangeMaxQuery {
    typedef long long D;
    static const int S = 1<<N;
    D seg[S*2];

    void init() {
        fill_n(seg, S*2, 0);
    }

    void set(int i, D x) {
        i += S - 1;
        seg[i] = x;
        while (i) {
            i = (i - 1) / 2;
            T s1 = seg[i*2+1], s2 = seg[i*2+2];
            seg[i] = max(s1, s2);
        }
    }

    void add(int i, D x) {
        i += S - 1;
        seg[i] += x;
        while (i) {
            i = (i - 1) / 2;
            T s1 = seg[i*2+1], s2 = seg[i*2+2];
            seg[i] = max(s1, s2);
        }
    }

    D get(int a, int b, int k = 0, int l = 0, int r = S) {
        if (a <= l && r <= b) return seg[k];
        if (r <= a || b <= l) return numeric_limits<D>::min();
        D vl = get(a, b, k*2+1, l, (l+r)/2);
        D vr = get(a, b, k*2+2, (l+r)/2, r);
        return min(vl, vr);
    }
};