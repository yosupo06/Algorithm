struct LowLink {
    int r;
    V<int> low, ord, par, vlis;
    VV<int> tr;
    LowLink() {}
    LowLink(int n, int r) : r(r) {
        low = V<int>(n, -1);
        ord = V<int>(n, -1);
        par = V<int>(n);
        tr = VV<int>(n);        
    }
};

template<class E>
LowLink lowlink(const VV<E> &g, int r) {
    int n = int(g.size());
    LowLink lc(n, r);
    auto &low = lc.low;
    auto &ord = lc.ord;
    auto &par = lc.par;
    auto &vlis = lc.vlis;
    auto &tr = lc.tr;
    int co = 0;
    auto used = V<bool>(n, false);
    auto dfs = recur([&](auto self, int p, int b) -> void {
        used[p] = true;
        low[p] = ord[p] = co++; par[p] = b;
        vlis.push_back(p);

        bool rt = true;
        for (auto e: g[p]) {
            int d = e.to;
            if (rt && d == b) {
                rt = false;
                continue;
            }
            if (!used[d]) {
                tr[p].push_back(d);
                self(self, d, p);
                low[p] = min(low[p], low[d]);
            } else {
                low[p] = min(low[p], ord[d]);
            }
        }
    });
    if (r != -1) {
        dfs(r, -1);
    } else {
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs(i, -1);
        }
    }
    return lc;
}
