---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/RBSTree.hpp\"\nstruct NTree {\n\
    \    using D = ll;\n    struct Node;\n    using NP = Node*;\n    static Node last_d;\n\
    \    static NP last;\n    struct Node {\n        NP l, r;\n        int sz;\n \
    \       D v;\n        Node(D v) :l(last), r(last), sz(1), v(v) {}\n        Node()\
    \ :l(nullptr), r(nullptr), sz(0) {} //last\u7528\n        void push() {\n    \
    \        assert(this != last);\n        }\n        NP update() {\n           \
    \ assert(this != last);\n            sz = 1+l->sz+r->sz;\n            return this;\n\
    \        }\n        D get(int a) {\n            assert(0 <= a && a < sz);\n  \
    \          push();\n            if (a < l->sz) {\n                return l->get(a);\n\
    \            } else if (a == l->sz) {\n                return v;\n           \
    \ } else {\n                return r->get(a- (l->sz+1));\n            }\n    \
    \    }\n    } *n;\n\n\n    static NP built(int sz, D d[]) {\n        if (!sz)\
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
    \       y.first = x->update();\n            return y;\n        }\n    }\n    NTree()\
    \ : n(last) {}\n    NTree(NP n) : n(n) {}\n    NTree(D d) : n(new Node(d)) {}\n\
    \    NTree(int sz, D d[]) {\n        n = built(sz, d);\n    }\n    int sz() {\n\
    \        return n->sz;\n    }\n    void merge(NTree r) {\n        n = merge(n,\
    \ r.n);\n    }\n    NTree split(int k) {\n        auto u = split(n, k);\n    \
    \    n = u.first;\n        return NTree(u.second);\n    }\n    void insert(int\
    \ k, D x) {\n        auto u = split(n, k);\n        n = merge(merge(u.first, new\
    \ Node(x)), u.second);\n    }\n    void erase(int k) {\n        auto u = split(n,\
    \ k);\n        n = merge(u.first, split(u.second, 1).second);\n    }\n    D get(int\
    \ l) {\n        return n->get(l);\n    }\n};\nNTree::Node NTree::last_d = NTree::Node();\n\
    NTree::NP NTree::last = &last_d;\n"
  code: "struct NTree {\n    using D = ll;\n    struct Node;\n    using NP = Node*;\n\
    \    static Node last_d;\n    static NP last;\n    struct Node {\n        NP l,\
    \ r;\n        int sz;\n        D v;\n        Node(D v) :l(last), r(last), sz(1),\
    \ v(v) {}\n        Node() :l(nullptr), r(nullptr), sz(0) {} //last\u7528\n   \
    \     void push() {\n            assert(this != last);\n        }\n        NP\
    \ update() {\n            assert(this != last);\n            sz = 1+l->sz+r->sz;\n\
    \            return this;\n        }\n        D get(int a) {\n            assert(0\
    \ <= a && a < sz);\n            push();\n            if (a < l->sz) {\n      \
    \          return l->get(a);\n            } else if (a == l->sz) {\n         \
    \       return v;\n            } else {\n                return r->get(a- (l->sz+1));\n\
    \            }\n        }\n    } *n;\n\n\n    static NP built(int sz, D d[]) {\n\
    \        if (!sz) return last;\n        int md = sz/2;\n        NP x = new Node(d[md]);\n\
    \        x->l = built(md, d);\n        x->r = built(sz-(md+1), d+(md+1));\n  \
    \      return x->update();\n    }\n\n    static uint xor128(){\n        static\
    \ uint x=123456789,y=362436069,z=521288629,w=88675123;\n        uint t;\n    \
    \    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );\n    }\n \
    \   static NP merge(NP l, NP r) {\n        if (!l->sz) return r;\n        if (!r->sz)\
    \ return l; \n        l->push(); r->push();\n        if ((int)(xor128() % (l->sz\
    \ + r->sz)) < l->sz) {\n            l->r = merge(l->r, r);\n            return\
    \ l->update();\n        } else {\n            r->l = merge(l, r->l);\n       \
    \     return r->update();\n        }\n    }\n    static pair<NP, NP> split(NP\
    \ x, int k) {\n        if (!x->sz) return {last, last};\n        x->push();\n\
    \        if (k <= x->l->sz) {\n            auto y = split(x->l, k);\n        \
    \    x->l = y.second;\n            y.second = x->update();\n            return\
    \ y;\n        } else {\n            auto y = split(x->r, k- x->l->sz -1);\n  \
    \          x->r = y.first;\n            y.first = x->update();\n            return\
    \ y;\n        }\n    }\n    NTree() : n(last) {}\n    NTree(NP n) : n(n) {}\n\
    \    NTree(D d) : n(new Node(d)) {}\n    NTree(int sz, D d[]) {\n        n = built(sz,\
    \ d);\n    }\n    int sz() {\n        return n->sz;\n    }\n    void merge(NTree\
    \ r) {\n        n = merge(n, r.n);\n    }\n    NTree split(int k) {\n        auto\
    \ u = split(n, k);\n        n = u.first;\n        return NTree(u.second);\n  \
    \  }\n    void insert(int k, D x) {\n        auto u = split(n, k);\n        n\
    \ = merge(merge(u.first, new Node(x)), u.second);\n    }\n    void erase(int k)\
    \ {\n        auto u = split(n, k);\n        n = merge(u.first, split(u.second,\
    \ 1).second);\n    }\n    D get(int l) {\n        return n->get(l);\n    }\n};\n\
    NTree::Node NTree::last_d = NTree::Node();\nNTree::NP NTree::last = &last_d;"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/RBSTree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/RBSTree.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/RBSTree.hpp
- /library/src/datastructure/Develop/RBSTree.hpp.html
title: src/datastructure/Develop/RBSTree.hpp
---
