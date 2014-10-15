const int MAX_V = 20000;
int V;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];
void add_edge(int u, int v) {
    G[u].push_back(v+10000);
    G[v+10000].push_back(u);
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

int bit_matching() {
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

template<int V>
struct BitMatching {
    vector<int> G[2*V];
    int match[2*V];
    bool used[2*V];
    void add_edge(int a, int b) {
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

    int bit_matching() {
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