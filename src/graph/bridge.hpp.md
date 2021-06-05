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
  bundledCode: "#line 1 \"src/graph/bridge.hpp\"\nstruct Bridge {\n    V<int> id;\n\
    \    VV<int> groups;\n    VV<int> tr;\n};\n\ntemplate <class E> struct BridgeExec\
    \ : Bridge {\n    const VV<E>& g;\n    int n;\n    int ordc = 0;\n    V<int> low,\
    \ ord, vlist;\n    V<int> used;\n    BridgeExec(const VV<E>& _g)\n        : g(_g),\
    \ n(int(g.size())), low(n), ord(n), used(n) {\n        id = V<int>(n);\n     \
    \   for (int i = 0; i < n; i++) {\n            if (used[i]) continue;\n      \
    \      dfs1(i, -1);\n            dfs2(i, -1);\n        }\n    }\n    void dfs1(int\
    \ p, int b) {\n        used[p] = 1;\n        low[p] = ord[p] = ordc++;\n     \
    \   vlist.push_back(p);\n        bool rt = true;\n        for (auto e : g[p])\
    \ {\n            int d = e.to;\n            if (rt && d == b) {\n            \
    \    rt = false;\n                continue;\n            }\n            if (!used[d])\
    \ {\n                dfs1(d, p);\n                low[p] = min(low[p], low[d]);\n\
    \            } else {\n                low[p] = min(low[p], ord[d]);\n       \
    \     }\n        }\n    }\n    void dfs2(int p, int b) {\n        used[p] = 2;\n\
    \        bool is_root = low[p] == ord[p];\n        if (is_root) {\n          \
    \  int idc = int(groups.size());\n            id[p] = idc;\n            groups.push_back({p});\n\
    \            tr.push_back({});\n            if (b != -1) {\n                tr[idc].push_back(id[b]);\n\
    \                tr[id[b]].push_back(idc);\n            }\n        } else {\n\
    \            id[p] = id[b];\n            groups[id[p]].push_back(p);\n       \
    \ }\n        for (auto e : g[p]) {\n            int d = e.to;\n            if\
    \ (d == b || used[d] == 2) continue;\n            dfs2(d, p);\n        }\n   \
    \ }\n};\n\ntemplate <class E> Bridge get_bridge(const VV<E>& g) {\n    return\
    \ BridgeExec<E>(g);\n}\n"
  code: "struct Bridge {\n    V<int> id;\n    VV<int> groups;\n    VV<int> tr;\n};\n\
    \ntemplate <class E> struct BridgeExec : Bridge {\n    const VV<E>& g;\n    int\
    \ n;\n    int ordc = 0;\n    V<int> low, ord, vlist;\n    V<int> used;\n    BridgeExec(const\
    \ VV<E>& _g)\n        : g(_g), n(int(g.size())), low(n), ord(n), used(n) {\n \
    \       id = V<int>(n);\n        for (int i = 0; i < n; i++) {\n            if\
    \ (used[i]) continue;\n            dfs1(i, -1);\n            dfs2(i, -1);\n  \
    \      }\n    }\n    void dfs1(int p, int b) {\n        used[p] = 1;\n       \
    \ low[p] = ord[p] = ordc++;\n        vlist.push_back(p);\n        bool rt = true;\n\
    \        for (auto e : g[p]) {\n            int d = e.to;\n            if (rt\
    \ && d == b) {\n                rt = false;\n                continue;\n     \
    \       }\n            if (!used[d]) {\n                dfs1(d, p);\n        \
    \        low[p] = min(low[p], low[d]);\n            } else {\n               \
    \ low[p] = min(low[p], ord[d]);\n            }\n        }\n    }\n    void dfs2(int\
    \ p, int b) {\n        used[p] = 2;\n        bool is_root = low[p] == ord[p];\n\
    \        if (is_root) {\n            int idc = int(groups.size());\n         \
    \   id[p] = idc;\n            groups.push_back({p});\n            tr.push_back({});\n\
    \            if (b != -1) {\n                tr[idc].push_back(id[b]);\n     \
    \           tr[id[b]].push_back(idc);\n            }\n        } else {\n     \
    \       id[p] = id[b];\n            groups[id[p]].push_back(p);\n        }\n \
    \       for (auto e : g[p]) {\n            int d = e.to;\n            if (d ==\
    \ b || used[d] == 2) continue;\n            dfs2(d, p);\n        }\n    }\n};\n\
    \ntemplate <class E> Bridge get_bridge(const VV<E>& g) {\n    return BridgeExec<E>(g);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/bridge.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/bridge.hpp
layout: document
redirect_from:
- /library/src/graph/bridge.hpp
- /library/src/graph/bridge.hpp.html
title: src/graph/bridge.hpp
---
