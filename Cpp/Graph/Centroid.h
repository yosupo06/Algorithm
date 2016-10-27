struct Centroid {
    int r;
    Graph<int> cg;
    vector<int> par;
    vector<bool> used;

    using P = pair<int, int>;
    vector<P> info; //(child max, child)
    template<class E>
    int dfs(const Graph<E> &g, int p, int b) {
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
    int init(const Graph<E> &g, int p, int b) {
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
    Centroid(const Graph<E> &g) {
        int n = (int)g.size();
        cg = Graph<int>(n);
        par = vector<int>(n);
        used = vector<bool>(n, false);
        info = vector<P>(n);
        r = init(g, 0, -1);
    }
};

template<class C>
struct CentDist {
    using P = pair<int, C>; //root, dist
    vector<vector<P>> plist;
    vector<bool> used;

    template<class E>
    void dfs(const Graph<E> &g, int p, int b, int r, C dp = 0) {
        plist[p].push_back(P(r, dp));
        for (const E &e: g[p]) {
            int d = e.to;
            if (used[d] || d == b) continue;
            dfs(g, d, p, r, dp+e.dist);
        }
    }

    template<class E>
    void init(const Graph<E> &g, const Centroid &cen, int p) {
        dfs(g, p, -1, p);
        //nex
        used[p] = true;
        for (int d: cen.cg[p]) {
            init(g, cen, d);
        }
    }

    CentDist() {}
    template<class E>
    CentDist(const Graph<E> &g, const Centroid &cen) {
        int n = int(g.size());
        plist = vector<vector<P>>(n);
        used = vector<bool>(n);
        init(g, cen, cen.r);
    }
};
