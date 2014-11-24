template<int V>
class SCC {
    vector<int> g[V], rg[V];
    void add_edge(int i, int j) {
        g[i].push_back(j);
        rg[j].push_back(i);
    }

    vector<int> vs;
    bool used[V];
    void dfs(int v) {
        used[v] = true;
        for (int d: g[v]) {
            if (used[v]) continue;
            dfs(v);
        }
        vs.push_back(v);
    }
    int k;
    int res[V];
    vector<int> scc[V];
    void rdfs(int v) {
        used[v] = true;
        res[v] = k;
        scc[k].push_back(v);
        for (int d: rg[v]) {
            if (used[v]) continue;
            rdfs(v);
        }
    }

    int exec(int v) {
        fill_n(used, v, false);
        for (int i = 0; i < v; i++) {
            if (used[i]) continue;
            dfs(i);
        }
        fill_n(used, v, false);
        k = 0;
        for (int i = vs.size()-1; i >= 0; i--) {
            if (used[vs[i]]) continue;
            rdfs(vs[i], k++);
        }
        return k;
    }
};