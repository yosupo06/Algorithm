---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/lctree_lca.test.cpp
    title: src/lctree_lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/lctree_vertex_add_path_sum.test.cpp
    title: src/lctree_vertex_add_path_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/linkcuttree.hpp\"\ntemplate <class N>\
    \ struct LCNode {\n    using NP = LCNode*;\n    using D = typename N::D;\n   \
    \ NP p = nullptr, l = nullptr, r = nullptr;\n    int sz = 1;\n    bool rev = false;\n\
    \    D v = N::e_d(), sm = N::e_d();\n\n    void single_set(D x) {\n        v =\
    \ x;\n        update();\n    }\n    void single_add(D x) {\n        v = N::op_dd(v,\
    \ x);\n        update();\n    }\n\n    void init_node(D _v) {\n        v = _v;\n\
    \        sm = _v;\n    }\n    void update() {\n        sz = 1;\n        if (l)\
    \ sz += l->sz;\n        if (r) sz += r->sz;\n        sm = l ? N::op_dd(l->sm,\
    \ v) : v;\n        if (r) sm = N::op_dd(sm, r->sm);\n    }\n    void push() {\n\
    \        if (rev) {\n            if (l) l->revdata();\n            if (r) r->revdata();\n\
    \            rev = false;\n        }\n    }\n    void revdata() {\n        rev\
    \ ^= true;\n        swap(l, r);\n        sm = N::rev(sm);\n    }\n\n    inline\
    \ int pos() {\n        if (p) {\n            if (p->l == this) return -1;\n  \
    \          if (p->r == this) return 1;\n        }\n        return 0;\n    }\n\
    \    void rot() {\n        NP q = p->p;\n        int pps = p->pos();\n       \
    \ if (pps == -1) q->l = this;\n        if (pps == 1) q->r = this;\n        if\
    \ (p->l == this) {\n            p->l = r;\n            if (r) r->p = p;\n    \
    \        r = p;\n        } else {\n            p->r = l;\n            if (l) l->p\
    \ = p;\n            l = p;\n        }\n        p->p = this;\n        p->update();\n\
    \        update();\n        p = q;\n        if (q) q->update();\n    }\n    void\
    \ all_push() {\n        if (pos()) p->all_push();\n        push();\n    }\n  \
    \  void splay() {\n        all_push();\n        int ps;\n        while ((ps =\
    \ pos())) {\n            int pps = p->pos();\n            if (!pps) {\n      \
    \          rot();\n            } else if (ps == pps) {\n                p->rot();\n\
    \                rot();\n            } else {\n                rot();\n      \
    \          rot();\n            }\n        }\n    }\n    void expose() {\n    \
    \    NP u = this, ur = nullptr;\n        do {\n            u->splay();\n     \
    \       u->r = ur;\n            u->update();\n            ur = u;\n        } while\
    \ ((u = u->p));\n        splay();\n    }\n    // \u89AA\u3068\u3057\u3066np\u3092\
    \u63A5\u7D9A\u3059\u308B\n    void link(NP np) {\n        evert();\n        np->expose();\n\
    \        p = np;\n    }\n    // \u89AA\u304B\u3089\u81EA\u5206\u3092\u5207\u308A\
    \u96E2\u3059\n    void cut() {\n        expose();\n        assert(l);\n      \
    \  l->p = nullptr;\n        l = nullptr;\n        update();\n    }\n    void evert()\
    \ {\n        expose();\n        revdata();\n    }\n\n    NP lca(NP n) {\n    \
    \    n->expose();\n        expose();\n        NP t = n;\n        while (n->p !=\
    \ nullptr) {\n            if (!n->pos()) t = n->p;\n            n = n->p;\n  \
    \      }\n        return (this == n) ? t : nullptr;\n    }\n};\n"
  code: "template <class N> struct LCNode {\n    using NP = LCNode*;\n    using D\
    \ = typename N::D;\n    NP p = nullptr, l = nullptr, r = nullptr;\n    int sz\
    \ = 1;\n    bool rev = false;\n    D v = N::e_d(), sm = N::e_d();\n\n    void\
    \ single_set(D x) {\n        v = x;\n        update();\n    }\n    void single_add(D\
    \ x) {\n        v = N::op_dd(v, x);\n        update();\n    }\n\n    void init_node(D\
    \ _v) {\n        v = _v;\n        sm = _v;\n    }\n    void update() {\n     \
    \   sz = 1;\n        if (l) sz += l->sz;\n        if (r) sz += r->sz;\n      \
    \  sm = l ? N::op_dd(l->sm, v) : v;\n        if (r) sm = N::op_dd(sm, r->sm);\n\
    \    }\n    void push() {\n        if (rev) {\n            if (l) l->revdata();\n\
    \            if (r) r->revdata();\n            rev = false;\n        }\n    }\n\
    \    void revdata() {\n        rev ^= true;\n        swap(l, r);\n        sm =\
    \ N::rev(sm);\n    }\n\n    inline int pos() {\n        if (p) {\n           \
    \ if (p->l == this) return -1;\n            if (p->r == this) return 1;\n    \
    \    }\n        return 0;\n    }\n    void rot() {\n        NP q = p->p;\n   \
    \     int pps = p->pos();\n        if (pps == -1) q->l = this;\n        if (pps\
    \ == 1) q->r = this;\n        if (p->l == this) {\n            p->l = r;\n   \
    \         if (r) r->p = p;\n            r = p;\n        } else {\n           \
    \ p->r = l;\n            if (l) l->p = p;\n            l = p;\n        }\n   \
    \     p->p = this;\n        p->update();\n        update();\n        p = q;\n\
    \        if (q) q->update();\n    }\n    void all_push() {\n        if (pos())\
    \ p->all_push();\n        push();\n    }\n    void splay() {\n        all_push();\n\
    \        int ps;\n        while ((ps = pos())) {\n            int pps = p->pos();\n\
    \            if (!pps) {\n                rot();\n            } else if (ps ==\
    \ pps) {\n                p->rot();\n                rot();\n            } else\
    \ {\n                rot();\n                rot();\n            }\n        }\n\
    \    }\n    void expose() {\n        NP u = this, ur = nullptr;\n        do {\n\
    \            u->splay();\n            u->r = ur;\n            u->update();\n \
    \           ur = u;\n        } while ((u = u->p));\n        splay();\n    }\n\
    \    // \u89AA\u3068\u3057\u3066np\u3092\u63A5\u7D9A\u3059\u308B\n    void link(NP\
    \ np) {\n        evert();\n        np->expose();\n        p = np;\n    }\n   \
    \ // \u89AA\u304B\u3089\u81EA\u5206\u3092\u5207\u308A\u96E2\u3059\n    void cut()\
    \ {\n        expose();\n        assert(l);\n        l->p = nullptr;\n        l\
    \ = nullptr;\n        update();\n    }\n    void evert() {\n        expose();\n\
    \        revdata();\n    }\n\n    NP lca(NP n) {\n        n->expose();\n     \
    \   expose();\n        NP t = n;\n        while (n->p != nullptr) {\n        \
    \    if (!n->pos()) t = n->p;\n            n = n->p;\n        }\n        return\
    \ (this == n) ? t : nullptr;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/linkcuttree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/lctree_vertex_add_path_sum.test.cpp
  - src/lctree_lca.test.cpp
documentation_of: src/datastructure/linkcuttree.hpp
layout: document
redirect_from:
- /library/src/datastructure/linkcuttree.hpp
- /library/src/datastructure/linkcuttree.hpp.html
title: src/datastructure/linkcuttree.hpp
---
