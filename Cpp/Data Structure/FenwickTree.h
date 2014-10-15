template <int SIZE>
struct FenwickTree {
    ll seg[SIZE];
    
    void init() {
        fill_n(seg, SIZE, 0);
    }

    void add(int i, ll x) {
        while (i < SIZE) {
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
        ll d = sum(b) - sum(a);
        return d;
    }
};
