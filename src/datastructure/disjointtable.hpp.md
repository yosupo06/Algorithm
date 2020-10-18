---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/disjointtable.hpp\"\ntemplate <class D,\
    \ class OP> struct DisjointTable {\n    D e;\n    OP op;\n    VV<D> data;\n  \
    \  DisjointTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op)\
    \ {\n        int lg = 1;\n        while ((1 << lg) < int(v.size())) lg++;\n  \
    \      int n = 1 << lg;\n        v.resize(n, e);\n        data = VV<D>(lg, V<D>(n));\n\
    \        data[0] = v;\n        for (int h = 1; h < lg; h++) {\n            int\
    \ u = (1 << h);\n            for (int i = 0; i < n / (2 * u); i++) {\n       \
    \         int base = i * (2 * u) + u;\n                D res;\n              \
    \  res = e;\n                for (int j = base - 1; j >= base - u; j--) {\n  \
    \                  res = op(v[j], res);\n                    data[h][j] = res;\n\
    \                }\n                res = e;\n                for (int j = base;\
    \ j < base + u; j++) {\n                    res = op(res, v[j]);\n           \
    \         data[h][j] = res;\n                }\n            }\n        }\n   \
    \ }\n    D query(int l, int r) {\n        r--;\n        if (l > r) return e;\n\
    \        if (l == r) return data[0][l];\n        int u = bsr(uint(l ^ r));\n \
    \       return op(data[u][l], data[u][r]);\n    }\n};\n\ntemplate <class D, class\
    \ OP>\nDisjointTable<D, OP> get_disjoint_table(V<D> v, D e, OP op) {\n    return\
    \ DisjointTable<D, OP>(v, e, op);\n}\n"
  code: "template <class D, class OP> struct DisjointTable {\n    D e;\n    OP op;\n\
    \    VV<D> data;\n    DisjointTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())\
    \ : e(_e), op(_op) {\n        int lg = 1;\n        while ((1 << lg) < int(v.size()))\
    \ lg++;\n        int n = 1 << lg;\n        v.resize(n, e);\n        data = VV<D>(lg,\
    \ V<D>(n));\n        data[0] = v;\n        for (int h = 1; h < lg; h++) {\n  \
    \          int u = (1 << h);\n            for (int i = 0; i < n / (2 * u); i++)\
    \ {\n                int base = i * (2 * u) + u;\n                D res;\n   \
    \             res = e;\n                for (int j = base - 1; j >= base - u;\
    \ j--) {\n                    res = op(v[j], res);\n                    data[h][j]\
    \ = res;\n                }\n                res = e;\n                for (int\
    \ j = base; j < base + u; j++) {\n                    res = op(res, v[j]);\n \
    \                   data[h][j] = res;\n                }\n            }\n    \
    \    }\n    }\n    D query(int l, int r) {\n        r--;\n        if (l > r) return\
    \ e;\n        if (l == r) return data[0][l];\n        int u = bsr(uint(l ^ r));\n\
    \        return op(data[u][l], data[u][r]);\n    }\n};\n\ntemplate <class D, class\
    \ OP>\nDisjointTable<D, OP> get_disjoint_table(V<D> v, D e, OP op) {\n    return\
    \ DisjointTable<D, OP>(v, e, op);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/disjointtable.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/disjointtable.hpp
layout: document
redirect_from:
- /library/src/datastructure/disjointtable.hpp
- /library/src/datastructure/disjointtable.hpp.html
title: src/datastructure/disjointtable.hpp
---
