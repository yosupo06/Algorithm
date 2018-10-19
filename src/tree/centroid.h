struct Centroid {
    int r;
    VV<int> cg;
    V<int> par;
    V<bool> used;

    using P = pair<int, int>;
    vector<P> info; //(child max, child)
    template<class E>
    int dfs(const VV<E> &g, int p, int b) {
        int sz = 1;
        info[p] = P(0, -1);
        for (E e: g[p]) {
            int d = e.to;
            if (d == b || used[d]) continue;
            int csz = dfs(g, d, p);
            sz += csz;
            info[p] = max(info[p], P(csz, d));
        }
        return sz;
    }
    template<class E>
    int init(const VV<E> &g, int p, int b) {
        int sz = dfs(g, p, -1);
        while (info[p].first > sz/2) p = info[p].second;
        par[p] = b;
        used[p] = true;
        for (E e: g[p]) {
            int d = e.to;
            if (used[d]) continue;
            cg[p].push_back(init(g, d, p));
        }
        return p;
    }
    Centroid() {}
    template<class E>
    Centroid(const VV<E> &g) {
        int n = (int)g.size();
        cg = VV<int>(n);
        par = V<int>(n);
        used = V<bool>(n);
        info = V<P>(n);
        r = init(g, 0, -1);
    }
};
