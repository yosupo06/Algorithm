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
  bundledCode: "#line 1 \"src/graph/retrograde.hpp\"\n/**\n * d[i] = \n *   -1:\u3053\
    \u306E\u30DE\u30B9\u304B\u3089\u30B9\u30BF\u30FC\u30C8\u3059\u308B\u3068\u5148\
    \u624B\u304C\u8CA0\u3051\u308B\n *    0:?\n *    1:\u3053\u306E\u30DE\u30B9\u304B\
    \u3089\u30B9\u30BF\u30FC\u30C8\u3059\u308B\u3068\u5148\u624B\u304C\u52DD\u3064\
    \n */\ntemplate<class E>\nvoid retrograde(const Graph<E> &g, const Graph<E> &rg,\
    \ vector<int> &d) {\n    int V = (int)g.size();\n    vector<int> count(V);\n \
    \   for (int i = 0; i < V; i++) {\n        count[i] = (int)g[i].size();\n    }\n\
    \    for (int i = 0; i < V; i++) {\n        if (d[i] == 1) {\n            for\
    \ (E e: rg[i]) {\n                count[e.to]--;\n            }\n        }\n \
    \   }\n    for (int i = 0; i < V; i++) {\n        if (d[i] == -1) {\n        \
    \    for (E e: rg[i]) {\n                if (d[e.to]) continue;\n            \
    \    d[e.to] = 1;\n                for (E f: rg[e.to]) {\n                   \
    \ count[f.to]--;\n                }\n            }\n        }\n    }\n    queue<int>\
    \ q;\n    for (int i = 0; i < V; i++) {\n        if (count[i]) continue;\n   \
    \     q.push(i);\n    }\n    while (q.size()) {\n        int p = q.front(); q.pop();\n\
    \        if (d[p]) continue;\n        d[p] = -1;\n        for (E e: rg[p]) {\n\
    \            if (d[e.to]) continue;\n            d[e.to] = 1;\n            for\
    \ (E f: rg[e.to]) {\n                count[f.to]--;\n                if (!count[f.to])\
    \ {\n                    q.push(f.to);\n                }\n            }\n   \
    \     }\n    }\n}\n"
  code: "/**\n * d[i] = \n *   -1:\u3053\u306E\u30DE\u30B9\u304B\u3089\u30B9\u30BF\
    \u30FC\u30C8\u3059\u308B\u3068\u5148\u624B\u304C\u8CA0\u3051\u308B\n *    0:?\n\
    \ *    1:\u3053\u306E\u30DE\u30B9\u304B\u3089\u30B9\u30BF\u30FC\u30C8\u3059\u308B\
    \u3068\u5148\u624B\u304C\u52DD\u3064\n */\ntemplate<class E>\nvoid retrograde(const\
    \ Graph<E> &g, const Graph<E> &rg, vector<int> &d) {\n    int V = (int)g.size();\n\
    \    vector<int> count(V);\n    for (int i = 0; i < V; i++) {\n        count[i]\
    \ = (int)g[i].size();\n    }\n    for (int i = 0; i < V; i++) {\n        if (d[i]\
    \ == 1) {\n            for (E e: rg[i]) {\n                count[e.to]--;\n  \
    \          }\n        }\n    }\n    for (int i = 0; i < V; i++) {\n        if\
    \ (d[i] == -1) {\n            for (E e: rg[i]) {\n                if (d[e.to])\
    \ continue;\n                d[e.to] = 1;\n                for (E f: rg[e.to])\
    \ {\n                    count[f.to]--;\n                }\n            }\n  \
    \      }\n    }\n    queue<int> q;\n    for (int i = 0; i < V; i++) {\n      \
    \  if (count[i]) continue;\n        q.push(i);\n    }\n    while (q.size()) {\n\
    \        int p = q.front(); q.pop();\n        if (d[p]) continue;\n        d[p]\
    \ = -1;\n        for (E e: rg[p]) {\n            if (d[e.to]) continue;\n    \
    \        d[e.to] = 1;\n            for (E f: rg[e.to]) {\n                count[f.to]--;\n\
    \                if (!count[f.to]) {\n                    q.push(f.to);\n    \
    \            }\n            }\n        }\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/retrograde.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/retrograde.hpp
layout: document
redirect_from:
- /library/src/graph/retrograde.hpp
- /library/src/graph/retrograde.hpp.html
title: src/graph/retrograde.hpp
---
