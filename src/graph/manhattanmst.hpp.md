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
  bundledCode: "#line 1 \"src/graph/manhattanmst.hpp\"\ntemplate <class T>\nV<pair<int,\
    \ int>> manhattan_mst(V<pair<T, T>> ps,\n                                T inf\
    \ = numeric_limits<T>::max()) {\n    V<pair<int, int>> edges;\n    int n = int(ps.size());\n\
    \    V<int> ids(n);\n    iota(ids.begin(), ids.end(), 0);\n    for (int ph = 0;\
    \ ph < 4; ph++) {\n        sort(ids.begin(), ids.end(), [&](auto i, auto j) {\n\
    \            T ixy = (ps[i].first + ps[i].second),\n              jxy = (ps[j].first\
    \ + ps[j].second);\n            return tie(ixy, ps[i].second) > tie(jxy, ps[j].second);\n\
    \        });\n        V<T> xv;\n        for (int i = 0; i < n; i++) xv.push_back(ps[i].first);\n\
    \        sort(xv.begin(), xv.end());\n        xv.erase(unique(xv.begin(), xv.end()),\
    \ xv.end());\n        using P = pair<T, int>;\n        V<P> fen(n, P(-inf, -1));\n\
    \        for (int id : ids) {\n            auto xi = int(lower_bound(xv.begin(),\
    \ xv.end(), ps[id].first) -\n                          xv.begin());\n        \
    \    P ma = P(-inf, -1);\n            {\n                int i = xi + 1;\n   \
    \             while (i > 0) {\n                    if (ma.first <= fen[i - 1].first)\
    \ ma = fen[i - 1];\n                    i -= i & -i;\n                }\n    \
    \        }\n            if (ma.second != -1) edges.push_back({id, ma.second});\n\
    \            {\n                T x = ps[id].first - ps[id].second;\n        \
    \        int i = xi + 1;\n                while (i <= n) {\n                 \
    \   if (fen[i - 1].first <= x) fen[i - 1] = P(x, id);\n                    i +=\
    \ i & -i;\n                }\n            }\n        }\n\n        for (auto& p\
    \ : ps) {\n            swap(p.first, p.second);\n        }\n        if (ph ==\
    \ 1) {\n            for (auto& p : ps) {\n                p.second *= -1;\n  \
    \          }\n        }\n    }\n    auto dist = [&](int i, int j) {\n        return\
    \ abs(ps[i].first - ps[j].first) +\n               abs(ps[i].second - ps[j].second);\n\
    \    };\n    sort(edges.begin(), edges.end(), [&](auto x, auto y) {\n        return\
    \ dist(x.first, x.second) < dist(y.first, y.second);\n    });\n    auto uf = UnionFind(n);\n\
    \    V<pair<int, int>> res;\n    for (auto p : edges) {\n        if (uf.same(p.first,\
    \ p.second)) continue;\n        res.push_back(p);\n        uf.merge(p.first, p.second);\n\
    \    }\n    return res;\n}\n"
  code: "template <class T>\nV<pair<int, int>> manhattan_mst(V<pair<T, T>> ps,\n \
    \                               T inf = numeric_limits<T>::max()) {\n    V<pair<int,\
    \ int>> edges;\n    int n = int(ps.size());\n    V<int> ids(n);\n    iota(ids.begin(),\
    \ ids.end(), 0);\n    for (int ph = 0; ph < 4; ph++) {\n        sort(ids.begin(),\
    \ ids.end(), [&](auto i, auto j) {\n            T ixy = (ps[i].first + ps[i].second),\n\
    \              jxy = (ps[j].first + ps[j].second);\n            return tie(ixy,\
    \ ps[i].second) > tie(jxy, ps[j].second);\n        });\n        V<T> xv;\n   \
    \     for (int i = 0; i < n; i++) xv.push_back(ps[i].first);\n        sort(xv.begin(),\
    \ xv.end());\n        xv.erase(unique(xv.begin(), xv.end()), xv.end());\n    \
    \    using P = pair<T, int>;\n        V<P> fen(n, P(-inf, -1));\n        for (int\
    \ id : ids) {\n            auto xi = int(lower_bound(xv.begin(), xv.end(), ps[id].first)\
    \ -\n                          xv.begin());\n            P ma = P(-inf, -1);\n\
    \            {\n                int i = xi + 1;\n                while (i > 0)\
    \ {\n                    if (ma.first <= fen[i - 1].first) ma = fen[i - 1];\n\
    \                    i -= i & -i;\n                }\n            }\n        \
    \    if (ma.second != -1) edges.push_back({id, ma.second});\n            {\n \
    \               T x = ps[id].first - ps[id].second;\n                int i = xi\
    \ + 1;\n                while (i <= n) {\n                    if (fen[i - 1].first\
    \ <= x) fen[i - 1] = P(x, id);\n                    i += i & -i;\n           \
    \     }\n            }\n        }\n\n        for (auto& p : ps) {\n          \
    \  swap(p.first, p.second);\n        }\n        if (ph == 1) {\n            for\
    \ (auto& p : ps) {\n                p.second *= -1;\n            }\n        }\n\
    \    }\n    auto dist = [&](int i, int j) {\n        return abs(ps[i].first -\
    \ ps[j].first) +\n               abs(ps[i].second - ps[j].second);\n    };\n \
    \   sort(edges.begin(), edges.end(), [&](auto x, auto y) {\n        return dist(x.first,\
    \ x.second) < dist(y.first, y.second);\n    });\n    auto uf = UnionFind(n);\n\
    \    V<pair<int, int>> res;\n    for (auto p : edges) {\n        if (uf.same(p.first,\
    \ p.second)) continue;\n        res.push_back(p);\n        uf.merge(p.first, p.second);\n\
    \    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/manhattanmst.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/manhattanmst.hpp
layout: document
redirect_from:
- /library/src/graph/manhattanmst.hpp
- /library/src/graph/manhattanmst.hpp.html
title: src/graph/manhattanmst.hpp
---
