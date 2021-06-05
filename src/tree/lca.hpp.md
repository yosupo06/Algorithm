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
  bundledCode: "#line 2 \"src/tree/lca.hpp\"\n\nstruct LCA {\n    int lg;\n    VV<int>\
    \ anc;\n    V<int> dps;\n    /// l\u3068r\u306E\u9802\u70B9\u306ELCA\u3092\u6C42\
    \u3081\u308B\n    int query(int l, int r) {\n        if (dps[l] < dps[r]) swap(l,\
    \ r);\n        int dd = dps[l] - dps[r];\n        for (int i = lg - 1; i >= 0;\
    \ i--) {\n            if (dd < (1 << i)) continue;\n            dd -= 1 << i;\n\
    \            l = anc[i][l];\n        }\n        if (l == r) return l;\n      \
    \  for (int i = lg - 1; i >= 0; i--) {\n            if (anc[i][l] == anc[i][r])\
    \ continue;\n            tie(l, r) = tie(anc[i][l], anc[i][r]);\n        }\n \
    \       return anc[0][l];\n    }\n    int up(int p, int dist) {\n        for (int\
    \ i = lg - 1; i >= 0; i--) {\n            if (dist >= (1 << i)) {\n          \
    \      dist -= 1 << i;\n                p = anc[i][p];\n            }\n      \
    \  }\n        return p;\n    }\n    int dist(int l, int r) {\n        int z =\
    \ query(l, r);\n        return dps[l] + dps[r] - 2 * dps[z];\n    }\n};\n\ntemplate\
    \ <class E> struct LCAExec : LCA {\n    const VV<E>& g;\n\n    /// \u4E8B\u524D\
    \u51E6\u7406\u3092\u884C\u3046 r\u306Froot\u9802\u70B9\u306Eid\n    LCAExec(const\
    \ VV<E>& _g, int r) : g(_g) {\n        int N = int(g.size());\n        lg = 1;\n\
    \        while ((1 << lg) < N) lg++;\n        anc = VV<int>(lg, V<int>(N, -1));\n\
    \        dps = V<int>(N);\n        dfs(r, -1, 0);\n        for (int i = 1; i <\
    \ lg; i++) {\n            for (int j = 0; j < N; j++) {\n                anc[i][j]\
    \ =\n                    (anc[i - 1][j] == -1) ? -1 : anc[i - 1][anc[i - 1][j]];\n\
    \            }\n        }\n    }\n\n    void dfs(int p, int b, int now) {\n  \
    \      anc[0][p] = b;\n        dps[p] = now;\n        for (E e : g[p]) {\n   \
    \         if (e.to == b) continue;\n            dfs(e.to, p, now + 1);\n     \
    \   }\n    }\n};\n\ntemplate <class E> LCA get_lca(const VV<E>& g, int r) {\n\
    \    return LCAExec<E>(g, r);\n}\n"
  code: "#pragma once\n\nstruct LCA {\n    int lg;\n    VV<int> anc;\n    V<int> dps;\n\
    \    /// l\u3068r\u306E\u9802\u70B9\u306ELCA\u3092\u6C42\u3081\u308B\n    int\
    \ query(int l, int r) {\n        if (dps[l] < dps[r]) swap(l, r);\n        int\
    \ dd = dps[l] - dps[r];\n        for (int i = lg - 1; i >= 0; i--) {\n       \
    \     if (dd < (1 << i)) continue;\n            dd -= 1 << i;\n            l =\
    \ anc[i][l];\n        }\n        if (l == r) return l;\n        for (int i = lg\
    \ - 1; i >= 0; i--) {\n            if (anc[i][l] == anc[i][r]) continue;\n   \
    \         tie(l, r) = tie(anc[i][l], anc[i][r]);\n        }\n        return anc[0][l];\n\
    \    }\n    int up(int p, int dist) {\n        for (int i = lg - 1; i >= 0; i--)\
    \ {\n            if (dist >= (1 << i)) {\n                dist -= 1 << i;\n  \
    \              p = anc[i][p];\n            }\n        }\n        return p;\n \
    \   }\n    int dist(int l, int r) {\n        int z = query(l, r);\n        return\
    \ dps[l] + dps[r] - 2 * dps[z];\n    }\n};\n\ntemplate <class E> struct LCAExec\
    \ : LCA {\n    const VV<E>& g;\n\n    /// \u4E8B\u524D\u51E6\u7406\u3092\u884C\
    \u3046 r\u306Froot\u9802\u70B9\u306Eid\n    LCAExec(const VV<E>& _g, int r) :\
    \ g(_g) {\n        int N = int(g.size());\n        lg = 1;\n        while ((1\
    \ << lg) < N) lg++;\n        anc = VV<int>(lg, V<int>(N, -1));\n        dps =\
    \ V<int>(N);\n        dfs(r, -1, 0);\n        for (int i = 1; i < lg; i++) {\n\
    \            for (int j = 0; j < N; j++) {\n                anc[i][j] =\n    \
    \                (anc[i - 1][j] == -1) ? -1 : anc[i - 1][anc[i - 1][j]];\n   \
    \         }\n        }\n    }\n\n    void dfs(int p, int b, int now) {\n     \
    \   anc[0][p] = b;\n        dps[p] = now;\n        for (E e : g[p]) {\n      \
    \      if (e.to == b) continue;\n            dfs(e.to, p, now + 1);\n        }\n\
    \    }\n};\n\ntemplate <class E> LCA get_lca(const VV<E>& g, int r) {\n    return\
    \ LCAExec<E>(g, r);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/tree/lca.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/tree/lca.hpp
layout: document
redirect_from:
- /library/src/tree/lca.hpp
- /library/src/tree/lca.hpp.html
title: src/tree/lca.hpp
---
