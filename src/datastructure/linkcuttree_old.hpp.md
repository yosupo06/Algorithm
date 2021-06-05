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
  bundledCode: "#line 1 \"src/datastructure/linkcuttree_old.hpp\"\nstruct LCNode {\n\
    \    using NP = LCNode*;\n    static NP last;\n    ll d, dsm, ma;\n    ll lz;\n\
    \    NP init_last() {\n        sz = 0; // Important\n        lz = 0; // Important\n\
    \        d = dsm = ma = 0;\n        return this;\n    }\n    void init_node(int\
    \ d) {\n        sz = 1; rev = false; // Important\n        lz = 0; // Important\n\
    \        this->d = dsm = ma = d;\n    }\n    void update() {\n        sz = 1 +\
    \ l->sz + r->sz; // Important\n        dsm = d + l->dsm + r->dsm;\n        ma\
    \ = max(d, max(l->ma, r->ma));\n    }\n    void push() {\n        assert(this\
    \ != last);\n        if (rev) { // Important\n            if (l != last) {\n \
    \               l->revdata();\n            }\n            if (r != last) {\n \
    \               r->revdata();\n            }\n            rev = false;\n     \
    \   }\n        if (lz) {\n            if (l != last) {\n                l->lzdata(lz);\n\
    \            }\n            if (r != last) {\n                r->lzdata(lz);\n\
    \            }\n            lz = 0;\n        }\n    }\n    void revdata() {\n\
    \        rev ^= true; swap(l, r); // Important\n    }\n    void lzdata(ll x) {\n\
    \        d += x;\n        dsm += x;\n        ma += x;\n        lz += x;\n    }\n\
    \    \n    NP p, l, r;\n    int sz;\n    bool rev;\n    LCNode() : p(nullptr),\
    \ l(last), r(last) {}\n    inline int pos() {\n        if (p) {\n            if\
    \ (p->l == this) return -1;\n            if (p->r == this) return 1;\n       \
    \ }\n        return 0;\n    }\n    void rot() {\n        NP q = p->p;\n      \
    \  int pps = p->pos();\n        if (pps == -1) q->l = this;\n        if (pps ==\
    \ 1) q->r = this;\n        if (p->l == this) {\n            p->l = r;\n      \
    \      if (r) r->p = p;\n            r = p;\n        } else {\n            p->r\
    \ = l;\n            if (l) l->p = p;\n            l = p;\n        }\n        p->p\
    \ = this;\n        p->update(); update();\n        p = q;\n        if (q) q->update();\n\
    \    }\n    void splay() {\n        supush();\n        int ps;\n        while\
    \ ((ps = pos())) {\n            int pps = p->pos();\n            if (!pps) {\n\
    \                rot();\n            } else if (ps == pps) {\n               \
    \ p->rot(); rot();\n            } else {\n                rot(); rot();\n    \
    \        }\n        }\n    }\n    void expose() {\n        assert(this != last);\n\
    \        NP u = this, ur = last;\n        do {\n            u->splay();\n    \
    \        u->r = ur;\n            u->update();\n            ur = u;\n        }\
    \ while ((u = u->p));\n        splay();\n    }\n    void supush() {\n        if\
    \ (pos()) p->supush();\n        push();\n    }\n    void link(NP r) {\n      \
    \  evert(); r->expose();\n        p = r;\n    }\n    void cut() {\n        expose();\n\
    \        l->p = NULL;\n        l = last;\n        update();\n    }\n    void evert()\
    \ {\n        expose(); revdata();\n    }\n\n    //tree func\n    NP parent() {\n\
    \        expose();\n        NP u = this->l;\n        if (u == last) return last;\n\
    \        u->push();\n        while (u->r != last) {\n            u = u->r;\n \
    \           u->push();\n        }\n        u->expose();\n        return u;\n \
    \   }\n\n    NP root() {\n        expose();\n        NP u = this;\n        while\
    \ (u->l != last) {\n            u = u->l;\n            u->push();\n        }\n\
    \        u->expose();\n        return u;\n    }\n\n\n    NP lca(NP n) {\n    \
    \    n->expose();\n        expose();\n        NP t = n;\n        while (n->p !=\
    \ nullptr) {\n            if (!n->pos()) t = n->p;\n            n = n->p;\n  \
    \      }\n        return (this == n) ? t : nullptr;\n    }\n};\nLCNode::NP LCNode::last\
    \ = (new LCNode())->init_last();\n"
  code: "struct LCNode {\n    using NP = LCNode*;\n    static NP last;\n    ll d,\
    \ dsm, ma;\n    ll lz;\n    NP init_last() {\n        sz = 0; // Important\n \
    \       lz = 0; // Important\n        d = dsm = ma = 0;\n        return this;\n\
    \    }\n    void init_node(int d) {\n        sz = 1; rev = false; // Important\n\
    \        lz = 0; // Important\n        this->d = dsm = ma = d;\n    }\n    void\
    \ update() {\n        sz = 1 + l->sz + r->sz; // Important\n        dsm = d +\
    \ l->dsm + r->dsm;\n        ma = max(d, max(l->ma, r->ma));\n    }\n    void push()\
    \ {\n        assert(this != last);\n        if (rev) { // Important\n        \
    \    if (l != last) {\n                l->revdata();\n            }\n        \
    \    if (r != last) {\n                r->revdata();\n            }\n        \
    \    rev = false;\n        }\n        if (lz) {\n            if (l != last) {\n\
    \                l->lzdata(lz);\n            }\n            if (r != last) {\n\
    \                r->lzdata(lz);\n            }\n            lz = 0;\n        }\n\
    \    }\n    void revdata() {\n        rev ^= true; swap(l, r); // Important\n\
    \    }\n    void lzdata(ll x) {\n        d += x;\n        dsm += x;\n        ma\
    \ += x;\n        lz += x;\n    }\n    \n    NP p, l, r;\n    int sz;\n    bool\
    \ rev;\n    LCNode() : p(nullptr), l(last), r(last) {}\n    inline int pos() {\n\
    \        if (p) {\n            if (p->l == this) return -1;\n            if (p->r\
    \ == this) return 1;\n        }\n        return 0;\n    }\n    void rot() {\n\
    \        NP q = p->p;\n        int pps = p->pos();\n        if (pps == -1) q->l\
    \ = this;\n        if (pps == 1) q->r = this;\n        if (p->l == this) {\n \
    \           p->l = r;\n            if (r) r->p = p;\n            r = p;\n    \
    \    } else {\n            p->r = l;\n            if (l) l->p = p;\n         \
    \   l = p;\n        }\n        p->p = this;\n        p->update(); update();\n\
    \        p = q;\n        if (q) q->update();\n    }\n    void splay() {\n    \
    \    supush();\n        int ps;\n        while ((ps = pos())) {\n            int\
    \ pps = p->pos();\n            if (!pps) {\n                rot();\n         \
    \   } else if (ps == pps) {\n                p->rot(); rot();\n            } else\
    \ {\n                rot(); rot();\n            }\n        }\n    }\n    void\
    \ expose() {\n        assert(this != last);\n        NP u = this, ur = last;\n\
    \        do {\n            u->splay();\n            u->r = ur;\n            u->update();\n\
    \            ur = u;\n        } while ((u = u->p));\n        splay();\n    }\n\
    \    void supush() {\n        if (pos()) p->supush();\n        push();\n    }\n\
    \    void link(NP r) {\n        evert(); r->expose();\n        p = r;\n    }\n\
    \    void cut() {\n        expose();\n        l->p = NULL;\n        l = last;\n\
    \        update();\n    }\n    void evert() {\n        expose(); revdata();\n\
    \    }\n\n    //tree func\n    NP parent() {\n        expose();\n        NP u\
    \ = this->l;\n        if (u == last) return last;\n        u->push();\n      \
    \  while (u->r != last) {\n            u = u->r;\n            u->push();\n   \
    \     }\n        u->expose();\n        return u;\n    }\n\n    NP root() {\n \
    \       expose();\n        NP u = this;\n        while (u->l != last) {\n    \
    \        u = u->l;\n            u->push();\n        }\n        u->expose();\n\
    \        return u;\n    }\n\n\n    NP lca(NP n) {\n        n->expose();\n    \
    \    expose();\n        NP t = n;\n        while (n->p != nullptr) {\n       \
    \     if (!n->pos()) t = n->p;\n            n = n->p;\n        }\n        return\
    \ (this == n) ? t : nullptr;\n    }\n};\nLCNode::NP LCNode::last = (new LCNode())->init_last();\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/linkcuttree_old.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/linkcuttree_old.hpp
layout: document
redirect_from:
- /library/src/datastructure/linkcuttree_old.hpp
- /library/src/datastructure/linkcuttree_old.hpp.html
title: src/datastructure/linkcuttree_old.hpp
---
