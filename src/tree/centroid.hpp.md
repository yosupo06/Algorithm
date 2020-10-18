---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/graph/balancedseparator.hpp
    title: src/graph/balancedseparator.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/tree/centroid.hpp\"\n\nstruct Centroid {\n    int r;\n\
    \    VV<int> tr;\n    V<int> par;\n};\n\ntemplate <class E> struct CentroidExec\
    \ : Centroid {\n    int n;\n    const VV<E>& g;\n    V<bool> used;\n\n    using\
    \ P = pair<int, int>;\n    V<P> info;  //(child max, child)\n\n    int dfs(int\
    \ p, int b) {\n        int sz = 1;\n        info[p] = P(0, -1);\n        for (E\
    \ e : g[p]) {\n            int d = e.to;\n            if (d == b || used[d]) continue;\n\
    \            int csz = dfs(d, p);\n            sz += csz;\n            info[p]\
    \ = max(info[p], P(csz, d));\n        }\n        return sz;\n    }\n    int init(int\
    \ p, int b) {\n        int sz = dfs(p, -1);\n        while (info[p].first > sz\
    \ / 2) p = info[p].second;\n        par[p] = b;\n        used[p] = true;\n   \
    \     for (E e : g[p]) {\n            int d = e.to;\n            if (used[d])\
    \ continue;\n            tr[p].push_back(init(d, p));\n        }\n        return\
    \ p;\n    }\n    CentroidExec(const VV<E>& _g) : n(int(_g.size())), g(_g), used(n),\
    \ info(n) {\n        tr = VV<int>(n);\n        par = V<int>(n);\n        r = init(0,\
    \ -1);\n    }\n};\n\ntemplate <class E> Centroid get_centroid(const VV<E>& g)\
    \ {\n    return CentroidExec<E>(g);\n}\n"
  code: "#pragma once\n\nstruct Centroid {\n    int r;\n    VV<int> tr;\n    V<int>\
    \ par;\n};\n\ntemplate <class E> struct CentroidExec : Centroid {\n    int n;\n\
    \    const VV<E>& g;\n    V<bool> used;\n\n    using P = pair<int, int>;\n   \
    \ V<P> info;  //(child max, child)\n\n    int dfs(int p, int b) {\n        int\
    \ sz = 1;\n        info[p] = P(0, -1);\n        for (E e : g[p]) {\n         \
    \   int d = e.to;\n            if (d == b || used[d]) continue;\n            int\
    \ csz = dfs(d, p);\n            sz += csz;\n            info[p] = max(info[p],\
    \ P(csz, d));\n        }\n        return sz;\n    }\n    int init(int p, int b)\
    \ {\n        int sz = dfs(p, -1);\n        while (info[p].first > sz / 2) p =\
    \ info[p].second;\n        par[p] = b;\n        used[p] = true;\n        for (E\
    \ e : g[p]) {\n            int d = e.to;\n            if (used[d]) continue;\n\
    \            tr[p].push_back(init(d, p));\n        }\n        return p;\n    }\n\
    \    CentroidExec(const VV<E>& _g) : n(int(_g.size())), g(_g), used(n), info(n)\
    \ {\n        tr = VV<int>(n);\n        par = V<int>(n);\n        r = init(0, -1);\n\
    \    }\n};\n\ntemplate <class E> Centroid get_centroid(const VV<E>& g) {\n   \
    \ return CentroidExec<E>(g);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/tree/centroid.hpp
  requiredBy:
  - src/graph/balancedseparator.hpp
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/tree/centroid.hpp
layout: document
redirect_from:
- /library/src/tree/centroid.hpp
- /library/src/tree/centroid.hpp.html
title: src/tree/centroid.hpp
---
