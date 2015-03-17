/*
0-indexed
*/

template <int N>
struct FenwickTree {
    using D = ll;
    D seg[N+1];
    
    void init() {
        for (int i = 0; i <= N; i++) {
            seg[i] = 0;
        }
    }

    void add(int i, D x) {
        i++;
        while (i <= N) {
            seg[i] += x;
            i += i & -i;
        }
    }

    //[0, i)
    D sum(int i) {
        D s = 0;
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }

    //[a, b)
    D sum(int a, int b) {
        return sum(b) - sum(a);
    }
};

template <int N>
struct FenwickTree2D {
    using D = ll;
    FenwickTree<N> seg[N+1];
    
    void init() {
        for (int i = 0; i <= N; i++) {
            seg[i].init();
        }
    }

    void add(int x, int y, D d) {
        x++;
        while (x <= N) {
            seg[x].add(y, d);
            x += x & -x;
        }
    }

    //[0, i)
    D sum(int x, int y) {
        D s = 0;
        while (x > 0) {
            s += seg[x].sum(y);
            x -= x & -x;
        }
        return s;
    }

    D sum(int lx, int ly, int hx, int hy) {
        return (sum(hx, hy) + sum(lx, ly))
             - (sum(lx, hy) + sum(hx, ly));
    }
};