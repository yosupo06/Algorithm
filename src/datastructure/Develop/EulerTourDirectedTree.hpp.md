---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/EulerTourDirectedTree.hpp\"\n\
    /**\n * \u68EE\u306B\u5BFE\u3059\u308B\u30AF\u30A8\u30EA\u3092\u51E6\u7406\u3059\
    \u308B\u52D5\u7684\u6728 \u90E8\u5206\u6728\u30AF\u30A8\u30EA\u306B\u5BFE\u3057\
    \u3066\u5F37\u3044\n *\n * \u73FE\u6642\u70B9\u3067\u306Fevert\u7121\u3057\u306E\
    \u307F\n */\nstruct ETDTree {\n    struct Node;\n    typedef Node* NP;\n    static\
    \ Node last_d;\n    static NP last;\n    struct Node {\n        NP p, l, r;\n\
    \        int sz, id, dps, dps_lz;\n        pair<int, int> lca;\n        Node(int\
    \ id) :p(nullptr), l(last), r(last), sz(1), id(id),\n                      dps(0),\
    \ dps_lz(0), lca(P(0, id)) {}\n        Node(NP n) : p(nullptr), l(last), r(last),\
    \ sz(1), id(n->id),\n                      dps(n->dps), dps_lz(0), lca(P(dps,\
    \ id)) {}\n        Node() : l(nullptr), r(nullptr), sz(0), id(-1) {}\n\n     \
    \   //push\u3092\u3059\u308B\u3068\u3001push\u3092\u3057\u305F\u9802\u70B9\u3068\
    \u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\u6B63\u5F53\u6027\
    \u304C\u4FDD\u8A3C\u3055\u308C\u308B\n        void push() { \n            if (dps_lz)\
    \ {\n                if (l != last) {\n                    l->dpslzdata(dps_lz);\n\
    \                }\n                if (r != last) {\n                    r->dpslzdata(dps_lz);\n\
    \                }\n                dps_lz = 0;\n            }\n            assert(sz);\n\
    \        }\n        NP update() {\n            assert(this != last);\n       \
    \     sz = 1+l->sz+r->sz;\n            lca = P(dps, id);\n            if (l !=\
    \ last) {\n                lca = min(lca, l->lca);\n            }\n          \
    \  if (r != last) {\n                lca = min(lca, r->lca);\n            }\n\
    \            return this;\n        }\n        void dpslzdata(int x) {\n      \
    \      dps += x;\n            dps_lz += x;\n            lca.first += x;\n    \
    \    }\n\n        inline int pos() {\n            if (p) {\n                if\
    \ (p->l == this) return -1;\n                if (p->r == this) return 1;\n   \
    \         }\n            return 0;\n        }\n        void rot() {\n        \
    \    NP qq = p->p;\n            int pps = p->pos();\n            if (p->l == this)\
    \ {\n                p->l = r; r->p = p;\n                r = p; p->p = this;\n\
    \            } else {\n                p->r = l; l->p = p;\n                l\
    \ = p; p->p = this;\n            }\n            p->update(); update();\n     \
    \       p = qq;\n            if (!pps) return;\n            if (pps == -1) {\n\
    \                qq->l = this;\n            } else {\n                qq->r =\
    \ this;\n            }\n            qq->update();\n        }\n        NP splay()\
    \ {\n            assert(this != last);\n            supush();\n            int\
    \ ps;\n            while ((ps = pos())) {\n                int pps = p->pos();\n\
    \                if (!pps) {\n                    rot();\n                } else\
    \ if (ps == pps) {\n                    p->rot(); rot();\n                } else\
    \ {\n                    rot(); rot();\n                }\n            }\n   \
    \         return this;\n        }\n        void supush() {\n            if (pos())\
    \ {\n                p->supush();\n            }\n            push();\n      \
    \  }\n        void debug() {\n            if (this == last) return;\n        \
    \    push();\n            l->debug();\n            printf(\"(%d-%d %llx) \", id,\
    \ dps, (unsigned long long)this & 0xffff);\n            r->debug();\n        }\n\
    \    };\n    int N;\n    typedef pair<int, int> P;\n    vector<int> parent;\n\
    \    vector<Node> pool;\n    ETDTree(int N) : N(N) {\n        parent = vector<int>(N,\
    \ N);\n        pool = vector<Node>(2*N);\n        for (int i = 0; i < N; i++)\
    \ {\n            pool[i*2] = Node(i);\n            pool[i*2+1] = Node(N);\n  \
    \          NP x = &pool[i*2];\n            NP y = &pool[i*2+1];\n            merge(x,\
    \ y);\n        }\n    }\n    void debug(int d) {\n        tree(d)->debug();\n\
    \        assert(tree(d)->id == d);\n        printf(\"\\n\");\n    }\n\n    NP\
    \ tree(int d) {\n        assert(0 <= d && d < N);\n        return (&pool[d*2])->splay();\n\
    \    }\n    NP merge(NP l, NP r) {\n        if (l == last) return r;\n       \
    \ if (r == last) return l;\n        r = at(r, 0);\n        r->l = l;\n       \
    \ l->p = r;\n        return r->update();\n    }\n    pair<NP, NP> split(NP n,\
    \ int k) {\n        if (!k) return {last, n};\n        if (n->sz == k) return\
    \ {n, last};\n        n = at(n, k);\n        NP m = n->l;\n        m->p = nullptr;\n\
    \        n->l = last;\n        n->update();\n        return {m, n};\n    }\n \
    \   NP at(NP n, int k) {\n        assert(n != last);\n        n->push();\n   \
    \     if (k < n->l->sz) {\n            return at(n->l, k);\n        } else if\
    \ (k == n->l->sz) {\n            n->splay();\n            return n;\n        }\
    \ else {\n            return at(n->r, k-(n->l->sz+1));\n        }\n    }\n\n \
    \   //y\u306E\u5B50\u3068\u3057\u3066x\u3092\u8FFD\u52A0\n    void link(int x,\
    \ int y) {\n        assert(parent[x] == N);\n        NP n, m, u;\n        n =\
    \ tree(y);\n        NP nn = &pool[x*2+1];\n        nn->splay();\n        assert(nn\
    \ != nullptr);\n        nn = split(nn, nn->sz-1).second;\n        *nn = Node(n);\n\
    \        tie(m, n) = split(n, n->l->sz+1);\n        u = &pool[x*2];\n        u->splay();\n\
    \        u->dpslzdata(nn->dps+1);\n        parent[x] = y;\n        merge(merge(merge(m,\
    \ u), nn), n);\n    }\n    //root(x) == y\n    void cut(int x) {\n        assert(parent[x]\
    \ != N);\n        parent[x] = N;\n        NP r, s1;\n        r = (&pool[x*2])->splay();\n\
    \        tie(s1, r) = split(r, r->l->sz);\n        NP s2 = (&pool[x*2+1])->splay();\n\
    \        s2 = split(s2, s2->l->sz+1).second;\n        merge(s1, s2);\n       \
    \ r->splay();\n        r->dpslzdata(-r->dps);\n    }\n\n\n    int lca(int x, int\
    \ y) {\n        NP a = tree(x);\n        int ac = a->l->sz;\n        NP b = tree(y);\n\
    \        int bc = b->l->sz;\n        if (a->p == nullptr) return -1;\n       \
    \ if (ac > bc) {\n            swap(ac, bc);\n            swap(a, b);\n       \
    \ }\n        b->splay();\n        auto s = split(b, bc+1);\n        auto t = split(s.first,\
    \ ac);\n        int res = t.second->lca.second;\n        merge(merge(t.first,\
    \ t.second), s.second);\n        return res;\n    }\n    int root(int x) {\n \
    \       return at(tree(x), 0)->id;\n    }\n    bool same(int x, int y) {\n   \
    \     return root(x) == root(y);\n    }\n};\nETDTree::Node ETDTree::last_d = ETDTree::Node();\n\
    ETDTree::NP ETDTree::last = &last_d;\n\n\n\ntemplate<int N>\nstruct ETTree {\n\
    \    struct Node;\n    typedef Node* NP;\n    static Node last_d;\n    static\
    \ NP last;\n    struct Node {\n        NP p, l, r;\n        int sz, idl, idr;\n\
    \        pair<int, int> lca;\n        Node(int idl, int idr) :p(nullptr), l(last),\
    \ r(last), sz(1), idl(idl), idr(idr) {}\n        Node() : l(nullptr), r(nullptr),\
    \ sz(0) {}\n\n        //push\u3092\u3059\u308B\u3068\u3001push\u3092\u3057\u305F\
    \u9802\u70B9\u3068\u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\
    \u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\u3055\u308C\u308B\n        void push() {\
    \ \n            assert(sz);\n        }\n        NP update() {\n            assert(this\
    \ != last);\n            sz = 1+l->sz+r->sz;\n            return this;\n     \
    \   }\n\n        inline int pos() {\n            if (p) {\n                if\
    \ (p->l == this) return -1;\n                if (p->r == this) return 1;\n   \
    \         }\n            return 0;\n        }\n        void rot() {\n        \
    \    NP qq = p->p;\n            int pps = p->pos();\n            if (p->l == this)\
    \ {\n                p->l = r; r->p = p;\n                r = p; p->p = this;\n\
    \            } else {\n                p->r = l; l->p = p;\n                l\
    \ = p; p->p = this;\n            }\n            p->update(); update();\n     \
    \       p = qq;\n            if (!pps) return;\n            if (pps == -1) {\n\
    \                qq->l = this;\n            } else {\n                qq->r =\
    \ this;\n            }\n            qq->update();\n        }\n        NP splay()\
    \ {\n            assert(this != last);\n            supush();\n            int\
    \ ps;\n            while ((ps = pos())) {\n                int pps = p->pos();\n\
    \                if (!pps) {\n                    rot();\n                } else\
    \ if (ps == pps) {\n                    p->rot(); rot();\n                } else\
    \ {\n                    rot(); rot();\n                }\n            }\n   \
    \         return this;\n        }\n        void supush() {\n            if (pos())\
    \ {\n                p->supush();\n            }\n            push();\n      \
    \  }\n        void debug() {\n            if (this == last) return;\n        \
    \    push();\n            l->debug();\n            printf(\"(%d-%d) \", idl, idr);\n\
    \            r->debug();\n        }\n    };\n    typedef pair<int, int> P;\n \
    \   map<int, int> mp[N+1];\n    Node pool[2*N];\n    ETTree() {\n        for (int\
    \ i = 0; i < N; i++) {\n            pool[2*i] = Node(N, i);\n            pool[2*i+1]\
    \ = Node(i, N);\n            merge(pool+2*i, pool+2*i+1);\n            mp[N][i]\
    \ = 2*i;\n            mp[i][N] = 2*i+1;\n        }\n    }\n    void debug(int\
    \ d) {\n        tree(d)->debug();\n    }\n\n    NP tree(int d) {\n        assert(0\
    \ <= d && d < N);\n        return (&pool[mp[d].begin()->second])->splay();\n \
    \   }\n    NP merge(NP l, NP r) {\n        if (l == last) return r;\n        if\
    \ (r == last) return l;\n        r = at(r, 0);\n        r->l = l;\n        l->p\
    \ = r;\n        return r->update();\n    }\n    pair<NP, NP> split(NP n, int k)\
    \ {\n        if (!k) return {last, n};\n        if (n->sz == k) return {n, last};\n\
    \        n = at(n, k);\n        NP m = n->l;\n        m->p = nullptr;\n      \
    \  n->l = last;\n        n->update();\n        return {m, n};\n    }\n    NP at(NP\
    \ n, int k) {\n        assert(n != last);\n        n->push();\n        if (k <\
    \ n->l->sz) {\n            return at(n->l, k);\n        } else if (k == n->l->sz)\
    \ {\n            n->splay();\n            return n;\n        } else {\n      \
    \      return at(n->r, k-(n->l->sz+1));\n        }\n    }\n\n    //y\u306E\u5B50\
    \u3068\u3057\u3066x\u3092\u8FFD\u52A0\n    void evert(int x) {\n        int rt\
    \ = root(x);\n        NP xt = tree(x);\n        auto sp = split(xt, xt->l->sz);\n\
    \        NP L, ML, MR, R;\n        tie(L, ML) = split(sp.first, 1);\n        tie(MR,\
    \ R) = split(sp.second, sp.second->sz-1);\n        assert(L->idl == N && L->idr\
    \ == rt && R->idl == rt && R->idr == N);\n        int lp = mp[N][rt], rp = mp[rt][N];\n\
    \        pool[lp].idr = x; pool[rp].idl = x;\n        mp[N].erase(rt); mp[rt].erase(N);\n\
    \        mp[N][x] = lp; mp[x][N] = rp;\n        merge(merge(merge(L, MR), ML),\
    \ R);\n    }\n    void link(int x, int y) {\n        assert(mp[x].count(N));\n\
    \        NP xt = tree(x);\n        NP yt = tree(y);\n        //yt\u306E\u524D\u306B\
    tree(x)\u3092\u5165\u308C\u305F\u3044\n        int lp = mp[N][x], rp = mp[x][N];\n\
    \        pool[lp].idl = y; pool[rp].idr = y;\n        mp[N].erase(x); mp[x].erase(N);\n\
    \        mp[y][x] = lp; mp[x][y] = rp;\n        auto sp = split(yt, yt->l->sz);\n\
    \        merge(merge(sp.first, xt), sp.second);\n    }\n    void cut(int x, int\
    \ y) {\n        assert(mp[x].count(y));\n        int lp = mp[y][x], rp = mp[x][y];\n\
    \        NP lx = pool+lp, rx = pool+rp;\n        pool[lp].idl = N; pool[rp].idr\
    \ = N;\n        mp[y].erase(x); mp[x].erase(y);\n        mp[N][x] = lp; mp[x][N]\
    \ = rp;\n        // L M R\n        NP L, M, R;\n        rx->splay();\n       \
    \ R = split(rx, rx->l->sz+1).second;\n        lx->splay();\n        tie(L, M)\
    \ = split(lx, lx->l->sz);\n        merge(L, R);\n    }\n    int root(int x) {\n\
    \        NP xt = tree(x);\n        return at(xt, 0)->idr;\n    }\n    //debug\u7528\
    \u3000\u3081\u3063\u3061\u3083\u91CD\u3044\u3088\n    void scan() {\n        for\
    \ (int i = 0; i <= N; i++) {\n            for (auto p: mp[i]) {\n            \
    \    assert(pool[p.second].idl == i);\n                assert(pool[p.second].idr\
    \ == p.first);\n            }\n        }\n    }\n};\ntemplate<int N>\ntypename\
    \ ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();\ntemplate<int N>\ntypename\
    \ ETTree<N>::NP ETTree<N>::last = &last_d;\n"
  code: "/**\n * \u68EE\u306B\u5BFE\u3059\u308B\u30AF\u30A8\u30EA\u3092\u51E6\u7406\
    \u3059\u308B\u52D5\u7684\u6728 \u90E8\u5206\u6728\u30AF\u30A8\u30EA\u306B\u5BFE\
    \u3057\u3066\u5F37\u3044\n *\n * \u73FE\u6642\u70B9\u3067\u306Fevert\u7121\u3057\
    \u306E\u307F\n */\nstruct ETDTree {\n    struct Node;\n    typedef Node* NP;\n\
    \    static Node last_d;\n    static NP last;\n    struct Node {\n        NP p,\
    \ l, r;\n        int sz, id, dps, dps_lz;\n        pair<int, int> lca;\n     \
    \   Node(int id) :p(nullptr), l(last), r(last), sz(1), id(id),\n             \
    \         dps(0), dps_lz(0), lca(P(0, id)) {}\n        Node(NP n) : p(nullptr),\
    \ l(last), r(last), sz(1), id(n->id),\n                      dps(n->dps), dps_lz(0),\
    \ lca(P(dps, id)) {}\n        Node() : l(nullptr), r(nullptr), sz(0), id(-1) {}\n\
    \n        //push\u3092\u3059\u308B\u3068\u3001push\u3092\u3057\u305F\u9802\u70B9\
    \u3068\u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\u6B63\u5F53\
    \u6027\u304C\u4FDD\u8A3C\u3055\u308C\u308B\n        void push() { \n         \
    \   if (dps_lz) {\n                if (l != last) {\n                    l->dpslzdata(dps_lz);\n\
    \                }\n                if (r != last) {\n                    r->dpslzdata(dps_lz);\n\
    \                }\n                dps_lz = 0;\n            }\n            assert(sz);\n\
    \        }\n        NP update() {\n            assert(this != last);\n       \
    \     sz = 1+l->sz+r->sz;\n            lca = P(dps, id);\n            if (l !=\
    \ last) {\n                lca = min(lca, l->lca);\n            }\n          \
    \  if (r != last) {\n                lca = min(lca, r->lca);\n            }\n\
    \            return this;\n        }\n        void dpslzdata(int x) {\n      \
    \      dps += x;\n            dps_lz += x;\n            lca.first += x;\n    \
    \    }\n\n        inline int pos() {\n            if (p) {\n                if\
    \ (p->l == this) return -1;\n                if (p->r == this) return 1;\n   \
    \         }\n            return 0;\n        }\n        void rot() {\n        \
    \    NP qq = p->p;\n            int pps = p->pos();\n            if (p->l == this)\
    \ {\n                p->l = r; r->p = p;\n                r = p; p->p = this;\n\
    \            } else {\n                p->r = l; l->p = p;\n                l\
    \ = p; p->p = this;\n            }\n            p->update(); update();\n     \
    \       p = qq;\n            if (!pps) return;\n            if (pps == -1) {\n\
    \                qq->l = this;\n            } else {\n                qq->r =\
    \ this;\n            }\n            qq->update();\n        }\n        NP splay()\
    \ {\n            assert(this != last);\n            supush();\n            int\
    \ ps;\n            while ((ps = pos())) {\n                int pps = p->pos();\n\
    \                if (!pps) {\n                    rot();\n                } else\
    \ if (ps == pps) {\n                    p->rot(); rot();\n                } else\
    \ {\n                    rot(); rot();\n                }\n            }\n   \
    \         return this;\n        }\n        void supush() {\n            if (pos())\
    \ {\n                p->supush();\n            }\n            push();\n      \
    \  }\n        void debug() {\n            if (this == last) return;\n        \
    \    push();\n            l->debug();\n            printf(\"(%d-%d %llx) \", id,\
    \ dps, (unsigned long long)this & 0xffff);\n            r->debug();\n        }\n\
    \    };\n    int N;\n    typedef pair<int, int> P;\n    vector<int> parent;\n\
    \    vector<Node> pool;\n    ETDTree(int N) : N(N) {\n        parent = vector<int>(N,\
    \ N);\n        pool = vector<Node>(2*N);\n        for (int i = 0; i < N; i++)\
    \ {\n            pool[i*2] = Node(i);\n            pool[i*2+1] = Node(N);\n  \
    \          NP x = &pool[i*2];\n            NP y = &pool[i*2+1];\n            merge(x,\
    \ y);\n        }\n    }\n    void debug(int d) {\n        tree(d)->debug();\n\
    \        assert(tree(d)->id == d);\n        printf(\"\\n\");\n    }\n\n    NP\
    \ tree(int d) {\n        assert(0 <= d && d < N);\n        return (&pool[d*2])->splay();\n\
    \    }\n    NP merge(NP l, NP r) {\n        if (l == last) return r;\n       \
    \ if (r == last) return l;\n        r = at(r, 0);\n        r->l = l;\n       \
    \ l->p = r;\n        return r->update();\n    }\n    pair<NP, NP> split(NP n,\
    \ int k) {\n        if (!k) return {last, n};\n        if (n->sz == k) return\
    \ {n, last};\n        n = at(n, k);\n        NP m = n->l;\n        m->p = nullptr;\n\
    \        n->l = last;\n        n->update();\n        return {m, n};\n    }\n \
    \   NP at(NP n, int k) {\n        assert(n != last);\n        n->push();\n   \
    \     if (k < n->l->sz) {\n            return at(n->l, k);\n        } else if\
    \ (k == n->l->sz) {\n            n->splay();\n            return n;\n        }\
    \ else {\n            return at(n->r, k-(n->l->sz+1));\n        }\n    }\n\n \
    \   //y\u306E\u5B50\u3068\u3057\u3066x\u3092\u8FFD\u52A0\n    void link(int x,\
    \ int y) {\n        assert(parent[x] == N);\n        NP n, m, u;\n        n =\
    \ tree(y);\n        NP nn = &pool[x*2+1];\n        nn->splay();\n        assert(nn\
    \ != nullptr);\n        nn = split(nn, nn->sz-1).second;\n        *nn = Node(n);\n\
    \        tie(m, n) = split(n, n->l->sz+1);\n        u = &pool[x*2];\n        u->splay();\n\
    \        u->dpslzdata(nn->dps+1);\n        parent[x] = y;\n        merge(merge(merge(m,\
    \ u), nn), n);\n    }\n    //root(x) == y\n    void cut(int x) {\n        assert(parent[x]\
    \ != N);\n        parent[x] = N;\n        NP r, s1;\n        r = (&pool[x*2])->splay();\n\
    \        tie(s1, r) = split(r, r->l->sz);\n        NP s2 = (&pool[x*2+1])->splay();\n\
    \        s2 = split(s2, s2->l->sz+1).second;\n        merge(s1, s2);\n       \
    \ r->splay();\n        r->dpslzdata(-r->dps);\n    }\n\n\n    int lca(int x, int\
    \ y) {\n        NP a = tree(x);\n        int ac = a->l->sz;\n        NP b = tree(y);\n\
    \        int bc = b->l->sz;\n        if (a->p == nullptr) return -1;\n       \
    \ if (ac > bc) {\n            swap(ac, bc);\n            swap(a, b);\n       \
    \ }\n        b->splay();\n        auto s = split(b, bc+1);\n        auto t = split(s.first,\
    \ ac);\n        int res = t.second->lca.second;\n        merge(merge(t.first,\
    \ t.second), s.second);\n        return res;\n    }\n    int root(int x) {\n \
    \       return at(tree(x), 0)->id;\n    }\n    bool same(int x, int y) {\n   \
    \     return root(x) == root(y);\n    }\n};\nETDTree::Node ETDTree::last_d = ETDTree::Node();\n\
    ETDTree::NP ETDTree::last = &last_d;\n\n\n\ntemplate<int N>\nstruct ETTree {\n\
    \    struct Node;\n    typedef Node* NP;\n    static Node last_d;\n    static\
    \ NP last;\n    struct Node {\n        NP p, l, r;\n        int sz, idl, idr;\n\
    \        pair<int, int> lca;\n        Node(int idl, int idr) :p(nullptr), l(last),\
    \ r(last), sz(1), idl(idl), idr(idr) {}\n        Node() : l(nullptr), r(nullptr),\
    \ sz(0) {}\n\n        //push\u3092\u3059\u308B\u3068\u3001push\u3092\u3057\u305F\
    \u9802\u70B9\u3068\u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\
    \u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\u3055\u308C\u308B\n        void push() {\
    \ \n            assert(sz);\n        }\n        NP update() {\n            assert(this\
    \ != last);\n            sz = 1+l->sz+r->sz;\n            return this;\n     \
    \   }\n\n        inline int pos() {\n            if (p) {\n                if\
    \ (p->l == this) return -1;\n                if (p->r == this) return 1;\n   \
    \         }\n            return 0;\n        }\n        void rot() {\n        \
    \    NP qq = p->p;\n            int pps = p->pos();\n            if (p->l == this)\
    \ {\n                p->l = r; r->p = p;\n                r = p; p->p = this;\n\
    \            } else {\n                p->r = l; l->p = p;\n                l\
    \ = p; p->p = this;\n            }\n            p->update(); update();\n     \
    \       p = qq;\n            if (!pps) return;\n            if (pps == -1) {\n\
    \                qq->l = this;\n            } else {\n                qq->r =\
    \ this;\n            }\n            qq->update();\n        }\n        NP splay()\
    \ {\n            assert(this != last);\n            supush();\n            int\
    \ ps;\n            while ((ps = pos())) {\n                int pps = p->pos();\n\
    \                if (!pps) {\n                    rot();\n                } else\
    \ if (ps == pps) {\n                    p->rot(); rot();\n                } else\
    \ {\n                    rot(); rot();\n                }\n            }\n   \
    \         return this;\n        }\n        void supush() {\n            if (pos())\
    \ {\n                p->supush();\n            }\n            push();\n      \
    \  }\n        void debug() {\n            if (this == last) return;\n        \
    \    push();\n            l->debug();\n            printf(\"(%d-%d) \", idl, idr);\n\
    \            r->debug();\n        }\n    };\n    typedef pair<int, int> P;\n \
    \   map<int, int> mp[N+1];\n    Node pool[2*N];\n    ETTree() {\n        for (int\
    \ i = 0; i < N; i++) {\n            pool[2*i] = Node(N, i);\n            pool[2*i+1]\
    \ = Node(i, N);\n            merge(pool+2*i, pool+2*i+1);\n            mp[N][i]\
    \ = 2*i;\n            mp[i][N] = 2*i+1;\n        }\n    }\n    void debug(int\
    \ d) {\n        tree(d)->debug();\n    }\n\n    NP tree(int d) {\n        assert(0\
    \ <= d && d < N);\n        return (&pool[mp[d].begin()->second])->splay();\n \
    \   }\n    NP merge(NP l, NP r) {\n        if (l == last) return r;\n        if\
    \ (r == last) return l;\n        r = at(r, 0);\n        r->l = l;\n        l->p\
    \ = r;\n        return r->update();\n    }\n    pair<NP, NP> split(NP n, int k)\
    \ {\n        if (!k) return {last, n};\n        if (n->sz == k) return {n, last};\n\
    \        n = at(n, k);\n        NP m = n->l;\n        m->p = nullptr;\n      \
    \  n->l = last;\n        n->update();\n        return {m, n};\n    }\n    NP at(NP\
    \ n, int k) {\n        assert(n != last);\n        n->push();\n        if (k <\
    \ n->l->sz) {\n            return at(n->l, k);\n        } else if (k == n->l->sz)\
    \ {\n            n->splay();\n            return n;\n        } else {\n      \
    \      return at(n->r, k-(n->l->sz+1));\n        }\n    }\n\n    //y\u306E\u5B50\
    \u3068\u3057\u3066x\u3092\u8FFD\u52A0\n    void evert(int x) {\n        int rt\
    \ = root(x);\n        NP xt = tree(x);\n        auto sp = split(xt, xt->l->sz);\n\
    \        NP L, ML, MR, R;\n        tie(L, ML) = split(sp.first, 1);\n        tie(MR,\
    \ R) = split(sp.second, sp.second->sz-1);\n        assert(L->idl == N && L->idr\
    \ == rt && R->idl == rt && R->idr == N);\n        int lp = mp[N][rt], rp = mp[rt][N];\n\
    \        pool[lp].idr = x; pool[rp].idl = x;\n        mp[N].erase(rt); mp[rt].erase(N);\n\
    \        mp[N][x] = lp; mp[x][N] = rp;\n        merge(merge(merge(L, MR), ML),\
    \ R);\n    }\n    void link(int x, int y) {\n        assert(mp[x].count(N));\n\
    \        NP xt = tree(x);\n        NP yt = tree(y);\n        //yt\u306E\u524D\u306B\
    tree(x)\u3092\u5165\u308C\u305F\u3044\n        int lp = mp[N][x], rp = mp[x][N];\n\
    \        pool[lp].idl = y; pool[rp].idr = y;\n        mp[N].erase(x); mp[x].erase(N);\n\
    \        mp[y][x] = lp; mp[x][y] = rp;\n        auto sp = split(yt, yt->l->sz);\n\
    \        merge(merge(sp.first, xt), sp.second);\n    }\n    void cut(int x, int\
    \ y) {\n        assert(mp[x].count(y));\n        int lp = mp[y][x], rp = mp[x][y];\n\
    \        NP lx = pool+lp, rx = pool+rp;\n        pool[lp].idl = N; pool[rp].idr\
    \ = N;\n        mp[y].erase(x); mp[x].erase(y);\n        mp[N][x] = lp; mp[x][N]\
    \ = rp;\n        // L M R\n        NP L, M, R;\n        rx->splay();\n       \
    \ R = split(rx, rx->l->sz+1).second;\n        lx->splay();\n        tie(L, M)\
    \ = split(lx, lx->l->sz);\n        merge(L, R);\n    }\n    int root(int x) {\n\
    \        NP xt = tree(x);\n        return at(xt, 0)->idr;\n    }\n    //debug\u7528\
    \u3000\u3081\u3063\u3061\u3083\u91CD\u3044\u3088\n    void scan() {\n        for\
    \ (int i = 0; i <= N; i++) {\n            for (auto p: mp[i]) {\n            \
    \    assert(pool[p.second].idl == i);\n                assert(pool[p.second].idr\
    \ == p.first);\n            }\n        }\n    }\n};\ntemplate<int N>\ntypename\
    \ ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();\ntemplate<int N>\ntypename\
    \ ETTree<N>::NP ETTree<N>::last = &last_d;"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/EulerTourDirectedTree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/EulerTourDirectedTree.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/EulerTourDirectedTree.hpp
- /library/src/datastructure/Develop/EulerTourDirectedTree.hpp.html
title: src/datastructure/Develop/EulerTourDirectedTree.hpp
---
