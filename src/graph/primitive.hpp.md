---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/graph/balancedseparator.hpp
    title: src/graph/balancedseparator.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/treedecomp.hpp
    title: src/graph/treedecomp.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/graph/primitive.hpp\"\n\nstruct SimpleEdge {\n    int\
    \ to;\n};\nostream& operator<<(ostream& os, const SimpleEdge& e) {\n    return\
    \ os << \"E(\" << e.to << \")\";\n}\n"
  code: "#pragma once\n\nstruct SimpleEdge {\n    int to;\n};\nostream& operator<<(ostream&\
    \ os, const SimpleEdge& e) {\n    return os << \"E(\" << e.to << \")\";\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/primitive.hpp
  requiredBy:
  - src/graph/balancedseparator.hpp
  - src/graph/treedecomp.hpp
  timestamp: '2020-05-26 02:54:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/treedecomp_width2.test.cpp
documentation_of: src/graph/primitive.hpp
layout: document
redirect_from:
- /library/src/graph/primitive.hpp
- /library/src/graph/primitive.hpp.html
title: src/graph/primitive.hpp
---
