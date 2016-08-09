/**
 * とりあえず正しい答えは返しそう
 * 現時点では使い物にならないし絶対定数倍改善しような
 */
template<int N>
struct ETTree {
    struct Node;
    typedef Node* NP;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz, idl, idr;
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
        void getall(vector<int> &v) {
            if (this == last) return;
            l->getall(v);
            v.push_back(idl);
            v.push_back(idr);
            r->getall(v);
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
        assert(mp[y].count(x));
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
    int sz(int x) {
        return tree(x)->sz / 2 - 1;
    }
    vector<int> getall(int x) {
        vector<int> v;
        tree(x).getall(v);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        return v;
    }
    //debug用　めっちゃ重いよ
    void scan() {
        for (int i = 0; i <= N; i++) {
            for (auto p: mp[i]) {
                assert(0 <= p.second && p.second < 2*N);
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

template<int N>
struct DynamicConnectivity {
    const static int LGN = 20;
    typedef pair<int, int> P;
    ETTree<N> ett[LGN+1];
    set<P> f;
    map<P, int> level;
    set<int> g[LGN+1][N];
    void add(int x, int y) {
        if (x > y) swap(x, y);
        assert(level.count(P(x, y)) == 0);
        level[P(x, y)] = LGN;
        g[LGN][x].insert(y);
        g[LGN][y].insert(x);
        if (!same(x, y)) {
            ett[LGN].evert(x);
            ett[LGN].link(x, y);
            f.insert(P(x, y));
        }
    }
    void del(int x, int y) {
        if (x > y) swap(x, y);
        assert(level.count(P(x, y)));
        int l = level[P(x, y)];
        level.erase(P(x, y));
        g[l][x].erase(y);
        g[l][y].erase(x);
        if (!f.count(P(x, y))) {
            level.erase(P(x, y));
            return;
        }
        ett[l].evert(y);
        ett[l].cut(x, y);
        for (int i = l; i <= LGN; i++) {
            int u = x, v = y;
            if (ett[i].sz(u) > ett[i].sz(v)) swap(u, v);
            int us = ett[i].sz(u);
            auto ut = ett[i].tree(u);
            for (int j = 0; j < us*2+1; j++) {
                ut->splay();
                ut = ett[i].at(ut, j);
                int p = ut->idr;
                int r = -1;
                auto it = g[i][p].begin();
                for (; it != g[i][p].end(); it++) {
                    int w = *it;
                    int ww = w, pp = p;
                    if (ww > pp) swap(ww, pp);
                    if (ett[i].root(w) == v) {
                        r = w;
                        f.insert(P(ww, pp));
                        ett[l].evert(ww);
                        ett[l].link(ww, pp);
                        break;
                    } else {
                        level[P(ww, pp)]--;
                        g[i-1][p].insert(w);
                        g[i-1][w].insert(p);
                        g[i][w].erase(p);
                    }
                }
                g[i][p].erase(g[i][p].begin(), it);
            }
        }
    }
    bool same(int x, int y) {
        return ett[LGN].root(x) == ett[LGN].root(y);
    }
    void scan() {
        for (int i = 0; i <= LGN; i++) {
            ett[i].scan();
        }
    }
};