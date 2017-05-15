struct SCC {
    V<int> id;
    VV<int> groups;
    SCC() {}
    SCC(int n) { id = V<int>(n); }
};
 
template<class E>
SCC scc(const VV<E> &g) {
    int n = int(g.size());
    SCC scc(n);
    auto &id = scc.id;
    auto &groups = scc.groups;
    V<bool> inS(n);
    V<int> low(n);
    V<int> ord(n, -1);
    V<int> st;
    int tm = 0;
    auto dfs = recur([&](auto self, int v) -> void {
        low[v] = ord[v] = tm++;
        st.push_back(v);
        inS[v] = true;
        for (auto e: g[v]) {
            if (ord[e.to] == -1) {
                self(self, e.to);
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
    });
 
    for (int i = 0; i < n; i++) {
        if (ord[i] == -1) dfs(i);
    }
    reverse(begin(groups), end(groups));
    for (int i = 0; i < int(groups.size()); i++) {
        for (int x: groups[i]) {
            id[x] = i;
        }
    }
    return scc;
}
