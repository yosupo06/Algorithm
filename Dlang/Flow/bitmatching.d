class BitMatching {
    const int V;
    int[][] G;
    int[] match, used;

    this(int v) {
        V = v;
        G = new int[][2*V];
        match = new int[2*V];
        used = new int[2*V];
    }

    void addEdge(int a, int b) {
        G[a] ~= (b+V);
        G[b+V] ~= (a);
    }

    bool dfs(int v) {
        used[v] = true;
        for (int i = 0; i < G[v].length; i++) {
            int u = G[v][i], w = match[u];
            if (w < 0 || (!used[w] && dfs(w))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

    int bitMatching() {
        int res = 0;
        match[] = -1;
        for (int v = 0; v < V; v++) {
            if (match[v] < 0) {
                used[] = 0;
                if (dfs(v)) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    BitMatching bm;
    return 0;
}