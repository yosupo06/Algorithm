template <class T, int N>
struct GcdSegTree {
    static constexpr int size = 1<<N;
    T seg[size*2];

    T gcd(T a, T b) {
        if (b==0) return a;
        return gcd(b, a%b);
    }

    void init(T x) {
        for (int i = 0; i < size*2; i++) {
            seg[i] = 0;
        }
    }

    void add(int i, T x) {
        //if (i >= size) return;
        i += size - 1;
        seg[i] += x;
        while (i) {
            i = (i - 1) / 2;
            T s1 = seg[i*2+1], s2 = seg[i*2+2];
            seg[i] = gcd(s1, s2);
        }
    }

    inline T get(int a = 0, int b = size, int k = 0, int l = 0, int r = size) {
        if (a >= b || b > size) return 0;
        if (a <= l && r <= b) return seg[k];
        if (r <= a || b <= l) return 0;
        T vl = get(a, b, k*2+1, l, (l+r)/2);
        T vr = get(a, b, k*2+2, (l+r)/2, r);
        return gcd(vl, vr);
    }
};