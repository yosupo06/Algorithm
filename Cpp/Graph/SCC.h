/**
 * SCC
 */
template<int V>
struct SCC {
    vector<int> g[V], rg[V];
    /// i-jに辺を追加する
    void add(int i, int j) {
        g[i].push_back(j);
        rg[j].push_back(i);
    }

    vector<int> vs;
    bool used[V];
    void dfs(int v) {
        used[v] = true;
        for (int d: g[v]) {
            if (!used[d]) dfs(d);
        }
        vs.push_back(v);
    }
    int res[V]; /// res[i] = 頂点iの属する強連結成分のID
    vector<int> scc[V]; /// scc[i] = i個目の強連結成分に属する頂点
    void rdfs(int v, int k) {
        used[v] = true;
        res[v] = k; scc[k].push_back(v);
        for (int d: rg[v]) {
            if (!used[d]) rdfs(d, k);
        }
    }

    int exec(int v) {
        fill_n(used, v, false);
        for (int i = 0; i < v; i++) {
            if (!used[i]) dfs(i);
        }
        fill_n(used, v, false);
        int k = 0;
        for (int i = vs.size()-1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }
};