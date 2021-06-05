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
  bundledCode: "#line 1 \"src/datastructure/Develop/EulerTourTree.hpp\"\ntemplate<int\
    \ N>\nstruct ETTree {\n    struct Node;\n    typedef Node* NP;\n    static Node\
    \ last_d;\n    static NP last;\n    struct Node {\n        NP p, l, r;\n     \
    \   int sz, idl, idr, idx;\n        Node(int idl, int idr, int idx) :p(nullptr),\
    \ l(last), r(last), sz(1), idl(idl), idr(idr), idx(idx) {\n        }\n       \
    \ Node() : l(nullptr), r(nullptr), sz(0) {}\n\n        //push\u3092\u3059\u308B\
    \u3068\u3001push\u3092\u3057\u305F\u9802\u70B9\u3068\u305D\u306E\u5B50\u306E\"\
    \u3059\u3079\u3066\"\u306E\u5024\u306E\u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\u3055\
    \u308C\u308B\n        void push() { \n            assert(sz);\n        }\n   \
    \     NP update() {\n            assert(this != last);\n            sz = 1+l->sz+r->sz;\n\
    \            return this;\n        }\n        inline int pos() {\n           \
    \ if (p) {\n                if (p->l == this) return -1;\n                if (p->r\
    \ == this) return 1;\n            }\n            return 0;\n        }\n      \
    \  void rot() {\n            NP qq = p->p;\n            int pps = p->pos();\n\
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
    \           push();\n        }\n    };\n\n    int up[N];\n    int tr[N];\n   \
    \ unordered_map<ull, int> mp;\n    Node pool[2*N];\n    ETTree() {\n        for\
    \ (int i = 0; i < N; i++) {\n            up[i] = i;\n            tr[i] = -1;\n\
    \        }\n    }\n\n    NP tree(int d) {\n        assert(0 <= d && d < N);\n\
    \        if (tr[d] == -1) return last;\n        return pool[tr[d]].splay();\n\
    \    }\n    NP merge(NP l, NP r) {\n        if (l == last) return r;\n       \
    \ if (r == last) return l;\n        r = at(r, 0);\n        r->l = l;\n       \
    \ l->p = r;\n        return r->update();\n    }\n    pair<NP, NP> split(NP n,\
    \ int k) {\n        assert(0 <= k && k <= n->sz);\n        if (!k) return {last,\
    \ n};\n        if (n->sz == k) return {n, last};\n        n = at(n, k);\n    \
    \    NP m = n->l;\n        m->p = nullptr;\n        n->l = last;\n        n->update();\n\
    \        return {m, n};\n    }\n    pair<NP, NP> splitl(NP n) {\n        if (n\
    \ == last) return {last, last};\n        NP m = n->l;\n        m->p = nullptr;\n\
    \        n->l = last;\n        n->update();\n        return {m, n};\n    }\n \
    \   NP at(NP n, int k) {\n        assert(n != last);\n        n->push();\n   \
    \     if (k < n->l->sz) {\n            return at(n->l, k);\n        } else if\
    \ (k == n->l->sz) {\n            n->splay();\n            return n;\n        }\
    \ else {\n            return at(n->r, k-(n->l->sz+1));\n        }\n    }\n   \
    \ pair<int, int> getmp(int x, int y) {\n        int lp, rp;\n        if (x < y)\
    \ {\n            assert(mp.count(((ull)(x)<<32) | y));\n            rp = mp[((ull)(x)<<32)\
    \ | y];\n            lp = rp ^ 1;\n        } else {\n            assert(mp.count(((ull)(y)<<32)\
    \ | x));\n            lp = mp[((ull)(y)<<32) | x];\n            rp = lp ^ 1;\n\
    \        }\n        return {lp, rp};\n    }\n    void evert(int x) {\n       \
    \ if (up[x] != -1) return;\n        int rt = root(x);\n        NP xt = tree(x);\n\
    \        NP L, R;\n        tie(L, R) = splitl(xt);\n        swap(up[rt], up[x]);\n\
    \        merge(R, L);\n    }\n\n    void link(int x, int y, int idx) {\n     \
    \   assert(root(x) != root(y));\n        assert(up[x] != -1);\n        NP xt =\
    \ tree(x);\n        NP yt = tree(y);\n        int lp = up[x]*2, rp = up[x]*2+1;\n\
    \        up[x] = -1;\n        tr[y] = lp; tr[x] = rp;\n        if (x < y) {\n\
    \            mp[((ull)x<<32) | y] = rp;\n        } else {\n            mp[((ull)y<<32)\
    \ | x] = lp;\n        }\n        pool[lp] = Node(y, x, idx);\n        pool[rp]\
    \ = Node(x, y, idx);\n        auto sp = splitl(yt);\n        NP lx = pool+lp,\
    \ rx = pool+rp;\n        merge(merge(merge(merge(sp.first, lx), xt), rx), sp.second);\n\
    \    }\n    void cut(int x, int y) {\n        assert(root(x) == root(y));\n  \
    \      assert(up[x] == -1);\n        int lp, rp;\n        tie(lp, rp) = getmp(x,\
    \ y);\n        if (x < y) {\n            mp.erase(((ull)(x)<<32) | y);\n     \
    \   } else {\n            mp.erase(((ull)(y)<<32) | x);\n        }\n        up[x]\
    \ = lp/2;\n        NP lx = pool+lp, rx = pool+rp;\n        // L M R\n        NP\
    \ L, M, R;\n        rx->splay();\n        tie(M, R) = split(rx, rx->l->sz+1);\n\
    \        split(M, M->sz-1);\n        lx->splay();\n        tie(L, M) = splitl(lx);\n\
    \        M = split(M, 1).second;\n        L = merge(L, R);\n        if (tr[y]\
    \ == lp) {\n            if (!L->sz) tr[y] = -1;\n            else {\n        \
    \        tr[y] = at(L, 0) - pool;\n            }\n        }\n        if (tr[x]\
    \ == rp) {\n            if (!M->sz) tr[x] = -1;\n            else {\n        \
    \        tr[x] = at(M, 0) - pool;\n            }\n        }\n    }\n    int root(int\
    \ x) {\n        if (up[x] != -1) return x;\n        NP xt = tree(x);\n       \
    \ int res = at(xt, 0)->idl;\n        return res;\n    }\n};\ntemplate<int N>\n\
    typename ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();\ntemplate<int N>\n\
    typename ETTree<N>::NP ETTree<N>::last = &last_d;\n"
  code: "template<int N>\nstruct ETTree {\n    struct Node;\n    typedef Node* NP;\n\
    \    static Node last_d;\n    static NP last;\n    struct Node {\n        NP p,\
    \ l, r;\n        int sz, idl, idr, idx;\n        Node(int idl, int idr, int idx)\
    \ :p(nullptr), l(last), r(last), sz(1), idl(idl), idr(idr), idx(idx) {\n     \
    \   }\n        Node() : l(nullptr), r(nullptr), sz(0) {}\n\n        //push\u3092\
    \u3059\u308B\u3068\u3001push\u3092\u3057\u305F\u9802\u70B9\u3068\u305D\u306E\u5B50\
    \u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\
    \u3055\u308C\u308B\n        void push() { \n            assert(sz);\n        }\n\
    \        NP update() {\n            assert(this != last);\n            sz = 1+l->sz+r->sz;\n\
    \            return this;\n        }\n        inline int pos() {\n           \
    \ if (p) {\n                if (p->l == this) return -1;\n                if (p->r\
    \ == this) return 1;\n            }\n            return 0;\n        }\n      \
    \  void rot() {\n            NP qq = p->p;\n            int pps = p->pos();\n\
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
    \           push();\n        }\n    };\n\n    int up[N];\n    int tr[N];\n   \
    \ unordered_map<ull, int> mp;\n    Node pool[2*N];\n    ETTree() {\n        for\
    \ (int i = 0; i < N; i++) {\n            up[i] = i;\n            tr[i] = -1;\n\
    \        }\n    }\n\n    NP tree(int d) {\n        assert(0 <= d && d < N);\n\
    \        if (tr[d] == -1) return last;\n        return pool[tr[d]].splay();\n\
    \    }\n    NP merge(NP l, NP r) {\n        if (l == last) return r;\n       \
    \ if (r == last) return l;\n        r = at(r, 0);\n        r->l = l;\n       \
    \ l->p = r;\n        return r->update();\n    }\n    pair<NP, NP> split(NP n,\
    \ int k) {\n        assert(0 <= k && k <= n->sz);\n        if (!k) return {last,\
    \ n};\n        if (n->sz == k) return {n, last};\n        n = at(n, k);\n    \
    \    NP m = n->l;\n        m->p = nullptr;\n        n->l = last;\n        n->update();\n\
    \        return {m, n};\n    }\n    pair<NP, NP> splitl(NP n) {\n        if (n\
    \ == last) return {last, last};\n        NP m = n->l;\n        m->p = nullptr;\n\
    \        n->l = last;\n        n->update();\n        return {m, n};\n    }\n \
    \   NP at(NP n, int k) {\n        assert(n != last);\n        n->push();\n   \
    \     if (k < n->l->sz) {\n            return at(n->l, k);\n        } else if\
    \ (k == n->l->sz) {\n            n->splay();\n            return n;\n        }\
    \ else {\n            return at(n->r, k-(n->l->sz+1));\n        }\n    }\n   \
    \ pair<int, int> getmp(int x, int y) {\n        int lp, rp;\n        if (x < y)\
    \ {\n            assert(mp.count(((ull)(x)<<32) | y));\n            rp = mp[((ull)(x)<<32)\
    \ | y];\n            lp = rp ^ 1;\n        } else {\n            assert(mp.count(((ull)(y)<<32)\
    \ | x));\n            lp = mp[((ull)(y)<<32) | x];\n            rp = lp ^ 1;\n\
    \        }\n        return {lp, rp};\n    }\n    void evert(int x) {\n       \
    \ if (up[x] != -1) return;\n        int rt = root(x);\n        NP xt = tree(x);\n\
    \        NP L, R;\n        tie(L, R) = splitl(xt);\n        swap(up[rt], up[x]);\n\
    \        merge(R, L);\n    }\n\n    void link(int x, int y, int idx) {\n     \
    \   assert(root(x) != root(y));\n        assert(up[x] != -1);\n        NP xt =\
    \ tree(x);\n        NP yt = tree(y);\n        int lp = up[x]*2, rp = up[x]*2+1;\n\
    \        up[x] = -1;\n        tr[y] = lp; tr[x] = rp;\n        if (x < y) {\n\
    \            mp[((ull)x<<32) | y] = rp;\n        } else {\n            mp[((ull)y<<32)\
    \ | x] = lp;\n        }\n        pool[lp] = Node(y, x, idx);\n        pool[rp]\
    \ = Node(x, y, idx);\n        auto sp = splitl(yt);\n        NP lx = pool+lp,\
    \ rx = pool+rp;\n        merge(merge(merge(merge(sp.first, lx), xt), rx), sp.second);\n\
    \    }\n    void cut(int x, int y) {\n        assert(root(x) == root(y));\n  \
    \      assert(up[x] == -1);\n        int lp, rp;\n        tie(lp, rp) = getmp(x,\
    \ y);\n        if (x < y) {\n            mp.erase(((ull)(x)<<32) | y);\n     \
    \   } else {\n            mp.erase(((ull)(y)<<32) | x);\n        }\n        up[x]\
    \ = lp/2;\n        NP lx = pool+lp, rx = pool+rp;\n        // L M R\n        NP\
    \ L, M, R;\n        rx->splay();\n        tie(M, R) = split(rx, rx->l->sz+1);\n\
    \        split(M, M->sz-1);\n        lx->splay();\n        tie(L, M) = splitl(lx);\n\
    \        M = split(M, 1).second;\n        L = merge(L, R);\n        if (tr[y]\
    \ == lp) {\n            if (!L->sz) tr[y] = -1;\n            else {\n        \
    \        tr[y] = at(L, 0) - pool;\n            }\n        }\n        if (tr[x]\
    \ == rp) {\n            if (!M->sz) tr[x] = -1;\n            else {\n        \
    \        tr[x] = at(M, 0) - pool;\n            }\n        }\n    }\n    int root(int\
    \ x) {\n        if (up[x] != -1) return x;\n        NP xt = tree(x);\n       \
    \ int res = at(xt, 0)->idl;\n        return res;\n    }\n};\ntemplate<int N>\n\
    typename ETTree<N>::Node ETTree<N>::last_d = ETTree::Node();\ntemplate<int N>\n\
    typename ETTree<N>::NP ETTree<N>::last = &last_d;"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/EulerTourTree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/EulerTourTree.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/EulerTourTree.hpp
- /library/src/datastructure/Develop/EulerTourTree.hpp.html
title: src/datastructure/Develop/EulerTourTree.hpp
---
