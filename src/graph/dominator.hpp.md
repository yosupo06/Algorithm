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
  bundledCode: "#line 1 \"src/graph/dominator.hpp\"\nstruct Dominator {\n    V<int>\
    \ idom, sdom;\n    LowLink lc;\n    Dominator() {}\n    template<class E>\n  \
    \  Dominator(const VV<E> &g, const VV<E> &rg, int s) {\n        lc = LowLink(g,\
    \ s);\n        int n = (int)g.size();\n        \n        // uf init\n        p.resize(n);\
    \ mv.resize(n);\n        fill_n(p.begin(), n, -1);\n        iota(mv.begin(), mv.end(),\
    \ 0);\n        idom = vector<int>(n, -1);\n        sdom = vector<int>(n);\n  \
    \      iota(sdom.begin(), sdom.end(), 0);\n\n        vector<int> up(n);\n    \
    \    vector<vector<int>> bucket(n);\n        int U = int(lc.vlis.size());\n  \
    \      for (int i = U-1; i > 0; i--) {\n            int u = lc.vlis[i];\n    \
    \        for (E e: rg[u]) {\n                if (lc.ord[e.to] == -1) continue;\n\
    \                sdom[u] = lc.vlis[min(lc.ord[sdom[u]], lc.ord[sdom[compress(e.to)]])];\n\
    \            }\n            bucket[sdom[u]].push_back(u);\n            for (int\
    \ v: bucket[lc.par[u]]) {\n                up[v] = compress(v);\n            }\n\
    \            bucket[lc.par[u]].clear();\n            p[u] = lc.par[u]; // uf merge\n\
    \        }\n\n        for (int i = 1; i < U; i++) {\n            int u = lc.vlis[i],\
    \ v = up[u];\n            if (sdom[u] == sdom[v]) idom[u] = sdom[u];\n       \
    \     else idom[u] = idom[v];\n        }\n    }\n\n    // unionfind\n    V<int>\
    \ p, mv; // parent, min sdom's v\n    int compress(int a) {\n        if (p[a]\
    \ != -1) {\n            compress(p[a]);\n            if (lc.ord[sdom[mv[a]]] >\
    \ lc.ord[sdom[mv[p[a]]]]) {\n                mv[a] = mv[p[a]];\n            }\n\
    \            p[a] = (p[p[a]] == -1 ? p[a] : p[p[a]]);\n        }\n        return\
    \ mv[a];\n    }\n};\n"
  code: "struct Dominator {\n    V<int> idom, sdom;\n    LowLink lc;\n    Dominator()\
    \ {}\n    template<class E>\n    Dominator(const VV<E> &g, const VV<E> &rg, int\
    \ s) {\n        lc = LowLink(g, s);\n        int n = (int)g.size();\n        \n\
    \        // uf init\n        p.resize(n); mv.resize(n);\n        fill_n(p.begin(),\
    \ n, -1);\n        iota(mv.begin(), mv.end(), 0);\n        idom = vector<int>(n,\
    \ -1);\n        sdom = vector<int>(n);\n        iota(sdom.begin(), sdom.end(),\
    \ 0);\n\n        vector<int> up(n);\n        vector<vector<int>> bucket(n);\n\
    \        int U = int(lc.vlis.size());\n        for (int i = U-1; i > 0; i--) {\n\
    \            int u = lc.vlis[i];\n            for (E e: rg[u]) {\n           \
    \     if (lc.ord[e.to] == -1) continue;\n                sdom[u] = lc.vlis[min(lc.ord[sdom[u]],\
    \ lc.ord[sdom[compress(e.to)]])];\n            }\n            bucket[sdom[u]].push_back(u);\n\
    \            for (int v: bucket[lc.par[u]]) {\n                up[v] = compress(v);\n\
    \            }\n            bucket[lc.par[u]].clear();\n            p[u] = lc.par[u];\
    \ // uf merge\n        }\n\n        for (int i = 1; i < U; i++) {\n          \
    \  int u = lc.vlis[i], v = up[u];\n            if (sdom[u] == sdom[v]) idom[u]\
    \ = sdom[u];\n            else idom[u] = idom[v];\n        }\n    }\n\n    //\
    \ unionfind\n    V<int> p, mv; // parent, min sdom's v\n    int compress(int a)\
    \ {\n        if (p[a] != -1) {\n            compress(p[a]);\n            if (lc.ord[sdom[mv[a]]]\
    \ > lc.ord[sdom[mv[p[a]]]]) {\n                mv[a] = mv[p[a]];\n           \
    \ }\n            p[a] = (p[p[a]] == -1 ? p[a] : p[p[a]]);\n        }\n       \
    \ return mv[a];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/dominator.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/dominator.hpp
layout: document
redirect_from:
- /library/src/graph/dominator.hpp
- /library/src/graph/dominator.hpp.html
title: src/graph/dominator.hpp
---
