/**
 * UnionFind
 */
struct UnionFind {
    vector<int> p, r;
    int gn;
    UnionFind(int N) {
        p.resize(N); r.resize(N);
        fill(begin(p), end(p), -1);
        fill(begin(r), end(r), 1);
        gn = N;
    }
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return; //same
        gn--;
        if (r[x] < r[y]) p[x] = y;
        else if (r[x] > r[y]) p[y] = x;
        else {p[x] = y; r[x]++;}
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) {
        return group(a) == group(b);
    }    
};
