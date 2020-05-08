template <class T>
V<pair<int, int>> manhattan_mst(V<pair<T, T>> ps,
                                T inf = numeric_limits<T>::max()) {
    V<pair<int, int>> edges;
    int n = int(ps.size());
    V<int> ids(n);
    iota(ids.begin(), ids.end(), 0);
    for (int ph = 0; ph < 4; ph++) {
        sort(ids.begin(), ids.end(), [&](auto i, auto j) {
            T ixy = (ps[i].first + ps[i].second),
              jxy = (ps[j].first + ps[j].second);
            return tie(ixy, ps[i].second) > tie(jxy, ps[j].second);
        });
        V<T> xv;
        for (int i = 0; i < n; i++) xv.push_back(ps[i].first);
        sort(xv.begin(), xv.end());
        xv.erase(unique(xv.begin(), xv.end()), xv.end());
        using P = pair<T, int>;
        V<P> fen(n, P(-inf, -1));
        for (int id : ids) {
            auto xi = int(lower_bound(xv.begin(), xv.end(), ps[id].first) -
                          xv.begin());
            P ma = P(-inf, -1);
            {
                int i = xi + 1;
                while (i > 0) {
                    if (ma.first <= fen[i - 1].first) ma = fen[i - 1];
                    i -= i & -i;
                }
            }
            if (ma.second != -1) edges.push_back({id, ma.second});
            {
                T x = ps[id].first - ps[id].second;
                int i = xi + 1;
                while (i <= n) {
                    if (fen[i - 1].first <= x) fen[i - 1] = P(x, id);
                    i += i & -i;
                }
            }
        }

        for (auto& p : ps) {
            swap(p.first, p.second);
        }
        if (ph == 1) {
            for (auto& p : ps) {
                p.second *= -1;
            }
        }
    }
    auto dist = [&](int i, int j) {
        return abs(ps[i].first - ps[j].first) +
               abs(ps[i].second - ps[j].second);
    };
    sort(edges.begin(), edges.end(), [&](auto x, auto y) {
        return dist(x.first, x.second) < dist(y.first, y.second);
    });
    auto uf = UnionFind(n);
    V<pair<int, int>> res;
    for (auto p : edges) {
        if (uf.same(p.first, p.second)) continue;
        res.push_back(p);
        uf.merge(p.first, p.second);
    }
    return res;
}
