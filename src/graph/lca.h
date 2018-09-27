struct LCA {
    int lg;
    VV<int> anc;
    V<int> dps;
    /// lとrの頂点のLCAを求める
    int query(int l, int r) {
        if (dps[l] < dps[r]) swap(l, r);
        int dd = dps[l]-dps[r];
        for (int i = lg-1; i >= 0; i--) {
            if (dd < (1<<i)) continue;
            dd -= 1<<i;
            l = anc[i][l];
        }
        if (l == r) return l;
        for (int i = lg-1; i >= 0; i--) {
            if (anc[i][l] == anc[i][r]) continue;
            l = anc[i][l]; r = anc[i][r];
        }
        return anc[0][l];
    }
};

template<class E>
struct LCA_EXEC : LCA {
    const VV<E>& g;

    /// 事前処理を行う rはroot頂点のid
    LCA_EXEC(const VV<E>& _g, int r) : g(_g) {
        int N = int(g.size());
        lg = 1;
        while ((1<<lg) < N) lg++;
        anc = VV<int>(lg, V<int>(N, -1));
        dps = V<int>(N);
        dfs(r, -1, 0);
        for (int i = 1; i < lg; i++) {
            for (int j = 0; j < N; j++) {
                anc[i][j] = (anc[i-1][j] == -1) ? -1 : anc[i-1][anc[i-1][j]];
            }
        }
    }

    void dfs(int p, int b, int now) {
        anc[0][p] = b;
        dps[p] = now;
        for (E e: g[p]) {
            if (e.to == b) continue;
            dfs(e.to, p, now+1);
        }
    }
};

template <class E>
LCA get_lca(const VV<E> &g, int r) { return LCA_EXEC<E>(g, r); }
