---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/DynamicConnectivity.hpp\"\n/**\n\
    \ * \u3068\u308A\u3042\u3048\u305A\u6B63\u3057\u3044\u7B54\u3048\u306F\u8FD4\u3057\
    \u305D\u3046\n * \u73FE\u6642\u70B9\u3067\u306F\u4F7F\u3044\u7269\u306B\u306A\u3089\
    \u306A\u3044\u3057\u7D76\u5BFE\u5B9A\u6570\u500D\u6539\u5584\u3057\u3088\u3046\
    \u306A\n */\ntemplate<int N>\nstruct ETTree {\n    struct Node;\n    typedef Node*\
    \ NP;\n    static Node last_d;\n    static NP last;\n    struct Node {\n     \
    \   NP p, l, r;\n        int sz, idl, idr;\n        Node(int idl, int idr) :p(nullptr),\
    \ l(last), r(last), sz(1), idl(idl), idr(idr) {}\n        Node() : l(nullptr),\
    \ r(nullptr), sz(0) {}\n\n        //push\u3092\u3059\u308B\u3068\u3001push\u3092\
    \u3057\u305F\u9802\u70B9\u3068\u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\
    \u5024\u306E\u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\u3055\u308C\u308B\n        void\
    \ push() { \n            assert(sz);\n        }\n        NP update() {\n     \
    \       assert(this != last);\n            sz = 1+l->sz+r->sz;\n            return\
    \ this;\n        }\n\n        inline int pos() {\n            if (p) {\n     \
    \           if (p->l == this) return -1;\n                if (p->r == this) return\
    \ 1;\n            }\n            return 0;\n        }\n        void rot() {\n\
    \            NP qq = p->p;\n            int pps = p->pos();\n            if (p->l\
    \ == this) {\n                p->l = r; r->p = p;\n                r = p; p->p\
    \ = this;\n            } else {\n                p->r = l; l->p = p;\n       \
    \         l = p; p->p = this;\n            }\n            p->update(); update();\n\
    \            p = qq;\n            if (!pps) return;\n            if (pps == -1)\
    \ {\n                qq->l = this;\n            } else {\n                qq->r\
    \ = this;\n            }\n            qq->update();\n        }\n        NP splay()\
    \ {\n            assert(this != last);\n            supush();\n            int\
    \ ps;\n            while ((ps = pos())) {\n                int pps = p->pos();\n\
    \                if (!pps) {\n                    rot();\n                } else\
    \ if (ps == pps) {\n                    p->rot(); rot();\n                } else\
    \ {\n                    rot(); rot();\n                }\n            }\n   \
    \         return this;\n        }\n        void supush() {\n            if (pos())\
    \ {\n                p->supush();\n            }\n            push();\n      \
    \  }\n        void getall(vector<int> &v) {\n            if (this == last) return;\n\
    \            l->getall(v);\n            v.push_back(idl);\n            v.push_back(idr);\n\
    \            r->getall(v);\n        }\n        void debug() {\n            if\
    \ (this == last) return;\n            push();\n            l->debug();\n     \
    \       printf(\"(%d-%d) \", idl, idr);\n            r->debug();\n        }\n\
    \    };\n    typedef pair<int, int> P;\n    map<int, int> mp[N+1];\n    Node pool[2*N];\n\
    \    ETTree() {\n        for (int i = 0; i < N; i++) {\n            pool[2*i]\
    \ = Node(N, i);\n            pool[2*i+1] = Node(i, N);\n            merge(pool+2*i,\
    \ pool+2*i+1);\n            mp[N][i] = 2*i;\n            mp[i][N] = 2*i+1;\n \
    \       }\n    }\n    void debug(int d) {\n        tree(d)->debug();\n    }\n\n\
    \    NP tree(int d) {\n        assert(0 <= d && d < N);\n        return (&pool[mp[d].begin()->second])->splay();\n\
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
    \   //y\u306E\u5B50\u3068\u3057\u3066x\u3092\u8FFD\u52A0\n    void evert(int x)\
    \ {\n        int rt = root(x);\n        NP xt = tree(x);\n        auto sp = split(xt,\
    \ xt->l->sz);\n        NP L, ML, MR, R;\n        tie(L, ML) = split(sp.first,\
    \ 1);\n        tie(MR, R) = split(sp.second, sp.second->sz-1);\n        assert(L->idl\
    \ == N && L->idr == rt && R->idl == rt && R->idr == N);\n        int lp = mp[N][rt],\
    \ rp = mp[rt][N];\n        pool[lp].idr = x; pool[rp].idl = x;\n        mp[N].erase(rt);\
    \ mp[rt].erase(N);\n        mp[N][x] = lp; mp[x][N] = rp;\n        merge(merge(merge(L,\
    \ MR), ML), R);\n    }\n    void link(int x, int y) {\n        assert(mp[x].count(N));\n\
    \        NP xt = tree(x);\n        NP yt = tree(y);\n        //yt\u306E\u524D\u306B\
    tree(x)\u3092\u5165\u308C\u305F\u3044\n        int lp = mp[N][x], rp = mp[x][N];\n\
    \        pool[lp].idl = y; pool[rp].idr = y;\n        mp[N].erase(x); mp[x].erase(N);\n\
    \        mp[y][x] = lp; mp[x][y] = rp;\n        auto sp = split(yt, yt->l->sz);\n\
    \        merge(merge(sp.first, xt), sp.second);\n    }\n    void cut(int x, int\
    \ y) {\n        assert(mp[x].count(y));\n        assert(mp[y].count(x));\n   \
    \     int lp = mp[y][x], rp = mp[x][y];\n        NP lx = pool+lp, rx = pool+rp;\n\
    \        pool[lp].idl = N; pool[rp].idr = N;\n        mp[y].erase(x); mp[x].erase(y);\n\
    \        mp[N][x] = lp; mp[x][N] = rp;\n        // L M R\n        NP L, M, R;\n\
    \        rx->splay();\n        R = split(rx, rx->l->sz+1).second;\n        lx->splay();\n\
    \        tie(L, M) = split(lx, lx->l->sz);\n        merge(L, R);\n    }\n    int\
    \ root(int x) {\n        NP xt = tree(x);\n        return at(xt, 0)->idr;\n  \
    \  }\n    int sz(int x) {\n        return tree(x)->sz / 2 - 1;\n    }\n    vector<int>\
    \ getall(int x) {\n        vector<int> v;\n        tree(x).getall(v);\n      \
    \  sort(v.begin(), v.end());\n        v.erase(unique(v.begin(), v.end()), v.end());\n\
    \        return v;\n    }\n    //debug\u7528\u3000\u3081\u3063\u3061\u3083\u91CD\
    \u3044\u3088\n    void scan() {\n        for (int i = 0; i <= N; i++) {\n    \
    \        for (auto p: mp[i]) {\n                assert(0 <= p.second && p.second\
    \ < 2*N);\n                assert(pool[p.second].idl == i);\n                assert(pool[p.second].idr\
    \ == p.first);\n            }\n        }\n    }\n};\ntemplate<int N>\ntypename\
    \ ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();\ntemplate<int N>\ntypename\
    \ ETTree<N>::NP ETTree<N>::last = &last_d;\n\ntemplate<int N>\nstruct DynamicConnectivity\
    \ {\n    const static int LGN = 20;\n    typedef pair<int, int> P;\n    ETTree<N>\
    \ ett[LGN+1];\n    set<P> f;\n    map<P, int> level;\n    set<int> g[LGN+1][N];\n\
    \    void add(int x, int y) {\n        if (x > y) swap(x, y);\n        assert(level.count(P(x,\
    \ y)) == 0);\n        level[P(x, y)] = LGN;\n        g[LGN][x].insert(y);\n  \
    \      g[LGN][y].insert(x);\n        if (!same(x, y)) {\n            ett[LGN].evert(x);\n\
    \            ett[LGN].link(x, y);\n            f.insert(P(x, y));\n        }\n\
    \    }\n    void del(int x, int y) {\n        if (x > y) swap(x, y);\n       \
    \ assert(level.count(P(x, y)));\n        int l = level[P(x, y)];\n        level.erase(P(x,\
    \ y));\n        g[l][x].erase(y);\n        g[l][y].erase(x);\n        if (!f.count(P(x,\
    \ y))) {\n            level.erase(P(x, y));\n            return;\n        }\n\
    \        ett[l].evert(y);\n        ett[l].cut(x, y);\n        for (int i = l;\
    \ i <= LGN; i++) {\n            int u = x, v = y;\n            if (ett[i].sz(u)\
    \ > ett[i].sz(v)) swap(u, v);\n            int us = ett[i].sz(u);\n          \
    \  auto ut = ett[i].tree(u);\n            for (int j = 0; j < us*2+1; j++) {\n\
    \                ut->splay();\n                ut = ett[i].at(ut, j);\n      \
    \          int p = ut->idr;\n                int r = -1;\n                auto\
    \ it = g[i][p].begin();\n                for (; it != g[i][p].end(); it++) {\n\
    \                    int w = *it;\n                    int ww = w, pp = p;\n \
    \                   if (ww > pp) swap(ww, pp);\n                    if (ett[i].root(w)\
    \ == v) {\n                        r = w;\n                        f.insert(P(ww,\
    \ pp));\n                        ett[l].evert(ww);\n                        ett[l].link(ww,\
    \ pp);\n                        break;\n                    } else {\n       \
    \                 level[P(ww, pp)]--;\n                        g[i-1][p].insert(w);\n\
    \                        g[i-1][w].insert(p);\n                        g[i][w].erase(p);\n\
    \                    }\n                }\n                g[i][p].erase(g[i][p].begin(),\
    \ it);\n            }\n        }\n    }\n    bool same(int x, int y) {\n     \
    \   return ett[LGN].root(x) == ett[LGN].root(y);\n    }\n    void scan() {\n \
    \       for (int i = 0; i <= LGN; i++) {\n            ett[i].scan();\n       \
    \ }\n    }\n};\n"
  code: "/**\n * \u3068\u308A\u3042\u3048\u305A\u6B63\u3057\u3044\u7B54\u3048\u306F\
    \u8FD4\u3057\u305D\u3046\n * \u73FE\u6642\u70B9\u3067\u306F\u4F7F\u3044\u7269\u306B\
    \u306A\u3089\u306A\u3044\u3057\u7D76\u5BFE\u5B9A\u6570\u500D\u6539\u5584\u3057\
    \u3088\u3046\u306A\n */\ntemplate<int N>\nstruct ETTree {\n    struct Node;\n\
    \    typedef Node* NP;\n    static Node last_d;\n    static NP last;\n    struct\
    \ Node {\n        NP p, l, r;\n        int sz, idl, idr;\n        Node(int idl,\
    \ int idr) :p(nullptr), l(last), r(last), sz(1), idl(idl), idr(idr) {}\n     \
    \   Node() : l(nullptr), r(nullptr), sz(0) {}\n\n        //push\u3092\u3059\u308B\
    \u3068\u3001push\u3092\u3057\u305F\u9802\u70B9\u3068\u305D\u306E\u5B50\u306E\"\
    \u3059\u3079\u3066\"\u306E\u5024\u306E\u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\u3055\
    \u308C\u308B\n        void push() { \n            assert(sz);\n        }\n   \
    \     NP update() {\n            assert(this != last);\n            sz = 1+l->sz+r->sz;\n\
    \            return this;\n        }\n\n        inline int pos() {\n         \
    \   if (p) {\n                if (p->l == this) return -1;\n                if\
    \ (p->r == this) return 1;\n            }\n            return 0;\n        }\n\
    \        void rot() {\n            NP qq = p->p;\n            int pps = p->pos();\n\
    \            if (p->l == this) {\n                p->l = r; r->p = p;\n      \
    \          r = p; p->p = this;\n            } else {\n                p->r = l;\
    \ l->p = p;\n                l = p; p->p = this;\n            }\n            p->update();\
    \ update();\n            p = qq;\n            if (!pps) return;\n            if\
    \ (pps == -1) {\n                qq->l = this;\n            } else {\n       \
    \         qq->r = this;\n            }\n            qq->update();\n        }\n\
    \        NP splay() {\n            assert(this != last);\n            supush();\n\
    \            int ps;\n            while ((ps = pos())) {\n                int\
    \ pps = p->pos();\n                if (!pps) {\n                    rot();\n \
    \               } else if (ps == pps) {\n                    p->rot(); rot();\n\
    \                } else {\n                    rot(); rot();\n               \
    \ }\n            }\n            return this;\n        }\n        void supush()\
    \ {\n            if (pos()) {\n                p->supush();\n            }\n \
    \           push();\n        }\n        void getall(vector<int> &v) {\n      \
    \      if (this == last) return;\n            l->getall(v);\n            v.push_back(idl);\n\
    \            v.push_back(idr);\n            r->getall(v);\n        }\n       \
    \ void debug() {\n            if (this == last) return;\n            push();\n\
    \            l->debug();\n            printf(\"(%d-%d) \", idl, idr);\n      \
    \      r->debug();\n        }\n    };\n    typedef pair<int, int> P;\n    map<int,\
    \ int> mp[N+1];\n    Node pool[2*N];\n    ETTree() {\n        for (int i = 0;\
    \ i < N; i++) {\n            pool[2*i] = Node(N, i);\n            pool[2*i+1]\
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
    \ y) {\n        assert(mp[x].count(y));\n        assert(mp[y].count(x));\n   \
    \     int lp = mp[y][x], rp = mp[x][y];\n        NP lx = pool+lp, rx = pool+rp;\n\
    \        pool[lp].idl = N; pool[rp].idr = N;\n        mp[y].erase(x); mp[x].erase(y);\n\
    \        mp[N][x] = lp; mp[x][N] = rp;\n        // L M R\n        NP L, M, R;\n\
    \        rx->splay();\n        R = split(rx, rx->l->sz+1).second;\n        lx->splay();\n\
    \        tie(L, M) = split(lx, lx->l->sz);\n        merge(L, R);\n    }\n    int\
    \ root(int x) {\n        NP xt = tree(x);\n        return at(xt, 0)->idr;\n  \
    \  }\n    int sz(int x) {\n        return tree(x)->sz / 2 - 1;\n    }\n    vector<int>\
    \ getall(int x) {\n        vector<int> v;\n        tree(x).getall(v);\n      \
    \  sort(v.begin(), v.end());\n        v.erase(unique(v.begin(), v.end()), v.end());\n\
    \        return v;\n    }\n    //debug\u7528\u3000\u3081\u3063\u3061\u3083\u91CD\
    \u3044\u3088\n    void scan() {\n        for (int i = 0; i <= N; i++) {\n    \
    \        for (auto p: mp[i]) {\n                assert(0 <= p.second && p.second\
    \ < 2*N);\n                assert(pool[p.second].idl == i);\n                assert(pool[p.second].idr\
    \ == p.first);\n            }\n        }\n    }\n};\ntemplate<int N>\ntypename\
    \ ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();\ntemplate<int N>\ntypename\
    \ ETTree<N>::NP ETTree<N>::last = &last_d;\n\ntemplate<int N>\nstruct DynamicConnectivity\
    \ {\n    const static int LGN = 20;\n    typedef pair<int, int> P;\n    ETTree<N>\
    \ ett[LGN+1];\n    set<P> f;\n    map<P, int> level;\n    set<int> g[LGN+1][N];\n\
    \    void add(int x, int y) {\n        if (x > y) swap(x, y);\n        assert(level.count(P(x,\
    \ y)) == 0);\n        level[P(x, y)] = LGN;\n        g[LGN][x].insert(y);\n  \
    \      g[LGN][y].insert(x);\n        if (!same(x, y)) {\n            ett[LGN].evert(x);\n\
    \            ett[LGN].link(x, y);\n            f.insert(P(x, y));\n        }\n\
    \    }\n    void del(int x, int y) {\n        if (x > y) swap(x, y);\n       \
    \ assert(level.count(P(x, y)));\n        int l = level[P(x, y)];\n        level.erase(P(x,\
    \ y));\n        g[l][x].erase(y);\n        g[l][y].erase(x);\n        if (!f.count(P(x,\
    \ y))) {\n            level.erase(P(x, y));\n            return;\n        }\n\
    \        ett[l].evert(y);\n        ett[l].cut(x, y);\n        for (int i = l;\
    \ i <= LGN; i++) {\n            int u = x, v = y;\n            if (ett[i].sz(u)\
    \ > ett[i].sz(v)) swap(u, v);\n            int us = ett[i].sz(u);\n          \
    \  auto ut = ett[i].tree(u);\n            for (int j = 0; j < us*2+1; j++) {\n\
    \                ut->splay();\n                ut = ett[i].at(ut, j);\n      \
    \          int p = ut->idr;\n                int r = -1;\n                auto\
    \ it = g[i][p].begin();\n                for (; it != g[i][p].end(); it++) {\n\
    \                    int w = *it;\n                    int ww = w, pp = p;\n \
    \                   if (ww > pp) swap(ww, pp);\n                    if (ett[i].root(w)\
    \ == v) {\n                        r = w;\n                        f.insert(P(ww,\
    \ pp));\n                        ett[l].evert(ww);\n                        ett[l].link(ww,\
    \ pp);\n                        break;\n                    } else {\n       \
    \                 level[P(ww, pp)]--;\n                        g[i-1][p].insert(w);\n\
    \                        g[i-1][w].insert(p);\n                        g[i][w].erase(p);\n\
    \                    }\n                }\n                g[i][p].erase(g[i][p].begin(),\
    \ it);\n            }\n        }\n    }\n    bool same(int x, int y) {\n     \
    \   return ett[LGN].root(x) == ett[LGN].root(y);\n    }\n    void scan() {\n \
    \       for (int i = 0; i <= LGN; i++) {\n            ett[i].scan();\n       \
    \ }\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/DynamicConnectivity.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/DynamicConnectivity.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/DynamicConnectivity.hpp
- /library/src/datastructure/Develop/DynamicConnectivity.hpp.html
title: src/datastructure/Develop/DynamicConnectivity.hpp
---
