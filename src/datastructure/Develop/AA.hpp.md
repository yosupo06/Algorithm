---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/AA.hpp\"\nstruct AA {\n\tusing\
    \ NP = AA*;\n\tint ma;\n\tNP l, r;\n\tint sz, lv;\n\tAA(int ma) : l(nullptr),\
    \ r(nullptr), sz(1), lv(0), ma(ma) {}\n\tAA(NP l, NP r, int lv) : l(l), r(r),\
    \ lv(lv) {\n\t\tupdate();\n\t}\n\tvoid update() {\n\t\tsz = l->sz + r->sz;\n\t\
    \tma = max(l->ma, r->ma);\n\t}\n\tstatic NP skew(NP n) {\n\t\tif (n->l == nullptr\
    \ || n->lv != n->l->lv) return n;\n\t\tNP L = n->l;\n\t\tn->l = L->r;\n\t\tn->update();\n\
    \t\tL->r = n;\n\t\tL->update();\n\t\treturn L;\n\t}\n\tstatic NP pull(NP n) {\n\
    \t\tif (n->r == nullptr || n->lv != n->r->lv) return n;\n\t\tif (n->r->r == nullptr\
    \ || n->lv != n->r->r->lv) return n;\n\t\tNP R = n->r;\n\t\tn->r = R->l;\n\t\t\
    n->update();\n\t\tR->l = n;\n\t\tR->lv++;\n\t\tR->update();\n\t\treturn R;\n\t\
    }\n\tstatic NP merge(NP l, NP r) {\n\t\tif (l == nullptr) return r;\n\t\tif (r\
    \ == nullptr) return l;\n\t\tif (l->lv == r->lv) {\n\t\t\treturn new AA(l, r,\
    \ l->lv+1);\n\t\t}\n\t\tif (l->lv < r->lv) {\n\t\t\tr->l = merge(l, r->l);\n\t\
    \t\tr->update();\n\t\t\treturn pull(skew(r));\n\t\t} else {\n\t\t\tl->r = merge(l->r,\
    \ r);\n\t\t\tl->update();\n\t\t\treturn pull(skew(l));\n\t\t}\n\t}\n\tstatic pair<NP,\
    \ NP> split(NP n, int k) {\n\t\tif (n == nullptr) return pair<NP, NP>(nullptr,\
    \ nullptr);\n\t\tif (n->sz == 1) {\n\t\t\tif (k == 0) return pair<NP, NP>(nullptr,\
    \ n);\n\t\t\telse return pair<NP, NP>(n, nullptr);\n\t\t}\n\t\tpair<NP, NP> m;\n\
    \t\tif (k <= n->l->sz) {\n\t\t\tm = split(n->l, k);\n\t\t\tm.second = merge(m.second,\
    \ n->r);\n\t\t} else {\n\t\t\tm = split(n->r, k - n->l->sz);\n\t\t\tm.first =\
    \ merge(n->l, m.first);\n\t\t}\n\t\tdelete n;\n\t\treturn m;\n\t}\n\tstatic NP\
    \ insert(NP n, int k, NP m) {\n\t\tif (n == nullptr) return m;\n\t\tif (n->sz\
    \ == 1) {\n\t\t\tif (k == 0) return new AA(m, n, 1);\n\t\t\telse return new AA(n,\
    \ m, 1);\n\t\t}\n\t\tif (k <= n->l->sz) {\n\t\t\tn->l = insert(n->l, k, m);\n\t\
    \t\tn->update();\n\t\t\treturn pull(skew(n));\n\t\t} else {\n\t\t\tn->r = insert(n->r,\
    \ k - n->l->sz, m);\n\t\t\tn->update();\n\t\t\treturn pull(skew(n));\n\t\t}\n\t\
    }\n\tstatic NP remove(NP n, int k) {\n\t\tif (n->sz == 1) {\n\t\t\tdelete n;\n\
    \t\t\treturn nullptr;\n\t\t}\n\t\tNP m;\n\t\tif (k < n->l->sz) {\n\t\t\tm = merge(remove(n->l,\
    \ k), n->r);\n\t\t} else {\n\t\t\tm = merge(n->l, remove(n->r, k - n->l->sz));\n\
    \t\t}\n\t\tdelete n;\n\t\treturn m;\n\t}\n};\n"
  code: "struct AA {\n\tusing NP = AA*;\n\tint ma;\n\tNP l, r;\n\tint sz, lv;\n\t\
    AA(int ma) : l(nullptr), r(nullptr), sz(1), lv(0), ma(ma) {}\n\tAA(NP l, NP r,\
    \ int lv) : l(l), r(r), lv(lv) {\n\t\tupdate();\n\t}\n\tvoid update() {\n\t\t\
    sz = l->sz + r->sz;\n\t\tma = max(l->ma, r->ma);\n\t}\n\tstatic NP skew(NP n)\
    \ {\n\t\tif (n->l == nullptr || n->lv != n->l->lv) return n;\n\t\tNP L = n->l;\n\
    \t\tn->l = L->r;\n\t\tn->update();\n\t\tL->r = n;\n\t\tL->update();\n\t\treturn\
    \ L;\n\t}\n\tstatic NP pull(NP n) {\n\t\tif (n->r == nullptr || n->lv != n->r->lv)\
    \ return n;\n\t\tif (n->r->r == nullptr || n->lv != n->r->r->lv) return n;\n\t\
    \tNP R = n->r;\n\t\tn->r = R->l;\n\t\tn->update();\n\t\tR->l = n;\n\t\tR->lv++;\n\
    \t\tR->update();\n\t\treturn R;\n\t}\n\tstatic NP merge(NP l, NP r) {\n\t\tif\
    \ (l == nullptr) return r;\n\t\tif (r == nullptr) return l;\n\t\tif (l->lv ==\
    \ r->lv) {\n\t\t\treturn new AA(l, r, l->lv+1);\n\t\t}\n\t\tif (l->lv < r->lv)\
    \ {\n\t\t\tr->l = merge(l, r->l);\n\t\t\tr->update();\n\t\t\treturn pull(skew(r));\n\
    \t\t} else {\n\t\t\tl->r = merge(l->r, r);\n\t\t\tl->update();\n\t\t\treturn pull(skew(l));\n\
    \t\t}\n\t}\n\tstatic pair<NP, NP> split(NP n, int k) {\n\t\tif (n == nullptr)\
    \ return pair<NP, NP>(nullptr, nullptr);\n\t\tif (n->sz == 1) {\n\t\t\tif (k ==\
    \ 0) return pair<NP, NP>(nullptr, n);\n\t\t\telse return pair<NP, NP>(n, nullptr);\n\
    \t\t}\n\t\tpair<NP, NP> m;\n\t\tif (k <= n->l->sz) {\n\t\t\tm = split(n->l, k);\n\
    \t\t\tm.second = merge(m.second, n->r);\n\t\t} else {\n\t\t\tm = split(n->r, k\
    \ - n->l->sz);\n\t\t\tm.first = merge(n->l, m.first);\n\t\t}\n\t\tdelete n;\n\t\
    \treturn m;\n\t}\n\tstatic NP insert(NP n, int k, NP m) {\n\t\tif (n == nullptr)\
    \ return m;\n\t\tif (n->sz == 1) {\n\t\t\tif (k == 0) return new AA(m, n, 1);\n\
    \t\t\telse return new AA(n, m, 1);\n\t\t}\n\t\tif (k <= n->l->sz) {\n\t\t\tn->l\
    \ = insert(n->l, k, m);\n\t\t\tn->update();\n\t\t\treturn pull(skew(n));\n\t\t\
    } else {\n\t\t\tn->r = insert(n->r, k - n->l->sz, m);\n\t\t\tn->update();\n\t\t\
    \treturn pull(skew(n));\n\t\t}\n\t}\n\tstatic NP remove(NP n, int k) {\n\t\tif\
    \ (n->sz == 1) {\n\t\t\tdelete n;\n\t\t\treturn nullptr;\n\t\t}\n\t\tNP m;\n\t\
    \tif (k < n->l->sz) {\n\t\t\tm = merge(remove(n->l, k), n->r);\n\t\t} else {\n\
    \t\t\tm = merge(n->l, remove(n->r, k - n->l->sz));\n\t\t}\n\t\tdelete n;\n\t\t\
    return m;\n\t}\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/AA.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/AA.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/AA.hpp
- /library/src/datastructure/Develop/AA.hpp.html
title: src/datastructure/Develop/AA.hpp
---
