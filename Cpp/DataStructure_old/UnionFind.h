/**
 * UnionFind
 */
template <int N>
struct UnionFind {
    int p[N], r[N];
    int gn;
    void init(int n = N) {
        fill_n(p, n, -1); fill_n(r, n, 1);
        gn = n;
    }
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return; //same
        gn--;
        if (r[x] > r[y]) p[x] = y;
        else if (r[x] > r[y]) p[y] = x;
        else p[x] = y; r[x]++;
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) {
        return group(a) == group(b);
    }
};
