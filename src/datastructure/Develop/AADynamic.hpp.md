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
  bundledCode: "#line 1 \"src/datastructure/Develop/AADynamic.hpp\"\nstruct AA {\n\
    \    using NP = AA*;\n\n    int ma, lz;\n    void init_node() {\n        ma =\
    \ lz = 0;\n    }\n    void update() {\n        assert(!lz);\n        sz = l->sz\
    \ + r->sz;\n        ma = max(l->ma, r->ma);\n    }\n    void push() {\n      \
    \  assert(l && r);\n        assert(l->sz && r->sz);\n        if (lz) {\n     \
    \       l->lzdata(lz);\n            r->lzdata(lz);\n            lz = 0;\n    \
    \    }\n    }\n    void lzdata(int x) {\n        ma += x;\n        lz += x;\n\
    \    }\n    void add(int a, int b, int x) {\n        if (b <= 0 || sz <= a) return;\n\
    \        if (a <= 0 && sz <= b) {\n            lzdata(x);\n            return;\n\
    \        }\n        push();\n        l->add(a, b, x);\n        r->add(a - l->sz,\
    \ b - l->sz, x);\n        update();\n    }\n    int get(int a, int b) {\n    \
    \    if (b <= 0 || sz <= a) return -1;\n        if (a <= 0 && sz <= b) {\n   \
    \         return ma;\n        }\n        push();\n        return max(l->get(a,\
    \ b), r->get(a - l->sz, b - l->sz));\n    }\n\n    NP l, r;\n    int sz; int lv;\n\
    \    bool isL; // is last\n    AA(int sz) : l(nullptr), r(nullptr), sz(sz), lv(0),\
    \ isL(true) {\n        init_node();\n    }    \n    static NP make_child(NP n,\
    \ int k) {\n        n->l = new AA(k); n->r = new AA(n->sz - k);\n        n->lv\
    \ = 1;\n        n->isL = false;\n        n->push();\n        return n;\n    }\n\
    \    static NP skew(NP n) {\n        if (n->l == nullptr || n->lv != n->l->lv)\
    \ return n;\n        NP L = n->l;\n        n->l = L->r;\n        n->update();\n\
    \        L->r = n;\n        L->update();\n        return L;\n    }\n    static\
    \ NP pull(NP n) {\n        if (n->r == nullptr || n->lv != n->r->lv) return n;\n\
    \        if (n->r->r == nullptr || n->lv != n->r->r->lv) return n;\n        NP\
    \ R = n->r;\n        n->r = R->l;\n        n->update();\n        R->l = n;\n \
    \       R->lv++;\n        R->update();\n        return R;\n    }\n    static NP\
    \ inscut(NP n, int k) {\n        if (k == 0 || k == n->sz) return n;\n       \
    \ if (n->isL) {\n            return make_child(n, k);\n        }\n        n->push();\n\
    \        if (k <= n->l->sz) {\n            n->l = inscut(n->l, k);\n         \
    \   n->update();\n            return pull(skew(n));\n        } else {\n      \
    \      n->r = inscut(n->r, k - n->l->sz);\n            n->update();\n        \
    \    return pull(skew(n));\n        }\n    }\n};\n"
  code: "struct AA {\n    using NP = AA*;\n\n    int ma, lz;\n    void init_node()\
    \ {\n        ma = lz = 0;\n    }\n    void update() {\n        assert(!lz);\n\
    \        sz = l->sz + r->sz;\n        ma = max(l->ma, r->ma);\n    }\n    void\
    \ push() {\n        assert(l && r);\n        assert(l->sz && r->sz);\n       \
    \ if (lz) {\n            l->lzdata(lz);\n            r->lzdata(lz);\n        \
    \    lz = 0;\n        }\n    }\n    void lzdata(int x) {\n        ma += x;\n \
    \       lz += x;\n    }\n    void add(int a, int b, int x) {\n        if (b <=\
    \ 0 || sz <= a) return;\n        if (a <= 0 && sz <= b) {\n            lzdata(x);\n\
    \            return;\n        }\n        push();\n        l->add(a, b, x);\n \
    \       r->add(a - l->sz, b - l->sz, x);\n        update();\n    }\n    int get(int\
    \ a, int b) {\n        if (b <= 0 || sz <= a) return -1;\n        if (a <= 0 &&\
    \ sz <= b) {\n            return ma;\n        }\n        push();\n        return\
    \ max(l->get(a, b), r->get(a - l->sz, b - l->sz));\n    }\n\n    NP l, r;\n  \
    \  int sz; int lv;\n    bool isL; // is last\n    AA(int sz) : l(nullptr), r(nullptr),\
    \ sz(sz), lv(0), isL(true) {\n        init_node();\n    }    \n    static NP make_child(NP\
    \ n, int k) {\n        n->l = new AA(k); n->r = new AA(n->sz - k);\n        n->lv\
    \ = 1;\n        n->isL = false;\n        n->push();\n        return n;\n    }\n\
    \    static NP skew(NP n) {\n        if (n->l == nullptr || n->lv != n->l->lv)\
    \ return n;\n        NP L = n->l;\n        n->l = L->r;\n        n->update();\n\
    \        L->r = n;\n        L->update();\n        return L;\n    }\n    static\
    \ NP pull(NP n) {\n        if (n->r == nullptr || n->lv != n->r->lv) return n;\n\
    \        if (n->r->r == nullptr || n->lv != n->r->r->lv) return n;\n        NP\
    \ R = n->r;\n        n->r = R->l;\n        n->update();\n        R->l = n;\n \
    \       R->lv++;\n        R->update();\n        return R;\n    }\n    static NP\
    \ inscut(NP n, int k) {\n        if (k == 0 || k == n->sz) return n;\n       \
    \ if (n->isL) {\n            return make_child(n, k);\n        }\n        n->push();\n\
    \        if (k <= n->l->sz) {\n            n->l = inscut(n->l, k);\n         \
    \   n->update();\n            return pull(skew(n));\n        } else {\n      \
    \      n->r = inscut(n->r, k - n->l->sz);\n            n->update();\n        \
    \    return pull(skew(n));\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/AADynamic.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/AADynamic.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/AADynamic.hpp
- /library/src/datastructure/Develop/AADynamic.hpp.html
title: src/datastructure/Develop/AADynamic.hpp
---
