struct StaticRangeUnion {
    using P = pair<int, int>;
    int n;
    VV<P> ques;
    StaticRangeUnion(int _n = 0) : n(_n), ques(n + 1) {}
    void merge(int a, int b, int di) {
        if (di == 0) return;
        ques[min(di, n)].push_back({a, b});
    }
    UnionFind exec() {
        UnionFind uf(n);
        V<P> que;
        for (int di = n; di >= 1; di--) {
            for (auto p : ques[di]) que.push_back(p);
            V<P> nque;
            for (auto p : que) {
                if (uf.same(p.first, p.second)) continue;
                uf.merge(p.first, p.second);
                nque.push_back({p.first + 1, p.second + 1});
            }
            que = nque;
        }
        return uf;
    }
};
