/**
 * 森に対するクエリを処理する動的木 部分木クエリに対して強い
 *
 * 現時点ではevert無しのみ
 */
struct ETDTree {
    struct Node;
    typedef Node* NP;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz, id, dps, dps_lz;
        pair<int, int> lca;
        Node(int id) :p(nullptr), l(last), r(last), sz(1), id(id),
                      dps(0), dps_lz(0), lca(P(0, id)) {}
        Node(NP n) : p(nullptr), l(last), r(last), sz(1), id(n->id),
                      dps(n->dps), dps_lz(0), lca(P(dps, id)) {}
        Node() : l(nullptr), r(nullptr), sz(0), id(-1) {}

        //pushをすると、pushをした頂点とその子の"すべて"の値の正当性が保証される
        void push() { 
            if (dps_lz) {
                if (l != last) {
                    l->dpslzdata(dps_lz);
                }
                if (r != last) {
                    r->dpslzdata(dps_lz);
                }
                dps_lz = 0;
            }
            assert(sz);
        }
        NP update() {
            assert(this != last);
            sz = 1+l->sz+r->sz;
            lca = P(dps, id);
            if (l != last) {
                lca = min(lca, l->lca);
            }
            if (r != last) {
                lca = min(lca, r->lca);
            }
            return this;
        }
        void dpslzdata(int x) {
            dps += x;
            dps_lz += x;
            lca.first += x;
        }

        inline int pos() {
            if (p) {
                if (p->l == this) return -1;
                if (p->r == this) return 1;
            }
            return 0;
        }
        void rot() {
            NP qq = p->p;
            int pps = p->pos();
            if (p->l == this) {
                p->l = r; r->p = p;
                r = p; p->p = this;
            } else {
                p->r = l; l->p = p;
                l = p; p->p = this;
            }
            p->update(); update();
            p = qq;
            if (!pps) return;
            if (pps == -1) {
                qq->l = this;
            } else {
                qq->r = this;
            }
            qq->update();
        }
        NP splay() {
            assert(this != last);
            supush();
            int ps;
            while ((ps = pos())) {
                int pps = p->pos();
                if (!pps) {
                    rot();
                } else if (ps == pps) {
                    p->rot(); rot();
                } else {
                    rot(); rot();
                }
            }
            return this;
        }
        void supush() {
            if (pos()) {
                p->supush();
            }
            push();
        }
        void debug() {
            if (this == last) return;
            push();
            l->debug();
            printf("(%d-%d %llx) ", id, dps, (unsigned long long)this & 0xffff);
            r->debug();
        }
    };
    int N;
    typedef pair<int, int> P;
    vector<int> parent;
    vector<Node> pool;
    ETDTree(int N) : N(N) {
        parent = vector<int>(N, N);
        pool = vector<Node>(2*N);
        for (int i = 0; i < N; i++) {
            pool[i*2] = Node(i);
            pool[i*2+1] = Node(N);
            NP x = &pool[i*2];
            NP y = &pool[i*2+1];
            merge(x, y);
        }
    }
    void debug(int d) {
        tree(d)->debug();
        assert(tree(d)->id == d);
        printf("\n");
    }

    NP tree(int d) {
        assert(0 <= d && d < N);
        return (&pool[d*2])->splay();
    }
    NP merge(NP l, NP r) {
        if (l == last) return r;
        if (r == last) return l;
        r = at(r, 0);
        r->l = l;
        l->p = r;
        return r->update();
    }
    pair<NP, NP> split(NP n, int k) {
        if (!k) return {last, n};
        if (n->sz == k) return {n, last};
        n = at(n, k);
        NP m = n->l;
        m->p = nullptr;
        n->l = last;
        n->update();
        return {m, n};
    }
    NP at(NP n, int k) {
        assert(n != last);
        n->push();
        if (k < n->l->sz) {
            return at(n->l, k);
        } else if (k == n->l->sz) {
            n->splay();
            return n;
        } else {
            return at(n->r, k-(n->l->sz+1));
        }
    }

    //yの子としてxを追加
    void link(int x, int y) {
        assert(parent[x] == N);
        NP n, m, u;
        n = tree(y);
        NP nn = &pool[x*2+1];
        nn->splay();
        assert(nn != nullptr);
        nn = split(nn, nn->sz-1).second;
        *nn = Node(n);
        tie(m, n) = split(n, n->l->sz+1);
        u = &pool[x*2];
        u->splay();
        u->dpslzdata(nn->dps+1);
        parent[x] = y;
        merge(merge(merge(m, u), nn), n);
    }
    //root(x) == y
    void cut(int x) {
        assert(parent[x] != N);
        parent[x] = N;
        NP r, s1;
        r = (&pool[x*2])->splay();
        tie(s1, r) = split(r, r->l->sz);
        NP s2 = (&pool[x*2+1])->splay();
        s2 = split(s2, s2->l->sz+1).second;
        merge(s1, s2);
        r->splay();
        r->dpslzdata(-r->dps);
    }


    int lca(int x, int y) {
        NP a = tree(x);
        int ac = a->l->sz;
        NP b = tree(y);
        int bc = b->l->sz;
        if (a->p == nullptr) return -1;
        if (ac > bc) {
            swap(ac, bc);
            swap(a, b);
        }
        b->splay();
        auto s = split(b, bc+1);
        auto t = split(s.first, ac);
        int res = t.second->lca.second;
        merge(merge(t.first, t.second), s.second);
        return res;
    }
    int root(int x) {
        return at(tree(x), 0)->id;
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
};
ETDTree::Node ETDTree::last_d = ETDTree::Node();
ETDTree::NP ETDTree::last = &last_d;



template<int N>
struct ETTree {
    struct Node;
    typedef Node* NP;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz, idl, idr;
        pair<int, int> lca;
        Node(int idl, int idr) :p(nullptr), l(last), r(last), sz(1), idl(idl), idr(idr) {}
        Node() : l(nullptr), r(nullptr), sz(0) {}

        //pushをすると、pushをした頂点とその子の"すべて"の値の正当性が保証される
        void push() { 
            assert(sz);
        }
        NP update() {
            assert(this != last);
            sz = 1+l->sz+r->sz;
            return this;
        }

        inline int pos() {
            if (p) {
                if (p->l == this) return -1;
                if (p->r == this) return 1;
            }
            return 0;
        }
        void rot() {
            NP qq = p->p;
            int pps = p->pos();
            if (p->l == this) {
                p->l = r; r->p = p;
                r = p; p->p = this;
            } else {
                p->r = l; l->p = p;
                l = p; p->p = this;
            }
            p->update(); update();
            p = qq;
            if (!pps) return;
            if (pps == -1) {
                qq->l = this;
            } else {
                qq->r = this;
            }
            qq->update();
        }
        NP splay() {
            assert(this != last);
            supush();
            int ps;
            while ((ps = pos())) {
                int pps = p->pos();
                if (!pps) {
                    rot();
                } else if (ps == pps) {
                    p->rot(); rot();
                } else {
                    rot(); rot();
                }
            }
            return this;
        }
        void supush() {
            if (pos()) {
                p->supush();
            }
            push();
        }
        void debug() {
            if (this == last) return;
            push();
            l->debug();
            printf("(%d-%d) ", idl, idr);
            r->debug();
        }
    };
    typedef pair<int, int> P;
    map<int, int> mp[N+1];
    Node pool[2*N];
    ETTree() {
        for (int i = 0; i < N; i++) {
            pool[2*i] = Node(N, i);
            pool[2*i+1] = Node(i, N);
            merge(pool+2*i, pool+2*i+1);
            mp[N][i] = 2*i;
            mp[i][N] = 2*i+1;
        }
    }
    void debug(int d) {
        tree(d)->debug();
    }

    NP tree(int d) {
        assert(0 <= d && d < N);
        return (&pool[mp[d].begin()->second])->splay();
    }
    NP merge(NP l, NP r) {
        if (l == last) return r;
        if (r == last) return l;
        r = at(r, 0);
        r->l = l;
        l->p = r;
        return r->update();
    }
    pair<NP, NP> split(NP n, int k) {
        if (!k) return {last, n};
        if (n->sz == k) return {n, last};
        n = at(n, k);
        NP m = n->l;
        m->p = nullptr;
        n->l = last;
        n->update();
        return {m, n};
    }
    NP at(NP n, int k) {
        assert(n != last);
        n->push();
        if (k < n->l->sz) {
            return at(n->l, k);
        } else if (k == n->l->sz) {
            n->splay();
            return n;
        } else {
            return at(n->r, k-(n->l->sz+1));
        }
    }

    //yの子としてxを追加
    void evert(int x) {
        int rt = root(x);
        NP xt = tree(x);
        auto sp = split(xt, xt->l->sz);
        NP L, ML, MR, R;
        tie(L, ML) = split(sp.first, 1);
        tie(MR, R) = split(sp.second, sp.second->sz-1);
        assert(L->idl == N && L->idr == rt && R->idl == rt && R->idr == N);
        int lp = mp[N][rt], rp = mp[rt][N];
        pool[lp].idr = x; pool[rp].idl = x;
        mp[N].erase(rt); mp[rt].erase(N);
        mp[N][x] = lp; mp[x][N] = rp;
        merge(merge(merge(L, MR), ML), R);
    }
    void link(int x, int y) {
        assert(mp[x].count(N));
        NP xt = tree(x);
        NP yt = tree(y);
        //ytの前にtree(x)を入れたい
        int lp = mp[N][x], rp = mp[x][N];
        pool[lp].idl = y; pool[rp].idr = y;
        mp[N].erase(x); mp[x].erase(N);
        mp[y][x] = lp; mp[x][y] = rp;
        auto sp = split(yt, yt->l->sz);
        merge(merge(sp.first, xt), sp.second);
    }
    void cut(int x, int y) {
        assert(mp[x].count(y));
        int lp = mp[y][x], rp = mp[x][y];
        NP lx = pool+lp, rx = pool+rp;
        pool[lp].idl = N; pool[rp].idr = N;
        mp[y].erase(x); mp[x].erase(y);
        mp[N][x] = lp; mp[x][N] = rp;
        // L M R
        NP L, M, R;
        rx->splay();
        R = split(rx, rx->l->sz+1).second;
        lx->splay();
        tie(L, M) = split(lx, lx->l->sz);
        merge(L, R);
    }
    int root(int x) {
        NP xt = tree(x);
        return at(xt, 0)->idr;
    }
    //debug用　めっちゃ重いよ
    void scan() {
        for (int i = 0; i <= N; i++) {
            for (auto p: mp[i]) {
                assert(pool[p.second].idl == i);
                assert(pool[p.second].idr == p.first);
            }
        }
    }
};
template<int N>
typename ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();
template<int N>
typename ETTree<N>::NP ETTree<N>::last = &last_d;