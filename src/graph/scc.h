struct SCC {
    V<int> id;
    VV<int> groups;
};

template <class E> struct SCCExec : SCC {
    int n;
    const VV<E>& g;
    int tm = 0;
    V<bool> flag;
    V<int> low, ord, st;
    void dfs(int v) {
        low[v] = ord[v] = tm++;
        st.push_back(v);
        flag[v] = true;
        for (auto e : g[v]) {
            if (ord[e.to] == -1) {
                dfs(e.to);
                low[v] = min(low[v], low[e.to]);
            } else if (flag[e.to]) {
                low[v] = min(low[v], ord[e.to]);
            }
        }
        if (low[v] == ord[v]) {
            V<int> gr;
            while (true) {
                int u = st.back();
                st.pop_back();
                gr.push_back(u);
                if (u == v) break;
            }
            for (int x : gr) flag[x] = false;
            groups.push_back(gr);
        }
    }
    SCCExec(const VV<E>& _g)
        : n(int(_g.size())), g(_g), flag(n), low(n), ord(n, -1) {
        id = V<int>(n);
        for (int i = 0; i < n; i++) {
            if (ord[i] == -1) dfs(i);
        }
        reverse(groups.begin(), groups.end());
        for (int i = 0; i < int(groups.size()); i++) {
            for (int x : groups[i]) {
                id[x] = i;
            }
        }
    }
};

template <class E> struct KosarajuSCCExec : SCC {
    int n;
    const VV<E>& g;
    const VV<E>& rg;
    V<int> vs;
    V<bool> used;
    void dfs(int v) {
        used[v] = true;
        for (E e : g[v]) {
            if (!used[e.to]) dfs(e.to);
        }
        vs.push_back(v);
    }

    void rdfs(int v, int k) {
        used[v] = true;
        id[v] = k;
        groups[k].push_back(v);
        for (E e : rg[v]) {
            if (!used[e.to]) rdfs(e.to, k);
        }
    }

    KosarajuSCCExec(const VV<E>& _g, const VV<E>& _rg)
        : n(int(_g.size())), g(_g), rg(_rg) {
        used = V<bool>(n);
        for (int i = 0; i < n; i++) {
            if (!used[i]) dfs(i);
        }
        reverse(vs.begin(), vs.end());
        used = V<bool>(n);
        id = V<int>(n);
        int k = 0;
        for (int i : vs) {
            if (!used[i]) {
                groups.push_back({});
                rdfs(i, k++);
            }
        }
    }
};

template <size_t N> struct BitsetSCCExec : SCC {
    using B = bitset<N>;
    int n;
    const V<B>& g;
    const V<B>& rg;
    V<int> vs;
    B unvis;
    void dfs(int v) {
        unvis.reset(v);
        while (true) {
            int d = (unvis & g[v])._Find_first();
            if (d >= n) break;
            dfs(d);
        }
        vs.push_back(v);
    }

    void rdfs(int v, int k) {
        unvis.reset(v);
        id[v] = k;
        groups[k].push_back(v);
        while (true) {
            int d = (unvis & rg[v])._Find_first();
            if (d >= n) break;
            rdfs(d, k);
        }
    }

    BitsetSCCExec(const V<B>& _g, const V<B>& _rg)
        : n(int(_g.size())), g(_g), rg(_rg) {
        unvis.set();
        for (int i = 0; i < n; i++) {
            if (unvis[i]) dfs(i);
        }
        reverse(vs.begin(), vs.end());
        unvis.set();
        id = V<int>(n);
        int k = 0;
        for (int i : vs) {
            if (unvis[i]) {
                groups.push_back({});
                rdfs(i, k++);
            }
        }
    }
};

template <class E> SCC get_scc(const VV<E>& g) { return SCCExec<E>(g); }
template <class E> SCC get_kosaraju_scc(const VV<E>& g, const VV<E>& rg) {
    return KosarajuSCCExec<E>(g, rg);
}
template <size_t N>
SCC get_bitset_scc(const V<bitset<N>>& g, const V<bitset<N>>& rg) {
    return BitsetSCCExec<N>(g, rg);
}
