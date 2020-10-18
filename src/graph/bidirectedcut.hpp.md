---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/graph/bidirectedcut.hpp\"\ntemplate<class D, D INF>\n\
    struct BidirectedCut {\n    D sum = INF;\n    template<class E>\n    BidirectedCut(VV<E>\
    \ g) {\n        int n = (int)g.size();\n        int m_a = -1, m_b = -1;\n    \
    \    V<D> dist_base(n, 0);\n        for (int m = n; m > 1; m--) {\n          \
    \  int a, b;\n            auto dist = dist_base;\n            for (int i = 0;\
    \ i < m; i++) {\n                a = b; b = max_element(begin(dist), end(dist))\
    \ - begin(dist);\n                if (i == m-1) sum = min(sum, dist[b]);\n   \
    \             dist[b] = -INF;\n                for (E &e: g[b]) {\n          \
    \          if (e.to == m_b) e.to = m_a;\n                    if (dist[e.to] ==\
    \ -INF) continue;\n                    dist[e.to] += e.dist;\n               \
    \ }\n            }\n            //merge a, b\n            m_a = a; m_b = b;\n\
    \            g[a].insert(end(g[a]), begin(g[b]), end(g[b]));\n            g[b].clear();\n\
    \            dist_base[b] = -INF;\n        }\n    }\n};\n"
  code: "template<class D, D INF>\nstruct BidirectedCut {\n    D sum = INF;\n    template<class\
    \ E>\n    BidirectedCut(VV<E> g) {\n        int n = (int)g.size();\n        int\
    \ m_a = -1, m_b = -1;\n        V<D> dist_base(n, 0);\n        for (int m = n;\
    \ m > 1; m--) {\n            int a, b;\n            auto dist = dist_base;\n \
    \           for (int i = 0; i < m; i++) {\n                a = b; b = max_element(begin(dist),\
    \ end(dist)) - begin(dist);\n                if (i == m-1) sum = min(sum, dist[b]);\n\
    \                dist[b] = -INF;\n                for (E &e: g[b]) {\n       \
    \             if (e.to == m_b) e.to = m_a;\n                    if (dist[e.to]\
    \ == -INF) continue;\n                    dist[e.to] += e.dist;\n            \
    \    }\n            }\n            //merge a, b\n            m_a = a; m_b = b;\n\
    \            g[a].insert(end(g[a]), begin(g[b]), end(g[b]));\n            g[b].clear();\n\
    \            dist_base[b] = -INF;\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/bidirectedcut.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/bidirectedcut.hpp
layout: document
redirect_from:
- /library/src/graph/bidirectedcut.hpp
- /library/src/graph/bidirectedcut.hpp.html
title: src/graph/bidirectedcut.hpp
---
