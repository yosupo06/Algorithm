---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/graph/matroidintersection.hpp\"\n\n/*\nelements: matroid\
    \ elements\non: used elements\nf: lambda, f(on, g1(i, j), g2(i, j))\u3068\u547C\
    \u3070\u308C\u308B\u306E\u3067\n\u305D\u306E\u307E\u307E\u8DB3\u305B\u308B\u8981\
    \u7D20\u306B\u3064\u3044\u3066g(i, -1)\u3092\u547C\u3073\u3001\u4EA4\u63DB\u3067\
    \u304D\u308B\u30DA\u30A2\u306B\u3064\u3044\u3066g(i, j)\u3092\u547C\u3076\n*/\n\
    template <class E, class F>\nbool matroid_intersection(const V<E>& elements, V<bool>&\
    \ on, F& f) {\n    int m = int(elements.size());\n    assert(int(on.size()) ==\
    \ m);\n    VV<int> g(m);\n    V<bool> st(m), ed(m);\n    f(on,\n      [&](int\
    \ u, int v) {\n          assert(0 <= u && u < m && !on[u]);\n          if (v ==\
    \ -1)\n              st[u] = true;\n          else {\n              assert(0 <=\
    \ v && v < m && on[v]);\n              g[v].push_back(u);\n          }\n     \
    \ },\n      [&](int u, int v) {\n          assert(0 <= u && u < m && !on[u]);\n\
    \          if (v == -1)\n              ed[u] = true;\n          else {\n     \
    \         assert(0 <= v && v < m && on[v]);\n              g[u].push_back(v);\n\
    \          }\n      });\n    V<int> prev(m, -1);\n    V<int> dist(m, TEN(9));\n\
    \    queue<int> que;\n    for (int i = 0; i < m; i++) {\n        if (st[i]) {\n\
    \            dist[i] = 0;\n            que.push(i);\n        }\n    }\n\n    while\
    \ (que.size()) {\n        int p = que.front();\n        que.pop();\n        if\
    \ (ed[p]) {\n            int now = p;\n            while (now != -1) {\n     \
    \           on[now] = !on[now];\n                now = prev[now];\n          \
    \  }\n            return true;\n        }\n        for (int d : g[p]) {\n    \
    \        if (dist[d] > dist[p] + 1) {\n                dist[d] = dist[p] + 1;\n\
    \                prev[d] = p;\n                que.push(d);\n            }\n \
    \       }\n    }\n    return false;\n}\ntemplate <class E, class F>\nV<bool> matroid_intersection(const\
    \ V<E>& elements, F f) {\n    int m = int(elements.size());\n    V<bool> on(m);\n\
    \    while (matroid_intersection(elements, on, f)) {\n    }\n    return on;\n\
    }\n\n/*\nvoid CFHello2020G {\n    // forest * choise\n    auto used =\n      \
    \  matroid_intersection(es, [&](const V<bool>& on, auto g1, auto g2) {\n     \
    \       auto base = UnionFind(n);\n            V<int> cnt(n);\n            for\
    \ (int l = 0; l < m; l++) {\n                if (!on[l]) continue;\n         \
    \       base.merge(es[l].from, es[l].to);\n                cnt[es[l].id]++;\n\
    \            }\n            for (int r = 0; r < m; r++) {\n                if\
    \ (on[r]) continue;\n                if (!base.same(es[r].from, es[r].to)) g1(r,\
    \ -1);\n                if (cnt[es[r].id] == 0) g2(r, -1);\n            }\n  \
    \          for (int l = 0; l < m; l++) {\n                if (!on[l]) continue;\n\
    \                auto uf = UnionFind(n);\n                for (int i = 0; i <\
    \ m; i++) {\n                    if (!on[i] || i == l) continue;\n           \
    \         uf.merge(es[i].from, es[i].to);\n                }\n               \
    \ for (int r = 0; r < m; r++) {\n                    if (on[r]) continue;\n  \
    \                  if (!uf.same(es[r].from, es[r].to)) g1(r, l);\n           \
    \         if (es[l].id == es[r].id) g2(r, l);\n                }\n           \
    \ }\n        });\n}*/\n"
  code: "#pragma once\n\n/*\nelements: matroid elements\non: used elements\nf: lambda,\
    \ f(on, g1(i, j), g2(i, j))\u3068\u547C\u3070\u308C\u308B\u306E\u3067\n\u305D\u306E\
    \u307E\u307E\u8DB3\u305B\u308B\u8981\u7D20\u306B\u3064\u3044\u3066g(i, -1)\u3092\
    \u547C\u3073\u3001\u4EA4\u63DB\u3067\u304D\u308B\u30DA\u30A2\u306B\u3064\u3044\
    \u3066g(i, j)\u3092\u547C\u3076\n*/\ntemplate <class E, class F>\nbool matroid_intersection(const\
    \ V<E>& elements, V<bool>& on, F& f) {\n    int m = int(elements.size());\n  \
    \  assert(int(on.size()) == m);\n    VV<int> g(m);\n    V<bool> st(m), ed(m);\n\
    \    f(on,\n      [&](int u, int v) {\n          assert(0 <= u && u < m && !on[u]);\n\
    \          if (v == -1)\n              st[u] = true;\n          else {\n     \
    \         assert(0 <= v && v < m && on[v]);\n              g[v].push_back(u);\n\
    \          }\n      },\n      [&](int u, int v) {\n          assert(0 <= u &&\
    \ u < m && !on[u]);\n          if (v == -1)\n              ed[u] = true;\n   \
    \       else {\n              assert(0 <= v && v < m && on[v]);\n            \
    \  g[u].push_back(v);\n          }\n      });\n    V<int> prev(m, -1);\n    V<int>\
    \ dist(m, TEN(9));\n    queue<int> que;\n    for (int i = 0; i < m; i++) {\n \
    \       if (st[i]) {\n            dist[i] = 0;\n            que.push(i);\n   \
    \     }\n    }\n\n    while (que.size()) {\n        int p = que.front();\n   \
    \     que.pop();\n        if (ed[p]) {\n            int now = p;\n           \
    \ while (now != -1) {\n                on[now] = !on[now];\n                now\
    \ = prev[now];\n            }\n            return true;\n        }\n        for\
    \ (int d : g[p]) {\n            if (dist[d] > dist[p] + 1) {\n               \
    \ dist[d] = dist[p] + 1;\n                prev[d] = p;\n                que.push(d);\n\
    \            }\n        }\n    }\n    return false;\n}\ntemplate <class E, class\
    \ F>\nV<bool> matroid_intersection(const V<E>& elements, F f) {\n    int m = int(elements.size());\n\
    \    V<bool> on(m);\n    while (matroid_intersection(elements, on, f)) {\n   \
    \ }\n    return on;\n}\n\n/*\nvoid CFHello2020G {\n    // forest * choise\n  \
    \  auto used =\n        matroid_intersection(es, [&](const V<bool>& on, auto g1,\
    \ auto g2) {\n            auto base = UnionFind(n);\n            V<int> cnt(n);\n\
    \            for (int l = 0; l < m; l++) {\n                if (!on[l]) continue;\n\
    \                base.merge(es[l].from, es[l].to);\n                cnt[es[l].id]++;\n\
    \            }\n            for (int r = 0; r < m; r++) {\n                if\
    \ (on[r]) continue;\n                if (!base.same(es[r].from, es[r].to)) g1(r,\
    \ -1);\n                if (cnt[es[r].id] == 0) g2(r, -1);\n            }\n  \
    \          for (int l = 0; l < m; l++) {\n                if (!on[l]) continue;\n\
    \                auto uf = UnionFind(n);\n                for (int i = 0; i <\
    \ m; i++) {\n                    if (!on[i] || i == l) continue;\n           \
    \         uf.merge(es[i].from, es[i].to);\n                }\n               \
    \ for (int r = 0; r < m; r++) {\n                    if (on[r]) continue;\n  \
    \                  if (!uf.same(es[r].from, es[r].to)) g1(r, l);\n           \
    \         if (es[l].id == es[r].id) g2(r, l);\n                }\n           \
    \ }\n        });\n}*/\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/matroidintersection.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/matroidintersection.hpp
layout: document
redirect_from:
- /library/src/graph/matroidintersection.hpp
- /library/src/graph/matroidintersection.hpp.html
title: src/graph/matroidintersection.hpp
---
