struct Dominator {
    V<int> idom, sdom;
    LowLink lc;
    Dominator() {}
    template<class E>
    Dominator(const VV<E> &g, const VV<E> &rg, int s) {
        lc = LowLink(g, s);
        int n = (int)g.size();
        
        // uf init
        p.resize(V); mv.resize(V);
        fill_n(p.begin(), V, -1);
        iota(mv.begin(), mv.end(), 0);
        idom = vector<int>(V, -1);
        sdom = vector<int>(V);
        iota(sdom.begin(), sdom.end(), 0);

        vector<int> up(V);
        vector<vector<int>> bucket(V);
        int U = int(lc.vlis.size());
        for (int i = U-1; i > 0; i--) {
            int u = lc.vlis[i];
            for (E e: rg[u]) {
                if (lc.ord[e.to] == -1) continue;
                sdom[u] = lc.vlis[min(lc.ord[sdom[u]], lc.ord[sdom[compress(e.to)]])];
            }
            bucket[sdom[u]].push_back(u);
            for (int v: bucket[lc.par[u]]) {
                up[v] = compress(v);
            }
            bucket[lc.par[u]].clear();
            p[u] = lc.par[u]; // uf merge
        }

        for (int i = 1; i < U; i++) {
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
