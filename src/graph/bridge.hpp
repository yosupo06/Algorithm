struct Bridge {
    V<int> id;
    VV<int> groups;
    VV<int> tr;
};

template <class E> struct BridgeExec : Bridge {
    const VV<E>& g;
    int n;
    int ordc = 0;
    V<int> low, ord, vlist;
    V<int> used;
    BridgeExec(const VV<E>& _g)
        : g(_g), n(int(g.size())), low(n), ord(n), used(n) {
        id = V<int>(n);
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs1(i, -1);
            dfs2(i, -1);
        }
    }
    void dfs1(int p, int b) {
        used[p] = 1;
        low[p] = ord[p] = ordc++;
        vlist.push_back(p);
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
    void dfs2(int p, int b) {
        used[p] = 2;
        bool is_root = low[p] == ord[p];
        if (is_root) {
            int idc = int(groups.size());
            id[p] = idc;
            groups.push_back({p});
            tr.push_back({});
            if (b != -1) {
                tr[idc].push_back(id[b]);
                tr[id[b]].push_back(idc);
            }
        } else {
            id[p] = id[b];
            groups[id[p]].push_back(p);
        }
        for (auto e : g[p]) {
            int d = e.to;
            if (d == b || used[d] == 2) continue;
            dfs2(d, p);
        }
    }
};

template <class E> Bridge get_bridge(const VV<E>& g) {
    return BridgeExec<E>(g);
}
