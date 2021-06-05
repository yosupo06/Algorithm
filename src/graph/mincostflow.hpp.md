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
  bundledCode: "#line 1 \"src/graph/mincostflow.hpp\"\n/*\nstruct E {\n    int to,\
    \ rev, cap, dist;\n};\nVV<E> g;\nauto add_edge = [&](int from, int to, int cap,\
    \ int dist) {\n    g[from].push_back(E{to, int(g[to].size()), cap, dist});\n \
    \   g[to].push_back(E{from, int(g[from].size())-1, 0, -dist});\n};\n\nauto res\
    \ = min_cost_flow<int, int>(g, s, t, false);\nres.max_flow(TEN(9));\n\n// cap_flow\
    \ : \u6700\u5927\u6D41\u91CF\n// flow : \u6700\u5C0F\u8CBB\u7528\n*/\n\ntemplate<class\
    \ C, class D, class E>\nstruct MinCostFlow {\n    static constexpr D INF = numeric_limits<D>::max();\n\
    \    int n;\n    VV<E> g;\n    int s, t;\n    C nc, cap_flow = 0;\n    D nd, flow\
    \ = 0;\n\n    V<D> dual;\n    V<int> pv, pe;\n\n    MinCostFlow(VV<E> _g, int\
    \ _s, int _t, bool neg)\n        : n(int(_g.size())), g(_g), s(_s), t(_t) {\n\
    \        assert(s != t);\n        dual = V<D>(n);\n        pv = pe = V<int>(n);\n\
    \        if (neg) {\n            V<D> dist(n, D(INF));\n            dist[s] =\
    \ 0;\n            for (int ph = 0; ph < n; ph++) {\n                bool update\
    \ = false;\n                for (int i = 0; i < n; i++) {\n                  \
    \  if (dist[i] == INF) continue;\n                    for (auto e: g[i]) {\n \
    \                       if (!e.cap) continue;\n                        if (dist[i]\
    \ + e.dist < dist[e.to]) {\n                            dist[e.to] = dist[i] +\
    \ e.dist;\n                            update = true;\n                      \
    \  }\n                    }\n                }\n                if (!update) break;\n\
    \            }\n            for (int v = 0; v < n; v++) {\n                dual[v]\
    \ += dist[v];\n            }\n        }\n        dual_ref();\n    }\n\n    C single_flow(C\
    \ c) {\n        if (nd == INF) return nc;\n        c = min(c, nc);\n        for\
    \ (int v = t; v != s; v = pv[v]) {\n            E& e = g[pv[v]][pe[v]];\n    \
    \        e.cap -= c;\n            g[v][e.rev].cap += c;\n        }\n        cap_flow\
    \ += c;\n        flow += nd * c;\n        nc -= c;\n        if (!nc) dual_ref();\n\
    \        return c;\n    }\n\n    void max_flow(C c) {\n        while (c) {\n \
    \           C f = single_flow(c);\n            if (!f) break;\n            c -=\
    \ f;\n        }\n    }\n\n    void dual_ref() {\n        V<D> dist(g.size(), D(INF));\n\
    \        pv = pe = V<int>(n, -1);\n        struct Q {\n            D key;\n  \
    \          int to;\n            bool operator<(Q r) const { return key > r.key;\
    \ }\n        };\n        priority_queue<Q> que;\n        dist[s] = 0;\n      \
    \  que.push(Q{D(0), s});\n        V<char> vis(n);\n        while (!que.empty())\
    \ {\n            int v = que.top().to; que.pop();\n            if (v == t) break;\n\
    \            if (vis[v]) continue;\n            vis[v] = true;\n            for\
    \ (int i = 0; i < int(g[v].size()); i++) {\n                E e = g[v][i];\n \
    \               if (vis[e.to] || !e.cap) continue;\n                D cost = dist[v]\
    \ + e.dist + dual[v] - dual[e.to];\n                if (dist[e.to] > cost) {\n\
    \                    dist[e.to] = cost;\n                    pv[e.to] = v; pe[e.to]\
    \ = i;\n                    que.push(Q{dist[e.to], e.to});\n                }\n\
    \            }\n        }\n        if (dist[t] == INF) {\n            nd = INF;\
    \ nc = 0;\n            return;\n        }\n        for (int v = 0; v < n; v++)\
    \ {\n            if (!vis[v]) continue;\n            dual[v] += dist[v] - dist[t];\n\
    \        }\n        nd = dual[t] - dual[s];\n        nc = numeric_limits<C>::max();\n\
    \        for (int v = t; v != s; v = pv[v]) {\n            nc = min(nc, g[pv[v]][pe[v]].cap);\n\
    \        }\n    }\n};\n\ntemplate<class C, class D, class E>\nMinCostFlow<C, D,\
    \ E> get_mcf(const VV<E>& g, int s, int t, bool neg = false) {\n    return MinCostFlow<C,\
    \ D, E>(g, s, t, neg);\n}\n"
  code: "/*\nstruct E {\n    int to, rev, cap, dist;\n};\nVV<E> g;\nauto add_edge\
    \ = [&](int from, int to, int cap, int dist) {\n    g[from].push_back(E{to, int(g[to].size()),\
    \ cap, dist});\n    g[to].push_back(E{from, int(g[from].size())-1, 0, -dist});\n\
    };\n\nauto res = min_cost_flow<int, int>(g, s, t, false);\nres.max_flow(TEN(9));\n\
    \n// cap_flow : \u6700\u5927\u6D41\u91CF\n// flow : \u6700\u5C0F\u8CBB\u7528\n\
    */\n\ntemplate<class C, class D, class E>\nstruct MinCostFlow {\n    static constexpr\
    \ D INF = numeric_limits<D>::max();\n    int n;\n    VV<E> g;\n    int s, t;\n\
    \    C nc, cap_flow = 0;\n    D nd, flow = 0;\n\n    V<D> dual;\n    V<int> pv,\
    \ pe;\n\n    MinCostFlow(VV<E> _g, int _s, int _t, bool neg)\n        : n(int(_g.size())),\
    \ g(_g), s(_s), t(_t) {\n        assert(s != t);\n        dual = V<D>(n);\n  \
    \      pv = pe = V<int>(n);\n        if (neg) {\n            V<D> dist(n, D(INF));\n\
    \            dist[s] = 0;\n            for (int ph = 0; ph < n; ph++) {\n    \
    \            bool update = false;\n                for (int i = 0; i < n; i++)\
    \ {\n                    if (dist[i] == INF) continue;\n                    for\
    \ (auto e: g[i]) {\n                        if (!e.cap) continue;\n          \
    \              if (dist[i] + e.dist < dist[e.to]) {\n                        \
    \    dist[e.to] = dist[i] + e.dist;\n                            update = true;\n\
    \                        }\n                    }\n                }\n       \
    \         if (!update) break;\n            }\n            for (int v = 0; v <\
    \ n; v++) {\n                dual[v] += dist[v];\n            }\n        }\n \
    \       dual_ref();\n    }\n\n    C single_flow(C c) {\n        if (nd == INF)\
    \ return nc;\n        c = min(c, nc);\n        for (int v = t; v != s; v = pv[v])\
    \ {\n            E& e = g[pv[v]][pe[v]];\n            e.cap -= c;\n          \
    \  g[v][e.rev].cap += c;\n        }\n        cap_flow += c;\n        flow += nd\
    \ * c;\n        nc -= c;\n        if (!nc) dual_ref();\n        return c;\n  \
    \  }\n\n    void max_flow(C c) {\n        while (c) {\n            C f = single_flow(c);\n\
    \            if (!f) break;\n            c -= f;\n        }\n    }\n\n    void\
    \ dual_ref() {\n        V<D> dist(g.size(), D(INF));\n        pv = pe = V<int>(n,\
    \ -1);\n        struct Q {\n            D key;\n            int to;\n        \
    \    bool operator<(Q r) const { return key > r.key; }\n        };\n        priority_queue<Q>\
    \ que;\n        dist[s] = 0;\n        que.push(Q{D(0), s});\n        V<char> vis(n);\n\
    \        while (!que.empty()) {\n            int v = que.top().to; que.pop();\n\
    \            if (v == t) break;\n            if (vis[v]) continue;\n         \
    \   vis[v] = true;\n            for (int i = 0; i < int(g[v].size()); i++) {\n\
    \                E e = g[v][i];\n                if (vis[e.to] || !e.cap) continue;\n\
    \                D cost = dist[v] + e.dist + dual[v] - dual[e.to];\n         \
    \       if (dist[e.to] > cost) {\n                    dist[e.to] = cost;\n   \
    \                 pv[e.to] = v; pe[e.to] = i;\n                    que.push(Q{dist[e.to],\
    \ e.to});\n                }\n            }\n        }\n        if (dist[t] ==\
    \ INF) {\n            nd = INF; nc = 0;\n            return;\n        }\n    \
    \    for (int v = 0; v < n; v++) {\n            if (!vis[v]) continue;\n     \
    \       dual[v] += dist[v] - dist[t];\n        }\n        nd = dual[t] - dual[s];\n\
    \        nc = numeric_limits<C>::max();\n        for (int v = t; v != s; v = pv[v])\
    \ {\n            nc = min(nc, g[pv[v]][pe[v]].cap);\n        }\n    }\n};\n\n\
    template<class C, class D, class E>\nMinCostFlow<C, D, E> get_mcf(const VV<E>&\
    \ g, int s, int t, bool neg = false) {\n    return MinCostFlow<C, D, E>(g, s,\
    \ t, neg);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/mincostflow.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/mincostflow.hpp
layout: document
redirect_from:
- /library/src/graph/mincostflow.hpp
- /library/src/graph/mincostflow.hpp.html
title: src/graph/mincostflow.hpp
---
