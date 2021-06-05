---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/graph/bimaching.hpp
    title: src/graph/bimaching.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/bimaching.test.cpp
    title: src/bimaching.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/graph/csr.hpp\"\n\nstruct CSR {\n    V<int> to, start;\n\
    \    CSR() {}\n    CSR(int n, const V<pair<int, int>>& edges) {\n        start\
    \ = V<int>(n + 1);\n        for (auto e : edges) {\n            start[e.first]++;\n\
    \        }\n        for (int i = 1; i <= n; i++) {\n            start[i] += start[i\
    \ - 1];\n        }\n        to = V<int>(start.back());\n        for (auto e :\
    \ edges) {\n            to[start[e.first] - 1] = e.second;\n            start[e.first]--;\n\
    \        }\n    }\n};\n"
  code: "#pragma once\n\nstruct CSR {\n    V<int> to, start;\n    CSR() {}\n    CSR(int\
    \ n, const V<pair<int, int>>& edges) {\n        start = V<int>(n + 1);\n     \
    \   for (auto e : edges) {\n            start[e.first]++;\n        }\n       \
    \ for (int i = 1; i <= n; i++) {\n            start[i] += start[i - 1];\n    \
    \    }\n        to = V<int>(start.back());\n        for (auto e : edges) {\n \
    \           to[start[e.first] - 1] = e.second;\n            start[e.first]--;\n\
    \        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/csr.hpp
  requiredBy:
  - src/graph/bimaching.hpp
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/bimaching.test.cpp
documentation_of: src/graph/csr.hpp
layout: document
redirect_from:
- /library/src/graph/csr.hpp
- /library/src/graph/csr.hpp.html
title: src/graph/csr.hpp
---
