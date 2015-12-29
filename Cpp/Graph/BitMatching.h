/**
 * 二部最大マッチング
 *
 * O(EV)
 */
template<int V>
struct BitMatching {
    vector<int> G[2*V];
    int match[2*V];
    bool used[2*V];
    /// 初期化
    void init() {
        for (int i = 0; i < 2*V; i++) {
            G[i].clear();
        }
    }
    /// 左側のa番目と右側のb番目に辺を張る
    void add(int a, int b) {
        G[a].push_back(b+V);
        G[b+V].push_back(a);
    }

    bool dfs(int v) {
        used[v] = true;
        for (int i = 0; i < G[v].size(); i++) {
            int u = G[v][i], w = match[u];
            if (w < 0 || (!used[w] && dfs(w))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }
    /// 最大マッチングの本数が返される
    int exec() {
        int res = 0;
        memset(match, -1, sizeof(match));
        for (int v = 0; v < V; v++) {
            if (match[v] < 0) {
                memset(used, 0, sizeof(used));
                if (dfs(v)) {
                    res++;
                }
            }
        }
        return res;
    }
};