template<int N>
struct ETTree {
    struct Node;
    typedef Node* NP;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz, idl, idr, idx;
        Node(int idl, int idr, int idx) :p(nullptr), l(last), r(last), sz(1), idl(idl), idr(idr), idx(idx) {
        }
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
    };

    int up[N];
    int tr[N];
    unordered_map<ull, int> mp;
    Node pool[2*N];
    ETTree() {
        for (int i = 0; i < N; i++) {
            up[i] = i;
            tr[i] = -1;
        }
    }

    NP tree(int d) {
        assert(0 <= d && d < N);
        if (tr[d] == -1) return last;
        return pool[tr[d]].splay();
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
        assert(0 <= k && k <= n->sz);
        if (!k) return {last, n};
        if (n->sz == k) return {n, last};
        n = at(n, k);
        NP m = n->l;
        m->p = nullptr;
        n->l = last;
        n->update();
        return {m, n};
    }
    pair<NP, NP> splitl(NP n) {
        if (n == last) return {last, last};
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
    pair<int, int> getmp(int x, int y) {
        int lp, rp;
        if (x < y) {
            assert(mp.count(((ull)(x)<<32) | y));
            rp = mp[((ull)(x)<<32) | y];
            lp = rp ^ 1;
        } else {
            assert(mp.count(((ull)(y)<<32) | x));
            lp = mp[((ull)(y)<<32) | x];
            rp = lp ^ 1;
        }
        return {lp, rp};
    }
    void evert(int x) {
        if (up[x] != -1) return;
        int rt = root(x);
        NP xt = tree(x);
        NP L, R;
        tie(L, R) = splitl(xt);
        swap(up[rt], up[x]);
        merge(R, L);
    }

    void link(int x, int y, int idx) {
        assert(root(x) != root(y));
        assert(up[x] != -1);
        NP xt = tree(x);
        NP yt = tree(y);
        int lp = up[x]*2, rp = up[x]*2+1;
        up[x] = -1;
        tr[y] = lp; tr[x] = rp;
        if (x < y) {
            mp[((ull)x<<32) | y] = rp;
        } else {
            mp[((ull)y<<32) | x] = lp;
        }
        pool[lp] = Node(y, x, idx);
        pool[rp] = Node(x, y, idx);
        auto sp = splitl(yt);
        NP lx = pool+lp, rx = pool+rp;
        merge(merge(merge(merge(sp.first, lx), xt), rx), sp.second);
    }
    void cut(int x, int y) {
        assert(root(x) == root(y));
        assert(up[x] == -1);
        int lp, rp;
        tie(lp, rp) = getmp(x, y);
        if (x < y) {
            mp.erase(((ull)(x)<<32) | y);
        } else {
            mp.erase(((ull)(y)<<32) | x);
        }
        up[x] = lp/2;
        NP lx = pool+lp, rx = pool+rp;
        // L M R
        NP L, M, R;
        rx->splay();
        tie(M, R) = split(rx, rx->l->sz+1);
        split(M, M->sz-1);
        lx->splay();
        tie(L, M) = splitl(lx);
        M = split(M, 1).second;
        L = merge(L, R);
        if (tr[y] == lp) {
            if (!L->sz) tr[y] = -1;
            else {
                tr[y] = at(L, 0) - pool;
            }
        }
        if (tr[x] == rp) {
            if (!M->sz) tr[x] = -1;
            else {
                tr[x] = at(M, 0) - pool;
            }
        }
    }
    int root(int x) {
        if (up[x] != -1) return x;
        NP xt = tree(x);
        int res = at(xt, 0)->idl;
        return res;
    }
};
template<int N>
typename ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();
template<int N>
typename ETTree<N>::NP ETTree<N>::last = &last_d;