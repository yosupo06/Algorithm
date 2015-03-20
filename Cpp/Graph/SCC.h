/*
SCC
使用法が困難
templateには頂点の最大数を入れる
add(i, j)で辺の追加
exec(v)は、頂点0..v-1にSCCを行い、その結果生まれた強連結成分の個数を返す
res[i]には頂点iの属する強連結成分のID
scc[i]にはi個目の強連結成分に属する頂点が入っている
scc[res[i]]で頂点iと同じ強連結成分の一覧が得られる
*/
template<int V>
struct SCC {
    vector<int> g[V], rg[V];
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
    int k;
    int res[V];
    vector<int> scc[V];
    void rdfs(int v) {
        used[v] = true;
        res[v] = k;
        scc[k].push_back(v);
        for (int d: rg[v]) {
            if (used[d]) continue;
            rdfs(d);
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
            rdfs(vs[i]);
            k++;
        }
        return k;
    }
};