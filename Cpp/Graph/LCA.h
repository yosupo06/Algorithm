template<int LG = 20>
struct LCA {
    vector<int> ro[LG], dps;

    /// 事前処理を行う rはroot頂点のid
    template<class E>
    LCA(const Graph<E> &g, int r) {
        int V = int(g.size());
        ro[0] = vector<int>(V, -1);
        dps.resize(V);
        dfs(g, r, -1, 0);
        for (int i = 1; i < LG; i++) {
            ro[i].resize(V);
            for (int j = 0; j < V; j++) {
                ro[i][j] = (ro[i-1][j] == -1) ? -1 : ro[i-1][ro[i-1][j]];
            }
        }
    }

    /// lとrの頂点のLCAを求める
    int query(int l, int r) {
        if (dps[l] < dps[r]) swap(l, r);
        int dd = dps[l]-dps[r];
        for (int i = LG-1; i >= 0; i--) {
            if (dd < (1<<i)) continue;
            dd -= 1<<i;
            l = ro[i][l];
        }
        if (l == r) return l;
        for (int i = LG-1; i >= 0; i--) {
            if (ro[i][l] == ro[i][r]) continue;
            l = ro[i][l]; r = ro[i][r];
        }
        return ro[0][l];
    }
    
    template<class E>
    void dfs(const Graph<E> &g, int p, int b, int now) {
        ro[0][p] = b;
        dps[p] = now;
        for (E e: g[p]) {
            if (e.to == b) continue;
            dfs(g, e.to, p, now+1);
        }
    }
};
