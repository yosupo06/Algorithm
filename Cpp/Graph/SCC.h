/**
 * SCC, つまり強連結成分分解を行うライブラリ
 *
 * 使用法は結構複雑
 *
 * template引数のint Vは頂点の最大数
 */
template<int V>
struct SCC {
    vector<int> g[V], rg[V];
    /// i-jに無向辺を追加する
    void add(int i, int j) {
        g[i].push_back(j);
        rg[j].push_back(i);
    }

    vector<int> vs;
    bool used[V];
    void dfs(int v) {
        used[v] = true;
        for (int d: g[v]) {
            if (used[d]) continue;
            dfs(d);
        }
        vs.push_back(v);
    }
    int res[V]; /// res[i] = 頂点iの属する強連結成分のID
    vector<int> scc[V]; /// scc[i] = i個目の強連結成分に属する頂点
    void rdfs(int v, int k) {
        used[v] = true;
        res[v] = k;
        scc[k].push_back(v);
        for (int d: rg[v]) {
            if (used[d]) continue;
            rdfs(d, k);
        }
    }

    /**
     * 頂点0..v-1に対してSCCを行う
     *
     * 返り値として強連結成分の個数が返される
     * これを呼び出すとres[0..v-1], scc[0..v-1]に情報が入る
     */
    int exec(int v) {
        fill_n(used, v, false);
        for (int i = 0; i < v; i++) {
            if (used[i]) continue;
            dfs(i);
        }
        fill_n(used, v, false);
        int k = 0;
        for (int i = vs.size()-1; i >= 0; i--) {
            if (used[vs[i]]) continue;
            rdfs(vs[i], k);
            k++;
        }
        return k;
    }
};