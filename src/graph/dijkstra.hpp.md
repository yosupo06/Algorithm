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
  bundledCode: "#line 1 \"src/graph/dijkstra.hpp\"\ntemplate <class D> struct MinDist\
    \ {\n    V<D> dist;\n    V<int> from;\n};\n\ntemplate <class D, class E>\nMinDist<D>\
    \ mindist(const VV<E>& g, int s, D inf = numeric_limits<D>::max()) {\n    int\
    \ n = (int)g.size();\n    V<D> dist = V<D>(n, inf);\n    V<int> from = V<int>(n);\n\
    \    struct P {\n        D key;\n        int to;\n        bool operator<(P r)\
    \ const { return key > r.key; }\n    };\n    priority_queue<P> q;\n    q.push(P{0,\
    \ s});\n    dist[s] = D(0);\n    while (!q.empty()) {\n        P p = q.top();\n\
    \        q.pop();\n        if (dist[p.to] < p.key) continue;\n        for (E e\
    \ : g[p.to]) {\n            if (p.key + e.dist < dist[e.to]) {\n             \
    \   dist[e.to] = p.key + e.dist;\n                from[e.to] = p.to;\n       \
    \         q.push(P{dist[e.to], e.to});\n            }\n        }\n    }\n    return\
    \ MinDist<D>{dist, from};\n}\n"
  code: "template <class D> struct MinDist {\n    V<D> dist;\n    V<int> from;\n};\n\
    \ntemplate <class D, class E>\nMinDist<D> mindist(const VV<E>& g, int s, D inf\
    \ = numeric_limits<D>::max()) {\n    int n = (int)g.size();\n    V<D> dist = V<D>(n,\
    \ inf);\n    V<int> from = V<int>(n);\n    struct P {\n        D key;\n      \
    \  int to;\n        bool operator<(P r) const { return key > r.key; }\n    };\n\
    \    priority_queue<P> q;\n    q.push(P{0, s});\n    dist[s] = D(0);\n    while\
    \ (!q.empty()) {\n        P p = q.top();\n        q.pop();\n        if (dist[p.to]\
    \ < p.key) continue;\n        for (E e : g[p.to]) {\n            if (p.key + e.dist\
    \ < dist[e.to]) {\n                dist[e.to] = p.key + e.dist;\n            \
    \    from[e.to] = p.to;\n                q.push(P{dist[e.to], e.to});\n      \
    \      }\n        }\n    }\n    return MinDist<D>{dist, from};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/dijkstra.hpp
layout: document
redirect_from:
- /library/src/graph/dijkstra.hpp
- /library/src/graph/dijkstra.hpp.html
title: src/graph/dijkstra.hpp
---
