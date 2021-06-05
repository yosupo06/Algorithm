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
  bundledCode: "#line 2 \"src/datastructure/smallfind.hpp\"\n\ntemplate <int N> struct\
    \ SmallFind {\n    array<int, N> id;\n    SmallFind() {\n        for (int i =\
    \ 0; i < N; i++) id[i] = i;\n    }\n\n    SmallFind(ull hs) {\n        for (int\
    \ i = 0; i < N; i++) {\n            id[i] = hs & 0xf;\n            hs >>= 4;\n\
    \        }\n    }\n\n    void merge(int x, int y) {\n        int xg = id[x], yg\
    \ = id[y];\n        if (xg == yg) return;\n        for (int i = 0; i < N; i++)\
    \ {\n            if (id[i] == yg) id[i] = xg;\n        }\n    }\n\n    bool same(int\
    \ x, int y) { return id[x] == id[y]; }\n\n    ull uf2hash() {\n        array<int,\
    \ N> b;\n        fill(b.begin(), b.end(), -1);\n        int c = 0;\n        ull\
    \ hs = 0;\n        for (int i = N - 1; i >= 0; i--) {\n            hs <<= 4;\n\
    \            if (b[id[i]] == -1) {\n                b[id[i]] = c++;\n        \
    \    }\n            hs += b[id[i]];\n        }\n        return hs;\n    }\n};\n"
  code: "#pragma once\n\ntemplate <int N> struct SmallFind {\n    array<int, N> id;\n\
    \    SmallFind() {\n        for (int i = 0; i < N; i++) id[i] = i;\n    }\n\n\
    \    SmallFind(ull hs) {\n        for (int i = 0; i < N; i++) {\n            id[i]\
    \ = hs & 0xf;\n            hs >>= 4;\n        }\n    }\n\n    void merge(int x,\
    \ int y) {\n        int xg = id[x], yg = id[y];\n        if (xg == yg) return;\n\
    \        for (int i = 0; i < N; i++) {\n            if (id[i] == yg) id[i] = xg;\n\
    \        }\n    }\n\n    bool same(int x, int y) { return id[x] == id[y]; }\n\n\
    \    ull uf2hash() {\n        array<int, N> b;\n        fill(b.begin(), b.end(),\
    \ -1);\n        int c = 0;\n        ull hs = 0;\n        for (int i = N - 1; i\
    \ >= 0; i--) {\n            hs <<= 4;\n            if (b[id[i]] == -1) {\n   \
    \             b[id[i]] = c++;\n            }\n            hs += b[id[i]];\n  \
    \      }\n        return hs;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/smallfind.hpp
  requiredBy: []
  timestamp: '2020-05-08 22:01:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/smallfind.hpp
layout: document
redirect_from:
- /library/src/datastructure/smallfind.hpp
- /library/src/datastructure/smallfind.hpp.html
title: src/datastructure/smallfind.hpp
---
