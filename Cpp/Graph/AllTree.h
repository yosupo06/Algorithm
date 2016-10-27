template<class N>
struct AllTree {
    vector<vector<N>> ldp;
    AllTree() {}
    template<class E>
    AllTree(const Graph<E> &g, const TreeOrd &t, int r = 0) {
        int n = int(g.size());
        auto sm = vector<N>(n), top = vector<N>(n);
        ldp = vector<vector<N>>(n);
        for (int i = 0; i < n; i++) {
            ldp[i].resize(int(g[i].size())+1);
        }
        for (auto pa: t.rs) {
            // first
            int p, b; tie(p, b) = pa;
            sm[p] = N();
            for (const E &e: g[p]) {
                int d = e.to;
                if (d == b) continue;
                sm[p] = sm[p] + N(sm[d]).first(p, e);
            }
            sm[p].finish(p);
        }
        top[r] = N();
        for (auto pa: t.s) {
            // second
            int p, b; tie(p, b) = pa;
            int dg = int(g[p].size());
            vector<N> &ln = ldp[p];
            ln[0] = N();
            for (int i = 0; i < dg; i++) {
                int d = g[p][i].to;
                ln[i+1] = ln[i] + N(d==b ? top[p] : sm[d]).first(p, g[p][i]);
            }
            N rnode = N();
            for (int i = dg-1; i >= 0; i--) {
                int d = g[p][i].to;
                if (d != b) {
                    top[d] = (ln[i]+rnode).finish(p);
                }
                ln[i] = ln[i] + rnode;
                rnode = rnode + N(d==b ? top[p] : sm[d]).first(p, g[p][i]);
            }
        }
    }
    N get(int p, int idx = -1) {
        if (idx == -1) idx = int(ldp[p].size())-1;
        return N(ldp[p][idx]).finish(p);
    }
};

struct Node {
    // サンプル 木の直径
    // firstは 根付き木->森
    // finishは森->根付き木
    int rad, dia;
    int rd[2];
    Node() {
        // !!!!!森を生成すること!!!!!
        rad = 0; dia = 0;
        rd[0] = rd[1] = 0;
    }
    template<class E>
    Node first(int par, const E &e) {
        // 根付き木->森 上に辺を追加するイメージ e=(par -> node)
        rd[0] = rad+e.dist;
        rd[1] = 0;
        return *this;
    }
    Node operator+(const Node &r) {
        // 結合則が必須 上に辺を追加された木をまとめるイメージ
        Node n;
        vector<int> v;
        v.push_back(rd[0]); v.push_back(rd[1]);
        v.push_back(r.rd[0]); v.push_back(r.rd[1]);
        sort(begin(v), end(v), greater<int>());
        n.rd[0] = v[0];
        n.rd[1] = v[1];
        n.dia = max(dia, r.dia);
        return n;
    }
    Node finish(int par) {
        // 元締めとしてidxを追加するイメージ
        rad = rd[0];
        dia = max(dia, rd[0]+rd[1]);
        return *this;
    }
};
