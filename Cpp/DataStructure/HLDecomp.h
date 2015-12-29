struct Tree {
    typedef Tree* NP;
    NP l, r;
    struct Node {
        Node(int sz = 0) : sz(sz), lzf(false) {}
        int sz;
        int d, sm, lz;
        int lsm, rsm, ma, mv;
        bool lzf;
    } n;
    Tree() {}
    Tree(int sz, int hev[], int hevsm[], int data[]) : n(sz) {
        if (sz == 1) {
            lzdata(data[0]);
            return;
        }
        int sm = hevsm[sz] - hevsm[0];
        int md = lower_bound(hevsm, hevsm+sz-1, sm/2+hevsm[0]) - hevsm;
        l = new Tree(md, hev, hevsm, data);
        r = new Tree(sz - md, hev+md, hevsm+md, data+md);
        update();
    }
    void lzdata(int d) {
        n.d = n.mv = d;
        n.sm = n.sz*d;
        n.lsm = n.rsm = n.ma = max(0, n.sm);
        n.lz = d;
        n.lzf = true;
    }
    void update() {
        n.sm = l->n.sm+r->n.sm;
        n.lsm = max(l->n.lsm, l->n.sm+r->n.lsm);
        n.rsm = max(r->n.rsm, r->n.sm+l->n.rsm);
        n.ma = max(max(l->n.ma, r->n.ma), l->n.rsm+r->n.lsm);
        n.mv = max(l->n.mv, r->n.mv);
    }
    void push() {
        if (n.sz == 1) return;
        if (n.lzf) {
            l->lzdata(n.lz);
            r->lzdata(n.lz);
            n.lzf = false;
        }
    }
    // void set(int k, int x) {
    //     if (n.sz == 1) {
    //         lzdata(x);
    //         return;
    //     }
    //     push();
    //     if (k < l->n.sz) {
    //         l->set(k, x);
    //     } else {
    //         r->set(k - l->n.sz, x);
    //     }
    //     update();
    // }
    void set(int a, int b, int x) {
        if (b <= 0 || n.sz <= a) {
            return;
        }
        push();
        if (a <= 0 && n.sz <= b) {
            lzdata(x);
            return;
        }
        l->set(a, b, x);
        r->set(a - l->n.sz, b - l->n.sz, x);
        update();
    }
    static Node merge(const Node &l, const Node &r) {
        if (l.sz == 0) return r;
        if (r.sz == 0) return l;
        Node res(l.sz + r.sz);
        res.sm = l.sm+r.sm;
        res.lsm = max(l.lsm, l.sm+r.lsm);
        res.rsm = max(r.rsm, r.sm+l.rsm);
        res.ma = max(max(l.ma, r.ma), l.rsm+r.lsm);
        res.mv = max(l.mv, r.mv);
        return res;
    }
    static Node rev(Node u) {
        swap(u.lsm, u.rsm);
        return u;
    }
    Node get(int a, int b) {
        if (b <= 0 || n.sz <= a) {
            return Node();
        }
        push();
        if (a <= 0 && n.sz <= b) {
            return n;
        }
        return merge(l->get(a, b), r->get(a- l->n.sz, b- l->n.sz));
    }
};

template <int N>
struct HLComp {
    vector<int> g[N];

    P n2l[N]; //node to line (line id - line pos)
    int lc;
    Tree *li[N]; //line data
    P l2p[N]; //line to parent
    int sz[N]; //node size

    int data[N]; // my data

    int buf[N]; // buffer of sz - sz[child]
    int bufsm[N+1];
    int bufdata[N]; // buffer of mydata
    int ldps[N]; // line dps

    void add(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void dfs_sz(int p, int b) {
        sz[p] = 1;
        for (int d: g[p]) {
            if (d == b) continue;
            dfs_sz(d, p);
            sz[p] += sz[d];
        }
    }
    void dfs(int p, int b) {
        if (g[p].size() == (b == -1 ? 0 : 1)) {
            // make line
            buf[n2l[p].second] = 1;
            bufdata[n2l[p].second] = data[p];
            bufsm[n2l[p].second+1] = bufsm[n2l[p].second] + buf[n2l[p].second];
            li[n2l[p].first] = new Tree(n2l[p].second+1, buf, bufsm, bufdata);
            return;
        }
        int ma = -1, md = -1;
        for (int d: g[p]) {
            if (d == b) continue;
            if (ma < sz[d]) {
                ma = sz[d];
                md = d;
            }
        }
        n2l[md] = P(n2l[p].first, n2l[p].second+1);
        buf[n2l[p].second] = sz[p]-sz[md];
        bufdata[n2l[p].second] = data[p];
        bufsm[n2l[p].second+1] = bufsm[n2l[p].second] + buf[n2l[p].second];
        dfs(md, p);
        for (int d: g[p]) {
            if (d == b) continue;
            if (d == md) continue;
            n2l[d] = P(lc, 0);
            l2p[lc] = n2l[p];
            ldps[lc] = ldps[n2l[p].first]+1;
            lc++;
            dfs(d, p); // light
        }
    }
    void init() {
        n2l[0] = P(0, 0);
        l2p[0] = P(-1, 0);
        ldps[0] = 0;
        bufsm[0] = 0;
        lc = 1;
        dfs_sz(0, -1);
        dfs(0, -1);
    }
    // void data_set(int k, int x) {
    //     li[n2l[k].first]->set(n2l[k].second, x);
    // }
    int lca_line(int u, int v) {
        int xl = n2l[u].first;
        int yl = n2l[v].first;
        if (ldps[xl] < ldps[yl]) swap(xl, yl);
        while (ldps[xl] > ldps[yl]) {
            xl = l2p[xl].first;
        }
        while (xl != yl) {
            xl = l2p[xl].first;
            yl = l2p[yl].first;
        }
        return xl;
    }

    void path_set(int u, int v, int d) {
        int xl, xp; tie(xl, xp) = n2l[u];
        int yl, yp; tie(yl, yp) = n2l[v];
        int lc = lca_line(u, v);
        while (xl != lc) {
            li[xl]->set(0, xp+1, d);
            tie(xl, xp) = l2p[xl];            
        }
        while (yl != lc) {
            li[yl]->set(0, yp+1, d);
            tie(yl, yp) = l2p[yl];
        }
        if (xp > yp) {
            li[xl]->set(yp, xp+1, d);
        } else {
            li[yl]->set(xp, yp+1, d);
        }   
    }
    Tree::Node path_get(int u, int v) {
        int xl, xp; tie(xl, xp) = n2l[u];
        int yl, yp; tie(yl, yp) = n2l[v];
        int lc = lca_line(u, v);
        Tree::Node nl, nr;
        while (xl != lc) {
            nl = Tree::merge(li[xl]->get(0, xp+1), nl);
            tie(xl, xp) = l2p[xl];
        }
        while (yl != lc) {
            nr = Tree::merge(li[yl]->get(0, yp+1), nr);
            tie(yl, yp) = l2p[yl];
        }
        if (xp > yp) {
            nl = Tree::merge(li[xl]->get(yp, xp+1), nl);
        } else {
            nr = Tree::merge(li[yl]->get(xp, yp+1), nr);
        }
        nl = Tree::rev(nl);
        return Tree::merge(nl, nr);
    }
};

