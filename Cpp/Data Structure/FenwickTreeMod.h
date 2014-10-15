template <int SIZE, ll MD>
struct FenwickTreeMod {
    ll seg[SIZE];
    
    void init() {
        fill_n(seg, SIZE, 0);
    }

    void add(int i, ll x) {
        x %= MD;
        while (i < SIZE) {
            seg[i] += x;
            seg[i] %= MD;
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
            s %= MD;
            d = (i+1) & ~i;
        }
        return s;
    }

    //[a, b)
    ll sum(int a, int b) {
        ll d = sum(b) - sum(a);
        return (d % MD + MD) % MD;
    }
};
