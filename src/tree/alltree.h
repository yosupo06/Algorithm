template <class N, class E> struct AllTree {
    int n;
    const VV<E>& g;
    V<N> sm;
    VV<N> dp;  // tree
    void dfs1(int p, int b) {
        sm[p] = N();
        for (auto e : g[p]) {
            int d = e.to;
            if (d == b) continue;
            dfs1(d, p);
            sm[p] = sm[p] + sm[d].to_subs(p, e);
        }
        sm[p] = sm[p].join(p);
    }
    void dfs2(int p, int b, N top) {
        int deg = int(g[p].size());
        dp[p] = V<N>(deg + 1);
        dp[p][0] = N();
        for (int i = 0; i < deg; i++) {
            int d = g[p][i].to;
            dp[p][i + 1] =
                dp[p][i] + (d == b ? top : sm[d]).to_subs(p, g[p][i]);
        }
        N rnode = N();
        dp[p].back() = dp[p].back().join(p);
        for (int i = deg - 1; i >= 0; i--) {
            dp[p][i] = (dp[p][i] + rnode).join(p);
            int d = g[p][i].to;
            if (d != b) dfs2(d, p, dp[p][i]);
            rnode = rnode + (d == b ? top : sm[d]).to_subs(p, g[p][i]);
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
    // Educational DP Contest V - Subtree
    Mint sm = Mint(1);
    template <class E> Node to_subs(int, const E&) const {
        // tree -> subtrees
        return {sm + 1};
    }
    Node operator+(const Node& r) const {
        // subtrees + subtrees
        return {sm * r.sm};
    }
    Node join(int) const {
        // subtrees -> tree
        return *this;
    }
};

struct Node {
    // Diameter of Tree
    int rad = 0, dia = 0;         // radius(tree), diameter
    array<int, 2> rd = {{0, 0}};  // radiuses(subtrees)
    template <class E> Node to_subs(int, const E& e) const {
        // tree -> subtrees
        return {-1, dia, {rad + e.dist, 0}};
    }
    Node operator+(const Node& r) const {
        // subtrees + subtrees
        array<int, 4> v = {rd[0], rd[1], r.rd[0], r.rd[1]};
        sort(v.begin(), v.end(), greater<>());
        return {-1, max(dia, r.dia), {v[0], v[1]}};
    }
    Node join(int) const {
        // subtrees -> tree
        return {rd[0], max(dia, rd[0] + rd[1]), {}};
    }
};
