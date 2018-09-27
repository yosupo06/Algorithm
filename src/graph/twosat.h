struct TwoSat {
    V<bool> res;

    struct Edge { int to; };
    VV<Edge> g;

    //(a == a_exp) || (b == b_exp)
    void add_cond(int a, bool a_exp, int b, bool b_exp) {
        g[2 * a + (a_exp ? 0 : 1)].push_back(Edge{2 * b + (b_exp ? 1 : 0)});
        g[2 * b + (b_exp ? 0 : 1)].push_back(Edge{2 * a + (a_exp ? 1 : 0)});
    }
    bool exec() {
        int n = int(res.size());
        auto s = get_scc(g);
        for (int i = 0; i < n; i++) {
            if (s.id[2 * i] == s.id[2 * i + 1]) return false;
            res[i] = s.id[2 * i] < s.id[2 * i + 1];
        }
        return true;
    }
    TwoSat() {}
    TwoSat(int n) {
        g = VV<Edge>(2 * n);
        res = V<bool>(n);
    }
};
