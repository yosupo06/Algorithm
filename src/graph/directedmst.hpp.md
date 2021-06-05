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
  bundledCode: "#line 1 \"src/graph/directedmst.hpp\"\ntemplate<class E>\nstruct DirectedMST\
    \ {\n    decltype(E::dist) cost = 0;\n    V<E> mine; // min edge\n    DirectedMST(const\
    \ Graph<E> &g, int r) {\n        int n = (int)g.size();\n        mine = vector<E>(n);\n\
    \        for (int i = 0; i < n; i++) {\n            if (i == r) continue;\n  \
    \          assert((int)g[i].size());\n            mine[i] = *min_element(g[i].begin(),\
    \ g[i].end(),\n                [](const E &l, const E &r){return l.dist < r.dist;});\n\
    \            cost += mine[i].dist;\n        }\n        V<int> i2g(n, -1); i2g[r]\
    \ = 0;\n        int gc = 1;\n        for (int i = 0; i < n; i++) {\n         \
    \   if (i2g[i] != -1) continue;\n            int j = i;\n            do {\n  \
    \              i2g[j] = gc++;\n            } while (j = mine[j].to, i2g[j] ==\
    \ -1);\n            if (i2g[j] < i2g[i]) continue;\n            //roop\n     \
    \       int k = j;\n            do {\n                i2g[k] = i2g[j];\n     \
    \       } while(k = mine[k].to, k != j);\n            gc = i2g[j]+1;\n       \
    \ }\n        if (gc == n) return;\n        Graph<E> ng(gc);\n        for (int\
    \ i = 0; i < n; i++) {\n            if (i == r) continue;\n            for (E\
    \ e: g[i]) {\n                if (i2g[e.to] == i2g[i]) continue;\n           \
    \     e.to = i2g[e.to];\n                e.dist -= mine[i].dist;\n           \
    \     ng[i2g[i]].push_back(e);\n            }\n        }\n        auto nme = DirectedMST(ng,\
    \ 0).mine;\n        vector<bool> ok(gc, false);\n        for (int i = 0; i < n;\
    \ i++) {\n            if (i == r or ok[i2g[i]]) continue;\n            for (E\
    \ e: g[i]) {\n                if (e.dist - mine[i].dist == nme[i2g[i]].dist) {\n\
    \                    ok[i2g[i]] = true;\n                    mine[i] = e;\n  \
    \                  cost += nme[i2g[i]].dist;\n                    break;\n   \
    \             }\n            }\n        }\n    }\n};\n"
  code: "template<class E>\nstruct DirectedMST {\n    decltype(E::dist) cost = 0;\n\
    \    V<E> mine; // min edge\n    DirectedMST(const Graph<E> &g, int r) {\n   \
    \     int n = (int)g.size();\n        mine = vector<E>(n);\n        for (int i\
    \ = 0; i < n; i++) {\n            if (i == r) continue;\n            assert((int)g[i].size());\n\
    \            mine[i] = *min_element(g[i].begin(), g[i].end(),\n              \
    \  [](const E &l, const E &r){return l.dist < r.dist;});\n            cost +=\
    \ mine[i].dist;\n        }\n        V<int> i2g(n, -1); i2g[r] = 0;\n        int\
    \ gc = 1;\n        for (int i = 0; i < n; i++) {\n            if (i2g[i] != -1)\
    \ continue;\n            int j = i;\n            do {\n                i2g[j]\
    \ = gc++;\n            } while (j = mine[j].to, i2g[j] == -1);\n            if\
    \ (i2g[j] < i2g[i]) continue;\n            //roop\n            int k = j;\n  \
    \          do {\n                i2g[k] = i2g[j];\n            } while(k = mine[k].to,\
    \ k != j);\n            gc = i2g[j]+1;\n        }\n        if (gc == n) return;\n\
    \        Graph<E> ng(gc);\n        for (int i = 0; i < n; i++) {\n           \
    \ if (i == r) continue;\n            for (E e: g[i]) {\n                if (i2g[e.to]\
    \ == i2g[i]) continue;\n                e.to = i2g[e.to];\n                e.dist\
    \ -= mine[i].dist;\n                ng[i2g[i]].push_back(e);\n            }\n\
    \        }\n        auto nme = DirectedMST(ng, 0).mine;\n        vector<bool>\
    \ ok(gc, false);\n        for (int i = 0; i < n; i++) {\n            if (i ==\
    \ r or ok[i2g[i]]) continue;\n            for (E e: g[i]) {\n                if\
    \ (e.dist - mine[i].dist == nme[i2g[i]].dist) {\n                    ok[i2g[i]]\
    \ = true;\n                    mine[i] = e;\n                    cost += nme[i2g[i]].dist;\n\
    \                    break;\n                }\n            }\n        }\n   \
    \ }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/directedmst.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/directedmst.hpp
layout: document
redirect_from:
- /library/src/graph/directedmst.hpp
- /library/src/graph/directedmst.hpp.html
title: src/graph/directedmst.hpp
---
