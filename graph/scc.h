struct SCC {
    V<int> id;
    VV<int> groups;
};

template<class E>
struct SCC_EXEC {
    const VV<E> &g;
    int tm = 0;
    V<bool> inS;
    V<int> id, low, ord, st;
    VV<int> groups;
    void dfs(int v) {
        low[v] = ord[v] = tm++;
        st.push_back(v);
        inS[v] = true;
        for (auto e: g[v]) {
            if (ord[e.to] == -1) {
                dfs(e.to);
                low[v] = min(low[v], low[e.to]);
            } else if (inS[e.to]) {
                low[v] = min(low[v], ord[e.to]);
            }
        }
        if (low[v] == ord[v]) {
            V<int> gr;
            while (true) {
                int u = st.back(); st.pop_back();
                gr.push_back(u);
                if (u == v) break;
            }
            for (int x: gr) inS[x] = false;
            groups.push_back(gr);
        }
    }
    SCC info;
    SCC_EXEC(const VV<E> &g) : g(g) {
        int n = int(g.size());
        inS = V<bool>(n); low = V<int>(n); ord = V<int>(n, -1);
        for (int i = 0; i < n; i++) {
            if (ord[i] == -1) dfs(i);
        }
        reverse(begin(groups), end(groups));
        V<int> id(n);
        for (int i = 0; i < int(groups.size()); i++) {
            for (int x: groups[i]) {
                id[x] = i;
            }
        }
        info = SCC{id, groups};
    }
};
template<class E> SCC scc(const VV<E> &g) { return SCC_EXEC<E>(g).info; }
