struct Articulation {
    VV<int> tr;
};

template <class E> struct ArticulationExec : Articulation {
    const VV<E>& g;
    int n;
    int ordc = 0;
    V<int> low, ord;
    V<int> used;
    AriticulationExec(const VV<E>& _g)
            : g(_g), n(int(g.size())), low(n), ord(n), used(n) {
        tr = VV<int>(n);
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs1(i, -1);
            dfs2(i, -1);
        }
    }
    void dfs1(int p, int b) {
        used[p] = 1;
        low[p] = ord[p] = ordc++;
        bool rt = true;
        for (auto e : g[p]) {
            int d = e.to;
            if (rt && d == b) {
                rt = false;
                continue;
            }
            if (!used[d]) {
                dfs1(d, p);
                low[p] = min(low[p], low[d]);
            } else {
                low[p] = min(low[p], ord[d]);
            }
        }
    }
    void dfs2(int p, int bid = -1) {
        used[p] = 2;
        if (bid != -1) {
            tr[p].push_back(bid);
            tr[bid].push_back(p);
        }
        for (auto e: g[p]) {
            int d = e.to;
            if (used[d] == 2) continue;
            if (low[d] < ord[p]) {
                dfs2(d, bid);
                continue;
            }
            int nid = int(tr.size());
            tr.push_back({});
            tr[p].push_back(nid);
            tr[nid].push_back(p);
            dfs2(d, nid);
        }
    }
};

template <class E> Articulation get_articulation(const VV<E>& g) {
    return ArticulationExec<E>(g);
}
