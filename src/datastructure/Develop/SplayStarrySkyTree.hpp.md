---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/SplayStarrySkyTree.hpp\"\nstruct\
    \ STree {\n    using D = ll;\n    const static D INF = 1LL<<55;\n    struct Node;\n\
    \    using NP = Node*;\n    static Node last_d;\n    static NP last;\n    struct\
    \ Node {\n        NP p, l, r;\n        int sz;\n        D v, mi, lz;\n       \
    \ Node(D v) :p(nullptr), l(last), r(last), sz(1), v(v), mi(v), lz(0) {}\n    \
    \    Node() : l(nullptr), r(nullptr), sz(0) {}\n        inline int pos() {\n \
    \           if (p) {\n                if (p->l == this) return -1;\n         \
    \       if (p->r == this) return 1;\n            }\n            return 0;\n  \
    \      }\n        void rot() {\n            NP qq = p->p;\n            int pps\
    \ = p->pos();\n            if (p->l == this) {\n                p->l = r; r->p\
    \ = p;\n                r = p; p->p = this;\n            } else {\n          \
    \      p->r = l; l->p = p;\n                l = p; p->p = this;\n            }\n\
    \            p->update(); update();\n            p = qq;\n            if (!pps)\
    \ return;\n            if (pps == -1) {\n                qq->l = this;\n     \
    \       } else {\n                qq->r = this;\n            }\n            qq->update();\n\
    \        }\n        void splay() {\n            assert(this != last);\n      \
    \      supush();\n            int ps;\n            while ((ps = pos())) {\n  \
    \              int pps = p->pos();\n                if (!pps) {\n            \
    \        rot();\n                } else if (ps == pps) {\n                   \
    \ p->rot(); rot();\n                } else {\n                    rot(); rot();\n\
    \                }\n            }\n        }\n        NP splay(int k) {\n    \
    \        assert(this != last);\n            assert(0 <= k && k < sz);\n      \
    \      if (k < l->sz) {\n                return l->splay(k);\n            } else\
    \ if (k == l->sz) {\n                splay();\n                return this;\n\
    \            } else {\n                return r->splay(k-(l->sz+1));\n       \
    \     }\n        }\n        void supush() {\n            if (pos()) {\n      \
    \          p->supush();\n            }\n            push();\n        }\n     \
    \   void push() { //push\u3092\u3059\u308B\u3068\u3001push\u3092\u3057\u305F\u9802\
    \u70B9\u3068\u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\u6B63\
    \u5F53\u6027\u304C\u4FDD\u8A3C\u3055\u308C\u308B\n            assert(this != last);\n\
    \            if (lz) {\n                if (l->sz) {\n                    l->lzdata(lz);\n\
    \                }\n                if (r->sz) {\n                    r->lzdata(lz);\n\
    \                }\n                lz = 0;\n            }\n        }\n      \
    \  void lzdata(D d) {\n            v += d;\n            mi += d;\n           \
    \ lz += d;\n        }\n        NP update() {\n            assert(this != last);\n\
    \            sz = 1+l->sz+r->sz;\n            assert(!lz);\n            mi = v;\n\
    \            if (l->sz) {\n                mi = min(mi, l->mi);\n            }\n\
    \            if (r->sz) {\n                mi = min(mi, r->mi);\n            }\n\
    \            return this;\n        }\n    } *n;\n    static NP merge(NP l, NP\
    \ r) {\n        if (r == last) {\n            return l;\n        }\n        r\
    \ = r->splay(0);\n        assert(r->l == last);\n        r->l = l;\n        l->p\
    \ = r;\n        return r->update();\n    }\n    static pair<NP, NP> split(NP x,\
    \ int k) {\n        assert(0 <= k && k <= x->sz);\n        if (k == x->sz) {\n\
    \            return {x, last};\n        }\n        x = x->splay(k);\n        NP\
    \ l = x->l;\n        l->p = nullptr;\n        x->l = last;\n        return {l,\
    \ x->update()};\n    }\n    static NP built(int sz, ll d[]) {\n        if (!sz)\
    \ return last;\n        int md = sz/2;\n        NP x = new Node(d[md]);\n    \
    \    x->l = built(md, d);\n        x->l->p = x;\n        x->r = built(sz-(md+1),\
    \ d+(md+1));\n        x->r->p = x;\n        return x->update();\n    }\n    STree()\
    \ : n(last) {}\n    STree(NP n) : n(n) {}\n    STree(D d) : n(new Node(d)) {}\n\
    \    STree(int sz, D d[]) {\n        n = built(sz, d);\n    }\n    int sz() {\n\
    \        return n->sz;\n    }\n    void insert(int k, D v) {\n        auto u =\
    \ split(n, k);\n        n = merge(merge(u.first, new Node(v)), u.second);\n  \
    \  }\n    void erase(int k) {\n        auto u = split(n, k);\n        n = merge(u.first,\
    \ split(u.second, 1).second);\n    }\n    void add(int l, int r, D x) {\n    \
    \    auto b = split(n, r);\n        auto a = split(b.first, l);\n        a.second->lzdata(x);\n\
    \        n = merge(merge(a.first, a.second), b.second);\n    }\n    D get(int\
    \ l, int r) {\n        auto b = split(n, r);\n        auto a = split(b.first,\
    \ l);\n        D res = a.second->mi;\n        n = merge(merge(a.first, a.second),\
    \ b.second);\n        return res;\n    }\n};\nSTree::Node STree::last_d = STree::Node();\n\
    STree::NP STree::last = &last_d;\n"
  code: "struct STree {\n    using D = ll;\n    const static D INF = 1LL<<55;\n  \
    \  struct Node;\n    using NP = Node*;\n    static Node last_d;\n    static NP\
    \ last;\n    struct Node {\n        NP p, l, r;\n        int sz;\n        D v,\
    \ mi, lz;\n        Node(D v) :p(nullptr), l(last), r(last), sz(1), v(v), mi(v),\
    \ lz(0) {}\n        Node() : l(nullptr), r(nullptr), sz(0) {}\n        inline\
    \ int pos() {\n            if (p) {\n                if (p->l == this) return\
    \ -1;\n                if (p->r == this) return 1;\n            }\n          \
    \  return 0;\n        }\n        void rot() {\n            NP qq = p->p;\n   \
    \         int pps = p->pos();\n            if (p->l == this) {\n             \
    \   p->l = r; r->p = p;\n                r = p; p->p = this;\n            } else\
    \ {\n                p->r = l; l->p = p;\n                l = p; p->p = this;\n\
    \            }\n            p->update(); update();\n            p = qq;\n    \
    \        if (!pps) return;\n            if (pps == -1) {\n                qq->l\
    \ = this;\n            } else {\n                qq->r = this;\n            }\n\
    \            qq->update();\n        }\n        void splay() {\n            assert(this\
    \ != last);\n            supush();\n            int ps;\n            while ((ps\
    \ = pos())) {\n                int pps = p->pos();\n                if (!pps)\
    \ {\n                    rot();\n                } else if (ps == pps) {\n   \
    \                 p->rot(); rot();\n                } else {\n               \
    \     rot(); rot();\n                }\n            }\n        }\n        NP splay(int\
    \ k) {\n            assert(this != last);\n            assert(0 <= k && k < sz);\n\
    \            if (k < l->sz) {\n                return l->splay(k);\n         \
    \   } else if (k == l->sz) {\n                splay();\n                return\
    \ this;\n            } else {\n                return r->splay(k-(l->sz+1));\n\
    \            }\n        }\n        void supush() {\n            if (pos()) {\n\
    \                p->supush();\n            }\n            push();\n        }\n\
    \        void push() { //push\u3092\u3059\u308B\u3068\u3001push\u3092\u3057\u305F\
    \u9802\u70B9\u3068\u305D\u306E\u5B50\u306E\"\u3059\u3079\u3066\"\u306E\u5024\u306E\
    \u6B63\u5F53\u6027\u304C\u4FDD\u8A3C\u3055\u308C\u308B\n            assert(this\
    \ != last);\n            if (lz) {\n                if (l->sz) {\n           \
    \         l->lzdata(lz);\n                }\n                if (r->sz) {\n  \
    \                  r->lzdata(lz);\n                }\n                lz = 0;\n\
    \            }\n        }\n        void lzdata(D d) {\n            v += d;\n \
    \           mi += d;\n            lz += d;\n        }\n        NP update() {\n\
    \            assert(this != last);\n            sz = 1+l->sz+r->sz;\n        \
    \    assert(!lz);\n            mi = v;\n            if (l->sz) {\n           \
    \     mi = min(mi, l->mi);\n            }\n            if (r->sz) {\n        \
    \        mi = min(mi, r->mi);\n            }\n            return this;\n     \
    \   }\n    } *n;\n    static NP merge(NP l, NP r) {\n        if (r == last) {\n\
    \            return l;\n        }\n        r = r->splay(0);\n        assert(r->l\
    \ == last);\n        r->l = l;\n        l->p = r;\n        return r->update();\n\
    \    }\n    static pair<NP, NP> split(NP x, int k) {\n        assert(0 <= k &&\
    \ k <= x->sz);\n        if (k == x->sz) {\n            return {x, last};\n   \
    \     }\n        x = x->splay(k);\n        NP l = x->l;\n        l->p = nullptr;\n\
    \        x->l = last;\n        return {l, x->update()};\n    }\n    static NP\
    \ built(int sz, ll d[]) {\n        if (!sz) return last;\n        int md = sz/2;\n\
    \        NP x = new Node(d[md]);\n        x->l = built(md, d);\n        x->l->p\
    \ = x;\n        x->r = built(sz-(md+1), d+(md+1));\n        x->r->p = x;\n   \
    \     return x->update();\n    }\n    STree() : n(last) {}\n    STree(NP n) :\
    \ n(n) {}\n    STree(D d) : n(new Node(d)) {}\n    STree(int sz, D d[]) {\n  \
    \      n = built(sz, d);\n    }\n    int sz() {\n        return n->sz;\n    }\n\
    \    void insert(int k, D v) {\n        auto u = split(n, k);\n        n = merge(merge(u.first,\
    \ new Node(v)), u.second);\n    }\n    void erase(int k) {\n        auto u = split(n,\
    \ k);\n        n = merge(u.first, split(u.second, 1).second);\n    }\n    void\
    \ add(int l, int r, D x) {\n        auto b = split(n, r);\n        auto a = split(b.first,\
    \ l);\n        a.second->lzdata(x);\n        n = merge(merge(a.first, a.second),\
    \ b.second);\n    }\n    D get(int l, int r) {\n        auto b = split(n, r);\n\
    \        auto a = split(b.first, l);\n        D res = a.second->mi;\n        n\
    \ = merge(merge(a.first, a.second), b.second);\n        return res;\n    }\n};\n\
    STree::Node STree::last_d = STree::Node();\nSTree::NP STree::last = &last_d;"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/SplayStarrySkyTree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/SplayStarrySkyTree.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/SplayStarrySkyTree.hpp
- /library/src/datastructure/Develop/SplayStarrySkyTree.hpp.html
title: src/datastructure/Develop/SplayStarrySkyTree.hpp
---
