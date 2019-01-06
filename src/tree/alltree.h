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
            sm[p] = sm[p] + sm[d].to_subs(p, e);
        }
        sm[p].join(p);
    }
    void dfs2(int p, int b, N top) {
        int deg = int(g[p].size());
        dp[p] = V<N>(deg + 1);
        dp[p][0] = N();
        for (int i = 0; i < deg; i++) {
            int d = g[p][i].to;
            dp[p][i + 1] = dp[p][i] + (d == b ? top : sm[d]).to_subs(p, g[p][i]);
        }
        N rnode = N();
        for (int i = deg - 1; i >= 0; i--) {
            int d = g[p][i].to;
            if (d != b) {
                dfs2(d, p, (dp[p][i] + rnode).join(p));
            }
            dp[p][i] = dp[p][i] + rnode;
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

//TODO : add sample, calc radius of tree
struct Node {
    //Educational DP Contest V - Subtree
    Mint sm = Mint(0);
    Node() {
        //empty subtree
        sm = 1;
    }
    template <class E> Node to_subs(int, const E&) const {
        //tree -> subtrees
        Node n = *this;
        n.sm += Mint(1);
        return n;
    }
    Node operator+(const Node& r) const {
        //subtrees + subtrees
        Node n;
        n.sm = sm * r.sm;
        return n;
    }
    Node join(int) const {
        //subtrees -> tree
        return *this;
    }
};
