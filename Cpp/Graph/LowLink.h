/**
 * LowLink
 * dfs木についてのいろいろな情報を求める
 */
struct LowLink {
    vector<int> low, ord, par;
    vector<int> vlis;
    
    LowLink() {}
    template<class E>
    LowLink(const Graph<E> &g, int r) { exec(g, r); }

    template<class E>
    void exec(const Graph<E> &g, int r) {
        int V = (int)g.size();
        low.resize(V); ord.resize(V); par.resize(V);
        co = 0; used.resize(V);
        fill_n(used.begin(), V, false);
        if (r != -1) {
            dfs(g, r, -1);
        } else {
            for (int i = 0; i < n; i++) {
                if (used[i]) continue;
                dfs(g, i, -1);
            }
        }
    }
    int co;
    vector<bool> used;
    template<class E>
    void dfs(const Graph<E> &g, int p, int b) {
        used[p] = true;
        bool rt = true;
        low[p] = ord[p] = co++;
        vlis.push_back(p);
        par[p] = b;
        for (E e: g[p]) {
            if (rt and e.to == b) {
                rt = false;
                continue;
            }
            if (!used[e.to]) {
                dfs(g, e.to, p);
                low[p] = min(low[p], low[e.to]);
            } else {
                low[p] = min(low[p], ord[e.to]);
            }
        }
    }
};
