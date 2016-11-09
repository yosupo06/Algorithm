/**
 * LowLink
 * dfs木についてのいろいろな情報を求める
 */
struct LowLink {
    int r;
    vector<int> low, ord, par; //low, ord, parent
    vector<int> vlis; //preorder list
    vector<vector<int>> tr; //dfs tree

    int co;
    vector<bool> used;
    
    template<class E>
    LowLink(const Graph<E> &g, int r) : r(r) {
        int V = int(g.size());
        low.resize(V); ord.resize(V); par.resize(V);
        tr.resize(V); used.resize(V);
        co = 0;
        used = vector<bool>(V, false);
        if (r != -1) {
            dfs(g, r, -1);
        } else {
            for (int i = 0; i < V; i++) {
                if (used[i]) continue;
                dfs(g, i, -1);
            }
        }
    }
    
    template<class E>
    void dfs(const Graph<E> &g, int p, int b) {
        used[p] = true;
        bool rt = true;
        low[p] = ord[p] = co++; par[p] = b;
        vlis.push_back(p);
        for (auto e: g[p]) {
            int d = e.to;
            if (rt && d == b) {
                rt = false;
                continue;
            }
            if (!used[d]) {
                tr[p].push_back(d); dfs(g, d, p);
                low[p] = min(low[p], low[d]);
            } else {
                low[p] = min(low[p], ord[d]);
            }
        }
    }
};
