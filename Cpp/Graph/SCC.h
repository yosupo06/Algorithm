/**
 * not verify
 * SCC
 */
struct SCC {
    int gc; /// group count
    vector<int> res; /// res[i] = 頂点iの属する強連結成分のID
    vector<vector<int>> scc; /// scc[i] = i個目の強連結成分に属する頂点

    template<class E>
    SCC(const Graph<E> &g, const Graph<E> &rg) {
        int V = (int)g.size();
        used = vector<bool>(V);
        res = vector<int>(V);
        gc = 0;

        fill(begin(used), end(used), false);
        for (int i = 0; i < V; i++) {
            if (!used[i]) dfs(g, i);
        }
        fill(begin(used), end(used), false);
        for (int i = vs.size()-1; i >= 0; i--) {
            if (!used[vs[i]]) {
                scc.push_back(vector<int>());
                rdfs(rg, vs[i], gc++, scc.back());
            }
        }        
    }

    vector<bool> used;
    vector<int> vs;

    template<class E>
    void dfs(const Graph<E> &g, int v) {
        used[v] = true;
        for (E e: g[v]) {
            if (!used[e.to]) dfs(g, e.to);
        }
        vs.push_back(v);
    }

    template<class E>
    void rdfs(const Graph<E> &rg, int v, int k, vector<int> &vv) {
        used[v] = true;
        res[v] = k; vv.push_back(v);
        for (E e: rg[v]) {
            if (!used[e.to]) rdfs(rg, e.to, k, vv);
        }
    }
};
