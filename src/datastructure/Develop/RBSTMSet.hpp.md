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
  bundledCode: "#line 1 \"src/datastructure/Develop/RBSTMSet.hpp\"\nstruct Tree {\n\
    \    using D = ll;\n    struct Node;\n    using NP = Node*;\n    static Node last_d;\n\
    \    static NP last;\n    struct Node {\n        NP l, r;\n        int sz;\n \
    \       D v;\n        Node(D v) :l(last), r(last), sz(1), v(v) {}\n        Node()\
    \ :l(nullptr), r(nullptr), sz(0) {}\n        void push() {\n\n        }\n    \
    \    NP update() {\n            sz = 1+l->sz+r->sz;\n            return this;\n\
    \        }\n        int lb(D a) {\n            if (!sz) return 0;\n          \
    \  if (a <= v) return l->lb(a);\n            return l->sz + 1 + r->lb(a);\n  \
    \      }\n        int ub(D a) {\n            if (!sz) return 0;\n            if\
    \ (v <= a) return l->sz + 1 + r->ub(a);\n            return l->ub(a);\n      \
    \  }\n        D get(int k) {\n            if (k == l->sz) return v;\n        \
    \    if (k < l->sz) {\n                return l->get(k);\n            } else {\n\
    \                return r->get(k- (l->sz+1));\n            }\n        }\n    }\
    \ *n;\n\n    static uint xor128(){\n        static uint x=123456789,y=362436069,z=521288629,w=88675123;\n\
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
    \ y;\n        }\n    }\n\n    Tree() : n(last) {}\n    Tree(NP n) : n(n) {}\n\
    \    int sz() {\n        return n->sz;\n    }\n    void merge(Tree r) {\n    \
    \    n = merge(n, r.n);\n    }\n    Tree split(int k) {\n        auto u = split(n,\
    \ k);\n        n = u.first;\n        return Tree(u.second);\n    }\n    void insert(D\
    \ v) {\n        auto u = split(n, lb(v));\n        n = merge(merge(u.first, new\
    \ Node(v)), u.second);\n    }\n    void erase(D v) {\n        assert(count(v));\n\
    \        auto u = split(n, lb(v));\n        n = merge(u.first, split(u.second,\
    \ 1).second);\n    }\n    int count(D v) {\n        return ub(v) - lb(v);\n  \
    \  }\n    int lb(D v) {\n        return n->lb(v);\n    }\n    int ub(D v) {\n\
    \        return n->ub(v);\n    }\n    D get(int k) {\n        return n->get(k);\n\
    \    }\n};\nTree::Node Tree::last_d = Tree::Node();\nTree::NP Tree::last = &last_d;\n"
  code: "struct Tree {\n    using D = ll;\n    struct Node;\n    using NP = Node*;\n\
    \    static Node last_d;\n    static NP last;\n    struct Node {\n        NP l,\
    \ r;\n        int sz;\n        D v;\n        Node(D v) :l(last), r(last), sz(1),\
    \ v(v) {}\n        Node() :l(nullptr), r(nullptr), sz(0) {}\n        void push()\
    \ {\n\n        }\n        NP update() {\n            sz = 1+l->sz+r->sz;\n   \
    \         return this;\n        }\n        int lb(D a) {\n            if (!sz)\
    \ return 0;\n            if (a <= v) return l->lb(a);\n            return l->sz\
    \ + 1 + r->lb(a);\n        }\n        int ub(D a) {\n            if (!sz) return\
    \ 0;\n            if (v <= a) return l->sz + 1 + r->ub(a);\n            return\
    \ l->ub(a);\n        }\n        D get(int k) {\n            if (k == l->sz) return\
    \ v;\n            if (k < l->sz) {\n                return l->get(k);\n      \
    \      } else {\n                return r->get(k- (l->sz+1));\n            }\n\
    \        }\n    } *n;\n\n    static uint xor128(){\n        static uint x=123456789,y=362436069,z=521288629,w=88675123;\n\
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
    \ y;\n        }\n    }\n\n    Tree() : n(last) {}\n    Tree(NP n) : n(n) {}\n\
    \    int sz() {\n        return n->sz;\n    }\n    void merge(Tree r) {\n    \
    \    n = merge(n, r.n);\n    }\n    Tree split(int k) {\n        auto u = split(n,\
    \ k);\n        n = u.first;\n        return Tree(u.second);\n    }\n    void insert(D\
    \ v) {\n        auto u = split(n, lb(v));\n        n = merge(merge(u.first, new\
    \ Node(v)), u.second);\n    }\n    void erase(D v) {\n        assert(count(v));\n\
    \        auto u = split(n, lb(v));\n        n = merge(u.first, split(u.second,\
    \ 1).second);\n    }\n    int count(D v) {\n        return ub(v) - lb(v);\n  \
    \  }\n    int lb(D v) {\n        return n->lb(v);\n    }\n    int ub(D v) {\n\
    \        return n->ub(v);\n    }\n    D get(int k) {\n        return n->get(k);\n\
    \    }\n};\nTree::Node Tree::last_d = Tree::Node();\nTree::NP Tree::last = &last_d;"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/RBSTMSet.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/RBSTMSet.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/RBSTMSet.hpp
- /library/src/datastructure/Develop/RBSTMSet.hpp.html
title: src/datastructure/Develop/RBSTMSet.hpp
---
