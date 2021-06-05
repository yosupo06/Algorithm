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
  bundledCode: "#line 1 \"src/datastructure/Develop/RBSStarrySkyTree.hpp\"\n/*\nRBST\u3067\
    \u66F8\u304B\u308C\u305FStarry Sky Tree\n*/\n\nstruct STree {\n    using D = ll;\n\
    \    const static D INF = 1LL<<55;\n    struct Node;\n    using NP = Node*;\n\
    \    static Node last_d;\n    static NP last;\n    struct Node {\n        NP l,\
    \ r;\n        int sz;\n        D v, mi, lz;\n        Node(D v) :l(last), r(last),\
    \ sz(1), v(v), mi(v), lz(0) {}\n        Node() :l(nullptr), r(nullptr), sz(0)\
    \ {} //last\u7528\n        void push() {\n            assert(this != last);\n\
    \            if (lz) {\n                if (l->sz) {\n                    l->lzdata(lz);\n\
    \                }\n                if (r->sz) {\n                    r->lzdata(lz);\n\
    \                }\n                lz = 0;\n            }\n        }\n      \
    \  void lzdata(D d) {\n            v += d;\n            mi += d;\n           \
    \ lz += d;\n        }\n        NP update() {\n            assert(this != last);\n\
    \            sz = 1+l->sz+r->sz;\n            assert(!lz);\n            mi = v;\n\
    \            if (l->sz) {\n                mi = min(mi, l->mi);\n            }\n\
    \            if (r->sz) {\n                mi = min(mi, r->mi);\n            }\n\
    \            return this;\n        }\n        D get(int a, int b) {\n        \
    \    if (!sz || b <= 0 || sz <= a) return INF;\n            if (a <= 0 && sz <=\
    \ b) return mi;\n            push();\n            D res = INF;\n            if\
    \ (a <= l->sz && l->sz < b) res = min(res, v);\n            res = min(res, l->get(a,\
    \ b));\n            res = min(res, r->get(a- l->sz - 1, b- l->sz - 1));\n    \
    \        return res;\n        }\n        void add(int a, int b, D x) {\n     \
    \       if (!sz || b <= 0 || sz <= a) return;\n            if (a <= 0 && sz <=\
    \ b) {\n                lzdata(x);\n                return;\n            }\n \
    \           push();\n            l->add(a, b, x);\n            if (a <= l->sz\
    \ && l->sz < b) {\n                v += x;\n            }\n            r->add(a-\
    \ l->sz - 1, b- l->sz - 1, x);\n            update();\n        }\n    } *n;\n\n\
    \n    static NP built(int sz, D d[]) {\n        if (!sz) return last;\n      \
    \  int md = sz/2;\n        NP x = new Node(d[md]);\n        x->l = built(md, d);\n\
    \        x->r = built(sz-(md+1), d+(md+1));\n        return x->update();\n   \
    \ }\n\n    static uint xor128(){\n        static uint x=123456789,y=362436069,z=521288629,w=88675123;\n\
    \        uint t;\n        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8))\
    \ );\n    }\n    static NP merge(NP l, NP r) {\n        if (!l->sz) return r;\n\
    \        if (!r->sz) return l; \n        l->push(); r->push();\n        if ((int)(xor128()\
    \ % (l->sz + r->sz)) < l->sz) {\n            l->r = merge(l->r, r);\n        \
    \    return l->update();\n        } else {\n            r->l = merge(l, r->l);\n\
    \            return r->update();\n        }\n    }\n    static pair<NP, NP> split(NP\
    \ x, int k) {\n        if (!x->sz) return {last, last};\n        x->push();\n\
    \        if (k <= x->l->sz) {\n            auto y = split(x->l, k);\n        \
    \    x->l = y.second;\n            y.second = x->update();\n            return\
    \ y;\n        } else {\n            auto y = split(x->r, k- x->l->sz -1);\n  \
    \          x->r = y.first;\n            y.first = x->update();\n            return\
    \ y;\n        }\n    }\n    STree() : n(last) {}\n    STree(NP n) : n(n) {}\n\
    \    STree(D d) : n(new Node(d)) {}\n    STree(int sz, D d[]) {\n        n = built(sz,\
    \ d);\n    }\n    int sz() {\n        return n->sz;\n    }\n    void merge(STree\
    \ r) {\n        n = merge(n, r.n);\n    }\n    STree split(int k) {\n        auto\
    \ u = split(n, k);\n        n = u.first;\n        return STree(u.second);\n  \
    \  }\n    void insert(int k, D x) {\n        auto u = split(n, k);\n        n\
    \ = merge(merge(u.first, new Node(x)), u.second);\n    }\n    void erase(int k)\
    \ {\n        auto u = split(n, k);\n        n = merge(u.first, split(u.second,\
    \ 1).second);\n    }\n    void add(int l, int r, D x) {\n        return n->add(l,\
    \ r, x);\n    }\n    D get(int l, int r) {\n        return n->get(l, r);\n   \
    \ }\n};\nSTree::Node STree::last_d = STree::Node();\nSTree::NP STree::last = &last_d;\n"
  code: "/*\nRBST\u3067\u66F8\u304B\u308C\u305FStarry Sky Tree\n*/\n\nstruct STree\
    \ {\n    using D = ll;\n    const static D INF = 1LL<<55;\n    struct Node;\n\
    \    using NP = Node*;\n    static Node last_d;\n    static NP last;\n    struct\
    \ Node {\n        NP l, r;\n        int sz;\n        D v, mi, lz;\n        Node(D\
    \ v) :l(last), r(last), sz(1), v(v), mi(v), lz(0) {}\n        Node() :l(nullptr),\
    \ r(nullptr), sz(0) {} //last\u7528\n        void push() {\n            assert(this\
    \ != last);\n            if (lz) {\n                if (l->sz) {\n           \
    \         l->lzdata(lz);\n                }\n                if (r->sz) {\n  \
    \                  r->lzdata(lz);\n                }\n                lz = 0;\n\
    \            }\n        }\n        void lzdata(D d) {\n            v += d;\n \
    \           mi += d;\n            lz += d;\n        }\n        NP update() {\n\
    \            assert(this != last);\n            sz = 1+l->sz+r->sz;\n        \
    \    assert(!lz);\n            mi = v;\n            if (l->sz) {\n           \
    \     mi = min(mi, l->mi);\n            }\n            if (r->sz) {\n        \
    \        mi = min(mi, r->mi);\n            }\n            return this;\n     \
    \   }\n        D get(int a, int b) {\n            if (!sz || b <= 0 || sz <= a)\
    \ return INF;\n            if (a <= 0 && sz <= b) return mi;\n            push();\n\
    \            D res = INF;\n            if (a <= l->sz && l->sz < b) res = min(res,\
    \ v);\n            res = min(res, l->get(a, b));\n            res = min(res, r->get(a-\
    \ l->sz - 1, b- l->sz - 1));\n            return res;\n        }\n        void\
    \ add(int a, int b, D x) {\n            if (!sz || b <= 0 || sz <= a) return;\n\
    \            if (a <= 0 && sz <= b) {\n                lzdata(x);\n          \
    \      return;\n            }\n            push();\n            l->add(a, b, x);\n\
    \            if (a <= l->sz && l->sz < b) {\n                v += x;\n       \
    \     }\n            r->add(a- l->sz - 1, b- l->sz - 1, x);\n            update();\n\
    \        }\n    } *n;\n\n\n    static NP built(int sz, D d[]) {\n        if (!sz)\
    \ return last;\n        int md = sz/2;\n        NP x = new Node(d[md]);\n    \
    \    x->l = built(md, d);\n        x->r = built(sz-(md+1), d+(md+1));\n      \
    \  return x->update();\n    }\n\n    static uint xor128(){\n        static uint\
    \ x=123456789,y=362436069,z=521288629,w=88675123;\n        uint t;\n        t=(x^(x<<11));x=y;y=z;z=w;\
    \ return( w=(w^(w>>19))^(t^(t>>8)) );\n    }\n    static NP merge(NP l, NP r)\
    \ {\n        if (!l->sz) return r;\n        if (!r->sz) return l; \n        l->push();\
    \ r->push();\n        if ((int)(xor128() % (l->sz + r->sz)) < l->sz) {\n     \
    \       l->r = merge(l->r, r);\n            return l->update();\n        } else\
    \ {\n            r->l = merge(l, r->l);\n            return r->update();\n   \
    \     }\n    }\n    static pair<NP, NP> split(NP x, int k) {\n        if (!x->sz)\
    \ return {last, last};\n        x->push();\n        if (k <= x->l->sz) {\n   \
    \         auto y = split(x->l, k);\n            x->l = y.second;\n           \
    \ y.second = x->update();\n            return y;\n        } else {\n         \
    \   auto y = split(x->r, k- x->l->sz -1);\n            x->r = y.first;\n     \
    \       y.first = x->update();\n            return y;\n        }\n    }\n    STree()\
    \ : n(last) {}\n    STree(NP n) : n(n) {}\n    STree(D d) : n(new Node(d)) {}\n\
    \    STree(int sz, D d[]) {\n        n = built(sz, d);\n    }\n    int sz() {\n\
    \        return n->sz;\n    }\n    void merge(STree r) {\n        n = merge(n,\
    \ r.n);\n    }\n    STree split(int k) {\n        auto u = split(n, k);\n    \
    \    n = u.first;\n        return STree(u.second);\n    }\n    void insert(int\
    \ k, D x) {\n        auto u = split(n, k);\n        n = merge(merge(u.first, new\
    \ Node(x)), u.second);\n    }\n    void erase(int k) {\n        auto u = split(n,\
    \ k);\n        n = merge(u.first, split(u.second, 1).second);\n    }\n    void\
    \ add(int l, int r, D x) {\n        return n->add(l, r, x);\n    }\n    D get(int\
    \ l, int r) {\n        return n->get(l, r);\n    }\n};\nSTree::Node STree::last_d\
    \ = STree::Node();\nSTree::NP STree::last = &last_d;"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/RBSStarrySkyTree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/RBSStarrySkyTree.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/RBSStarrySkyTree.hpp
- /library/src/datastructure/Develop/RBSStarrySkyTree.hpp.html
title: src/datastructure/Develop/RBSStarrySkyTree.hpp
---
