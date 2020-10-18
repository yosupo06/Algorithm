---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/IMRangeAddTree.hpp\"\n/**\n *\
    \ \u6C38\u7D9A\u5316\u3055\u308C\u3066\u3044\u308B\u3001\u7BC4\u56F2add\u3001\u7BC4\
    \u56F2sum\u3001\u533A\u9593\u30B3\u30D4\u30FC\u304C\u53EF\u80FD\u306ARBST\n *\
    \ \n * GC\u306F\u5B9F\u88C5\u3055\u308C\u3066\u3044\u306A\u3044\n *\n * Verify:\
    \ ARC \u30B0\u30E9\u30D5\u3067\u306F\u306A\u3044\n */\nstruct STree {\n    using\
    \ D = ll;\n    struct Node;\n \n    using NP = const Node*;\n    static Node last_d;\n\
    \    static NP last;\n    struct Node {\n        NP l, r;\n        int sz;\n \
    \       D v, sm, lz;\n        Node() : l(nullptr), r(nullptr), sz(0) {}\n    \
    \    Node(D vv) :l(last), r(last), sz(1) {\n            v = vv;\n            sm\
    \ = 0;\n            lz = 0;\n        }\n        static Node* make(NP x) {\n  \
    \          pool[pc] = *x;\n            pc++;\n            return &pool[pc-1];\n\
    \        }\n        static Node* make(D v) {\n            pool[pc] = Node(v);\n\
    \            pc++;\n            return &pool[pc-1];\n        }\n        void push()\
    \ {\n            auto nl = make(l);\n            auto nr = make(r);\n        \
    \    if (nl->sz) {\n                nl->lzdata(lz);\n            }\n         \
    \   if (nr->sz) {\n                nr->lzdata(lz);\n            }\n          \
    \  lz = 0;\n            l = nl;\n            r = nr;\n        }\n        /// push\u306F\
    const\u306B\u95A2\u308F\u3089\u305A\u547C\u3093\u3067\u826F\u3044\n        void\
    \ push() const {\n            const_cast<Node*>(this)->push();\n        }\n  \
    \      void update() {\n            sz = 1+l->sz+r->sz;\n            sm = v;\n\
    \            if (l->sz) {\n                sm += l->sm;\n            }\n     \
    \       if (r->sz) {\n                sm += r->sm;\n            }\n        }\n\
    \        void lzdata(D x) {\n            v += x;\n            sm += sz*x;\n  \
    \          lz += x;\n        }\n    };\n    NP n;\n\n    //200,000,000\u3068\u306F\
    200MB\u306E\u610F\n    static const int PLS = 200000000 / sizeof(Node);\n    static\
    \ int pc;\n    static Node pool[PLS];\n\n    static void get(NP n, D d[]) {\n\
    \        if (!n->sz) return;\n        n->push();\n        get(n->l, d);\n    \
    \    d[n->l->sz] = n->v;\n        get(n->r, d + (n->l->sz+1));\n    }\n    void\
    \ get(D d[]) {\n        get(n, d);\n    }\n\n    void add(int l, int r, D x) {\n\
    \        auto a = split(n, l);\n        auto b = split(a.second, r-l);\n     \
    \   auto u = Node::make(b.first);\n        u->lzdata(x);\n        n = merge(merge(a.first,\
    \ u), b.second);\n    }\n    D sum(int l, int r) {\n        auto a = split(n,\
    \ l);\n        auto b = split(a.second, r-l);\n        auto u = b.first;\n   \
    \     return u->sm;\n    }\n\n    static NP built(int l, int r, D d[]) {\n   \
    \     if (l == r) return last;\n        int md = (l+r)/2;\n        auto x = Node::make(d[md]);\n\
    \        x->l = built(l, md, d);\n        x->r = built(md+1, r, d);\n        x->update();\n\
    \        return x;\n    }\n \n    STree() : n(last) {}\n    STree(NP n) : n(n)\
    \ {}\n    STree(int sz, D d[]) {\n        n = built(0, sz, d);\n    }\n\n    int\
    \ sz() {\n        return n->sz;\n    }     \n    static uint xor128(){\n     \
    \   static uint x=123456789,y=362436069,z=521288629,w=88675123;\n        uint\
    \ t;\n        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );\n\
    \    }\n    static NP merge(NP l, NP r) {\n        if (!l->sz) return r;\n   \
    \     if (!r->sz) return l;\n        l->push(); r->push();\n        auto nl =\
    \ Node::make(l);\n        auto nr = Node::make(r);\n        if ((int)(xor128()\
    \ % (nl->sz + nr->sz)) < nl->sz) {\n            nl->r = merge(nl->r, nr);\n  \
    \          nl->update();\n            return nl;\n        } else {\n         \
    \   nr->l = merge(nl, nr->l);\n            nr->update();\n            return nr;\n\
    \        }\n    }\n    STree merge(STree r) {\n        return STree(merge(n, r.n));\n\
    \    }\n    static pair<NP, NP> split(NP x, int k) {\n        if (!x->sz) return\
    \ {last, last};\n        x->push();\n        auto nx = Node::make(x);\n      \
    \  if (k <= nx->l->sz) {\n            auto y = split(nx->l, k);\n            nx->l\
    \ = y.second;\n            nx->update();\n            y.second = nx;\n       \
    \     return y;\n        } else {\n            auto y = split(x->r, k- x->l->sz\
    \ -1);\n            nx->r = y.first;\n            nx->update();\n            y.first\
    \ = nx;\n            return y;\n        }\n    }\n    pair<STree, STree> split(int\
    \ k) {\n        auto u = split(n, k);\n        return pair<STree, STree>(STree(u.first),\
    \ STree(u.second));\n    }\n};\nSTree::Node STree::last_d = STree::Node();\nSTree::NP\
    \ STree::last = &last_d;\nSTree::Node STree::pool[STree::PLS];\nint STree::pc\
    \ = 0;\n \n"
  code: "/**\n * \u6C38\u7D9A\u5316\u3055\u308C\u3066\u3044\u308B\u3001\u7BC4\u56F2\
    add\u3001\u7BC4\u56F2sum\u3001\u533A\u9593\u30B3\u30D4\u30FC\u304C\u53EF\u80FD\
    \u306ARBST\n * \n * GC\u306F\u5B9F\u88C5\u3055\u308C\u3066\u3044\u306A\u3044\n\
    \ *\n * Verify: ARC \u30B0\u30E9\u30D5\u3067\u306F\u306A\u3044\n */\nstruct STree\
    \ {\n    using D = ll;\n    struct Node;\n \n    using NP = const Node*;\n   \
    \ static Node last_d;\n    static NP last;\n    struct Node {\n        NP l, r;\n\
    \        int sz;\n        D v, sm, lz;\n        Node() : l(nullptr), r(nullptr),\
    \ sz(0) {}\n        Node(D vv) :l(last), r(last), sz(1) {\n            v = vv;\n\
    \            sm = 0;\n            lz = 0;\n        }\n        static Node* make(NP\
    \ x) {\n            pool[pc] = *x;\n            pc++;\n            return &pool[pc-1];\n\
    \        }\n        static Node* make(D v) {\n            pool[pc] = Node(v);\n\
    \            pc++;\n            return &pool[pc-1];\n        }\n        void push()\
    \ {\n            auto nl = make(l);\n            auto nr = make(r);\n        \
    \    if (nl->sz) {\n                nl->lzdata(lz);\n            }\n         \
    \   if (nr->sz) {\n                nr->lzdata(lz);\n            }\n          \
    \  lz = 0;\n            l = nl;\n            r = nr;\n        }\n        /// push\u306F\
    const\u306B\u95A2\u308F\u3089\u305A\u547C\u3093\u3067\u826F\u3044\n        void\
    \ push() const {\n            const_cast<Node*>(this)->push();\n        }\n  \
    \      void update() {\n            sz = 1+l->sz+r->sz;\n            sm = v;\n\
    \            if (l->sz) {\n                sm += l->sm;\n            }\n     \
    \       if (r->sz) {\n                sm += r->sm;\n            }\n        }\n\
    \        void lzdata(D x) {\n            v += x;\n            sm += sz*x;\n  \
    \          lz += x;\n        }\n    };\n    NP n;\n\n    //200,000,000\u3068\u306F\
    200MB\u306E\u610F\n    static const int PLS = 200000000 / sizeof(Node);\n    static\
    \ int pc;\n    static Node pool[PLS];\n\n    static void get(NP n, D d[]) {\n\
    \        if (!n->sz) return;\n        n->push();\n        get(n->l, d);\n    \
    \    d[n->l->sz] = n->v;\n        get(n->r, d + (n->l->sz+1));\n    }\n    void\
    \ get(D d[]) {\n        get(n, d);\n    }\n\n    void add(int l, int r, D x) {\n\
    \        auto a = split(n, l);\n        auto b = split(a.second, r-l);\n     \
    \   auto u = Node::make(b.first);\n        u->lzdata(x);\n        n = merge(merge(a.first,\
    \ u), b.second);\n    }\n    D sum(int l, int r) {\n        auto a = split(n,\
    \ l);\n        auto b = split(a.second, r-l);\n        auto u = b.first;\n   \
    \     return u->sm;\n    }\n\n    static NP built(int l, int r, D d[]) {\n   \
    \     if (l == r) return last;\n        int md = (l+r)/2;\n        auto x = Node::make(d[md]);\n\
    \        x->l = built(l, md, d);\n        x->r = built(md+1, r, d);\n        x->update();\n\
    \        return x;\n    }\n \n    STree() : n(last) {}\n    STree(NP n) : n(n)\
    \ {}\n    STree(int sz, D d[]) {\n        n = built(0, sz, d);\n    }\n\n    int\
    \ sz() {\n        return n->sz;\n    }     \n    static uint xor128(){\n     \
    \   static uint x=123456789,y=362436069,z=521288629,w=88675123;\n        uint\
    \ t;\n        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );\n\
    \    }\n    static NP merge(NP l, NP r) {\n        if (!l->sz) return r;\n   \
    \     if (!r->sz) return l;\n        l->push(); r->push();\n        auto nl =\
    \ Node::make(l);\n        auto nr = Node::make(r);\n        if ((int)(xor128()\
    \ % (nl->sz + nr->sz)) < nl->sz) {\n            nl->r = merge(nl->r, nr);\n  \
    \          nl->update();\n            return nl;\n        } else {\n         \
    \   nr->l = merge(nl, nr->l);\n            nr->update();\n            return nr;\n\
    \        }\n    }\n    STree merge(STree r) {\n        return STree(merge(n, r.n));\n\
    \    }\n    static pair<NP, NP> split(NP x, int k) {\n        if (!x->sz) return\
    \ {last, last};\n        x->push();\n        auto nx = Node::make(x);\n      \
    \  if (k <= nx->l->sz) {\n            auto y = split(nx->l, k);\n            nx->l\
    \ = y.second;\n            nx->update();\n            y.second = nx;\n       \
    \     return y;\n        } else {\n            auto y = split(x->r, k- x->l->sz\
    \ -1);\n            nx->r = y.first;\n            nx->update();\n            y.first\
    \ = nx;\n            return y;\n        }\n    }\n    pair<STree, STree> split(int\
    \ k) {\n        auto u = split(n, k);\n        return pair<STree, STree>(STree(u.first),\
    \ STree(u.second));\n    }\n};\nSTree::Node STree::last_d = STree::Node();\nSTree::NP\
    \ STree::last = &last_d;\nSTree::Node STree::pool[STree::PLS];\nint STree::pc\
    \ = 0;\n "
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/IMRangeAddTree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/IMRangeAddTree.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/IMRangeAddTree.hpp
- /library/src/datastructure/Develop/IMRangeAddTree.hpp.html
title: src/datastructure/Develop/IMRangeAddTree.hpp
---
