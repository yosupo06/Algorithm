template <int N>
struct FenwickTree {
    ll seg[N];
    
    void init() {
        fill_n(seg, N, 0);
    }

    void add(int i, ll x) {
        while (i < N) {
            seg[i] += x;
            i += (i+1) & ~i;
        }
    }

    //[0, i)
    ll sum(int i) {
        ll s = 0;
        int d = 1;
        while (i >= d) {
            i -= d;
            s += seg[i];
            d = (i+1) & ~i;
        }
        return s;
    }

    //[a, b)
    ll sum(int a, int b) {
        return sum(b) - sum(a);
    }
};
