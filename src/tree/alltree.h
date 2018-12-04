template <class N, class E> struct AllTree {
    int n;
    const VV<E>& g;
    V<N> sm;
    VV<N> dp;
    void dfs1(int p, int b) {
        sm[p] = N();
        for (auto e : g[p]) {
            int d = e.to;
            if (d == b) continue;
            dfs1(d, p);
            sm[p] = sm[p] + sm[d].first(p, e);
        }
        sm[p].finish(p);
    }
    void dfs2(int p, int b, N top) {
        int deg = int(g[p].size());
        dp[p] = V<N>(deg + 1);
        dp[p][0] = N();
        for (int i = 0; i < deg; i++) {
            int d = g[p][i].to;
            dp[p][i + 1] = dp[p][i] + (d == b ? top : sm[d]).first(p, g[p][i]);
        }
        N rnode = N();
        for (int i = deg - 1; i >= 0; i--) {
            int d = g[p][i].to;
            if (d != b) {
                dfs2(d, p, (dp[p][i] + rnode).finish(p));
            }
            dp[p][i] = dp[p][i] + rnode;
            rnode = rnode + (d == b ? top : sm[d]).first(p, g[p][i]);
        }
    }
    AllTree(const VV<E>& _g) : n(int(_g.size())), g(_g), sm(n), dp(n) {
        dfs1(0, -1);
        dfs2(0, -1, N());
    }
};
template <class N, class E> VV<N> get_all_tree(const VV<E>& g) {
    return AllTree<N, E>(g).dp;
}

struct Node {
    // サンプル 木の直径
    // firstは 根付き木->森
    // finishは森->根付き木
    int rad, dia;
    int rd[2];
    Node() {
        // !!!!!森を生成すること!!!!!
        rad = 0;
        dia = 0;
        rd[0] = rd[1] = 0;
    }
    template <class E> Node first(int par, const E& e) {
        // 根付き木->森 上に辺を追加するイメージ e=(par -> node)
        rd[0] = rad + e.dist;
        rd[1] = 0;
        return *this;
    }
    Node operator+(const Node& r) {
        // 結合則が必須 上に辺を追加された木をまとめるイメージ
        Node n;
        vector<int> v;
        v.push_back(rd[0]);
        v.push_back(rd[1]);
        v.push_back(r.rd[0]);
        v.push_back(r.rd[1]);
        sort(begin(v), end(v), greater<int>());
        n.rd[0] = v[0];
        n.rd[1] = v[1];
        n.dia = max(dia, r.dia);
        return n;
    }
    Node finish(int par) {
        // 元締めとしてidxを追加するイメージ
        rad = rd[0];
        dia = max(dia, rd[0] + rd[1]);
        return *this;
    }
};
