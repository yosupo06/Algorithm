struct Dominator {
    vector<int> idom, sdom;

    template<class E>
    Dominator(const Graph<E> &g, const Graph<E> &rg, int s, const LowLink &lc) {
        int V = (int)g.size();
        
        // uf init
        p.resize(V); mv.resize(V);
        fill_n(p.begin(), V, -1);
        iota(mv.begin(), mv.end(), 0);
        idom.resize(V); sdom.resize(V);
        iota(sdom.begin(), sdom.end(), 0);

        vector<int> up(V);
        vector<vector<int>> bucket(V);
        for (int i = V-1; i > 0; i--) {
            int u = lc.vlis[i];
            for (E e: rg[u]) {
                sdom[u] = lc.vlis[min(lc.ord[sdom[u]], lc.ord[sdom[compress(e.to)]])];
            }
            bucket[sdom[u]].push_back(u);
            for (int v: bucket[lc.par[u]]) {
                up[v] = compress(v);
            }
            bucket[lc.par[u]].clear();
            p[u] = lc.par[u]; // uf merge
        }

        idom[s] = -1;
        for (int i = 1; i < V; i++) {
            int u = lc.vlis[i], v = up[u];
            if (sdom[u] == sdom[v]) idom[u] = sdom[u];
            else idom[u] = idom[v];
        }
    }

    // unionfind
    vector<int> p, mv; // parent, min sdom's v
    int compress(int a) {
        if (p[a] != -1) {
            compress(p[a]);
            if (lc.ord[sdom[mv[a]]] > lc.ord[sdom[mv[p[a]]]]) {
                mv[a] = mv[p[a]];
            }
            p[a] = (p[p[a]] == -1 ? p[a] : p[p[a]]);
        }
        return mv[a];
    }
};
