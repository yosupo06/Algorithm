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
  bundledCode: "#line 1 \"src/graph/articulation.hpp\"\nstruct Articulation {\n  \
    \  VV<int> tr;\n};\n\ntemplate <class E> struct ArticulationExec : Articulation\
    \ {\n    const VV<E>& g;\n    int n;\n    int ordc = 0;\n    V<int> low, ord;\n\
    \    V<int> used;\n    AriticulationExec(const VV<E>& _g)\n            : g(_g),\
    \ n(int(g.size())), low(n), ord(n), used(n) {\n        tr = VV<int>(n);\n    \
    \    for (int i = 0; i < n; i++) {\n            if (used[i]) continue;\n     \
    \       dfs1(i, -1);\n            dfs2(i, -1);\n        }\n    }\n    void dfs1(int\
    \ p, int b) {\n        used[p] = 1;\n        low[p] = ord[p] = ordc++;\n     \
    \   bool rt = true;\n        for (auto e : g[p]) {\n            int d = e.to;\n\
    \            if (rt && d == b) {\n                rt = false;\n              \
    \  continue;\n            }\n            if (!used[d]) {\n                dfs1(d,\
    \ p);\n                low[p] = min(low[p], low[d]);\n            } else {\n \
    \               low[p] = min(low[p], ord[d]);\n            }\n        }\n    }\n\
    \    void dfs2(int p, int bid = -1) {\n        used[p] = 2;\n        if (bid !=\
    \ -1) {\n            tr[p].push_back(bid);\n            tr[bid].push_back(p);\n\
    \        }\n        for (auto e: g[p]) {\n            int d = e.to;\n        \
    \    if (used[d] == 2) continue;\n            if (low[d] < ord[p]) {\n       \
    \         dfs2(d, bid);\n                continue;\n            }\n          \
    \  int nid = int(tr.size());\n            tr.push_back({});\n            tr[p].push_back(nid);\n\
    \            tr[nid].push_back(p);\n            dfs2(d, nid);\n        }\n   \
    \ }\n};\n\ntemplate <class E> Articulation get_articulation(const VV<E>& g) {\n\
    \    return ArticulationExec<E>(g);\n}\n"
  code: "struct Articulation {\n    VV<int> tr;\n};\n\ntemplate <class E> struct ArticulationExec\
    \ : Articulation {\n    const VV<E>& g;\n    int n;\n    int ordc = 0;\n    V<int>\
    \ low, ord;\n    V<int> used;\n    AriticulationExec(const VV<E>& _g)\n      \
    \      : g(_g), n(int(g.size())), low(n), ord(n), used(n) {\n        tr = VV<int>(n);\n\
    \        for (int i = 0; i < n; i++) {\n            if (used[i]) continue;\n \
    \           dfs1(i, -1);\n            dfs2(i, -1);\n        }\n    }\n    void\
    \ dfs1(int p, int b) {\n        used[p] = 1;\n        low[p] = ord[p] = ordc++;\n\
    \        bool rt = true;\n        for (auto e : g[p]) {\n            int d = e.to;\n\
    \            if (rt && d == b) {\n                rt = false;\n              \
    \  continue;\n            }\n            if (!used[d]) {\n                dfs1(d,\
    \ p);\n                low[p] = min(low[p], low[d]);\n            } else {\n \
    \               low[p] = min(low[p], ord[d]);\n            }\n        }\n    }\n\
    \    void dfs2(int p, int bid = -1) {\n        used[p] = 2;\n        if (bid !=\
    \ -1) {\n            tr[p].push_back(bid);\n            tr[bid].push_back(p);\n\
    \        }\n        for (auto e: g[p]) {\n            int d = e.to;\n        \
    \    if (used[d] == 2) continue;\n            if (low[d] < ord[p]) {\n       \
    \         dfs2(d, bid);\n                continue;\n            }\n          \
    \  int nid = int(tr.size());\n            tr.push_back({});\n            tr[p].push_back(nid);\n\
    \            tr[nid].push_back(p);\n            dfs2(d, nid);\n        }\n   \
    \ }\n};\n\ntemplate <class E> Articulation get_articulation(const VV<E>& g) {\n\
    \    return ArticulationExec<E>(g);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/articulation.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/articulation.hpp
layout: document
redirect_from:
- /library/src/graph/articulation.hpp
- /library/src/graph/articulation.hpp.html
title: src/graph/articulation.hpp
---
