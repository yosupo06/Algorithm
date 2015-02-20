/*
使い方
addで辺を追加する
execで事前処理
その後queryでLCAが求められる
計算量は事前処理O(NlogN) クエリO(logN)
*/
template<int V>
struct LowestCommonAncestor {
    const static int LG = 25;
    int ro[LG][V];
    int dps[V];
    vector<int> g[V];
    void add(int i, int j) {
        g[i].push_back(j);
        g[j].push_back(i);
    }
    void dfs(int p, int b) {
        assert(ro[0][p] == -1);
        ro[0][p] = b;
        dps[p] = (b == -1) ? 0 : dps[b]+1;
        for (int d: g[p]) {
            if (d == b) continue;
            dfs(d, p);
        }
    }
    void exec(int r) {
        memset(ro, -1, sizeof(ro));
        dfs(r, -1);
        for (int i = 0; i < LG-1; i++) {
            for (int j = 0; j < V; j++) {
                ro[i+1][j] = (ro[i][j] == -1) ? -1 : ro[i][ro[i][j]];
            }
        }
    }
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
};