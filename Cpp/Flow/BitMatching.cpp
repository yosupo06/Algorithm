template<int V>
struct BitMatching {
    vector<int> G[2*V];
    int match[2*V];
    bool used[2*V];
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