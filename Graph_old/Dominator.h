template <int N>
struct Dominator {
    int idom[N], sdom[N];
    vector<int> g[N], rg[N];
    void init() {
        for (int i = 0; i < N; i++) {
            g[i].clear(); rg[i].clear();
        }
    }
    void add(int a, int b) {
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    int idc, id[N], rid[N], par[N];
    void dfs(int p, int b) {
        if (id[p] != -1) return;
        par[p] = b;
        id[p] = idc; rid[idc] = p; idc++;
        for (int d: g[p]) {
            dfs(d, p);
        }
    }

    // unionfind
    int p[N];
    int mv[N];
    void merge(int a, int b) {
        p[a] = b;
    }
    int group(int a) {
        if (p[a] == -1) return a;
        int pa = group(p[a]);
        if (id[sdom[mv[a]]] > id[sdom[mv[p[a]]]]) {
            mv[a] = mv[p[a]];
        }
        return p[a] = pa;
    }

    vector<int> bucket[N];
    int V[N];
    void exec(int s, int n = N) {
        // uf init
        fill_n(p, n, -1);
        iota(mv, mv+n, 0);

        fill_n(id, n, -1);
        idc = 0;
        dfs(s, -1);
        iota(sdom, sdom+n, 0);

        for (int i = n-1; i > 0; i--) {
            int u = rid[i];
            for (int v: rg[u]) {
                group(v);
                sdom[u] = rid[min(id[sdom[u]], id[sdom[mv[v]]])];
            }
            bucket[sdom[u]].push_back(u);
            for (int v: bucket[par[u]]) {
                group(v);
                V[v] = mv[v];
            }
            bucket[par[u]].clear();
            merge(u, par[u]);
        }

        idom[s] = -1;
        for (int i = 1; i < n; i++) {
            int u = rid[i], v = V[u];
            if (sdom[u] == sdom[v]) idom[u] = sdom[u];
            else idom[u] = idom[v];
        }
    }
};
