struct UnionFind {
    int n;
    V<int> p, r;
    int gn;
    UnionFind(int _n = 0) : n(_n), p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        assert(0 <= a && a < n);
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return group(a) == group(b);
    }
};
