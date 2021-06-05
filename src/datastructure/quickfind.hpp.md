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
  bundledCode: "#line 1 \"src/datastructure/quickfind.hpp\"\nstruct QuickFind {\n\
    \    V<int> id;\n    VV<int> groups;\n    int gc;  // group count\n    QuickFind(int\
    \ n = 0) {\n        id = V<int>(n);\n        groups = VV<int>(n);\n        for\
    \ (int i = 0; i < n; i++) {\n            id[i] = i;\n            groups[i] = {i};\n\
    \        }\n        gc = n;\n    }\n    void merge(int a, int b) {\n        if\
    \ (same(a, b)) return;\n        gc--;\n        int x = id[a], y = id[b];\n   \
    \     if (groups[x].size() < groups[y].size()) swap(x, y);\n        for (int j\
    \ : groups[y]) {\n            id[j] = x;\n            groups[x].push_back(j);\n\
    \        }\n        groups[y].clear();\n    }\n    bool same(int a, int b) { return\
    \ id[a] == id[b]; }\n};\n"
  code: "struct QuickFind {\n    V<int> id;\n    VV<int> groups;\n    int gc;  //\
    \ group count\n    QuickFind(int n = 0) {\n        id = V<int>(n);\n        groups\
    \ = VV<int>(n);\n        for (int i = 0; i < n; i++) {\n            id[i] = i;\n\
    \            groups[i] = {i};\n        }\n        gc = n;\n    }\n    void merge(int\
    \ a, int b) {\n        if (same(a, b)) return;\n        gc--;\n        int x =\
    \ id[a], y = id[b];\n        if (groups[x].size() < groups[y].size()) swap(x,\
    \ y);\n        for (int j : groups[y]) {\n            id[j] = x;\n           \
    \ groups[x].push_back(j);\n        }\n        groups[y].clear();\n    }\n    bool\
    \ same(int a, int b) { return id[a] == id[b]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/quickfind.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/quickfind.hpp
layout: document
redirect_from:
- /library/src/datastructure/quickfind.hpp
- /library/src/datastructure/quickfind.hpp.html
title: src/datastructure/quickfind.hpp
---
