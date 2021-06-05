---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/unionfind.test.cpp
    title: src/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/unionfind.hpp\"\nstruct UnionFind {\n\
    \    int n;\n    V<int> p, r;\n    int gn;\n    UnionFind(int _n = 0) : n(_n),\
    \ p(n, -1), r(n, 1), gn(n) {}\n    void merge(int a, int b) {\n        assert(0\
    \ <= a && a < n);\n        assert(0 <= b && b < n);\n        int x = group(a),\
    \ y = group(b);\n        if (x == y) return;  // same\n        gn--;\n       \
    \ if (r[x] < r[y]) swap(x, y);\n        p[y] = x;\n        r[x] += r[y];\n   \
    \ }\n    int group(int a) {\n        assert(0 <= a && a < n);\n        if (p[a]\
    \ == -1) return a;\n        return p[a] = group(p[a]);\n    }\n    bool same(int\
    \ a, int b) {\n        assert(0 <= a && a < n);\n        assert(0 <= b && b <\
    \ n);\n        return group(a) == group(b);\n    }\n};\n"
  code: "struct UnionFind {\n    int n;\n    V<int> p, r;\n    int gn;\n    UnionFind(int\
    \ _n = 0) : n(_n), p(n, -1), r(n, 1), gn(n) {}\n    void merge(int a, int b) {\n\
    \        assert(0 <= a && a < n);\n        assert(0 <= b && b < n);\n        int\
    \ x = group(a), y = group(b);\n        if (x == y) return;  // same\n        gn--;\n\
    \        if (r[x] < r[y]) swap(x, y);\n        p[y] = x;\n        r[x] += r[y];\n\
    \    }\n    int group(int a) {\n        assert(0 <= a && a < n);\n        if (p[a]\
    \ == -1) return a;\n        return p[a] = group(p[a]);\n    }\n    bool same(int\
    \ a, int b) {\n        assert(0 <= a && a < n);\n        assert(0 <= b && b <\
    \ n);\n        return group(a) == group(b);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/unionfind.hpp
  requiredBy: []
  timestamp: '2020-05-26 21:19:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/unionfind.test.cpp
documentation_of: src/datastructure/unionfind.hpp
layout: document
redirect_from:
- /library/src/datastructure/unionfind.hpp
- /library/src/datastructure/unionfind.hpp.html
title: src/datastructure/unionfind.hpp
---
