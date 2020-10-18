---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/graph/hungarian.hpp\"\n/**\n\u5272\u5F53\u554F\u984C\
    \u3092\u89E3\u304D\uFF0C\u4EE5\u4E0B\u306E\u6761\u4EF6\u3092\u6E80\u305F\u3059\
    le, ri, perm\u3092\u5F97\u308B\n- le[i] <= 0, ri[j] >= 0\n- cost[i][j] + le[i]\
    \ + ri[j] >= 0\n- cost[i][perm[i]] + le[i] + ri[perm[i]] = 0\n*/\ntemplate<class\
    \ D>\nstruct Hungarian {\n    V<D> le, ri;\n    V<int> perm;\n\n    Hungarian(const\
    \ VV<D>& c) {\n        int n = int(c.size()), m = int(c[0].size());\n        assert(n\
    \ <= m);\n        le = V<D>(n, D(0)); ri = V<D>(m, D(0));\n        perm = V<int>(n);\n\
    \        V<int> to_r(n, -1), to_l(m, -1);\n\n        for (int s = 0; s < n; s++)\
    \ {\n            V<char> l_u(n), r_u(m);\n            l_u[s] = true;\n       \
    \     V<int> tr(m, -1), min_l(m, s);\n            V<D> min_cost(m);\n        \
    \    for (int j = 0; j < m; j++) min_cost[j] = c[s][j] + le[s] + ri[j];\n    \
    \        while (true) {\n                int r = -1;\n                D d = numeric_limits<D>::max();\n\
    \                for (int j = 0; j < m; j++) {\n                    if (!r_u[j]\
    \ && min_cost[j] < d) {\n                        r = j;\n                    \
    \    d = min_cost[j];\n                    }\n                }\n            \
    \    for (int i = 0; i < n; i++) if (l_u[i]) le[i] -= d;\n                for\
    \ (int j = 0; j < m; j++) {\n                    if (r_u[j]) ri[j] += d;\n   \
    \                 else min_cost[j] -= d;\n                }\n                tr[r]\
    \ = min_l[r];\n                int l = to_l[r];\n                if (l == -1)\
    \ {\n                    while (r != -1) {\n                        int nl = tr[r],\
    \ nr = to_r[nl];\n                        to_l[r] = nl; to_r[nl] = r;\n      \
    \                  r = nr;\n                    }\n                    break;\n\
    \                }\n                l_u[l] = r_u[r] = true;\n                for\
    \ (int j = 0; j < m; j++) {\n                    D cost = c[l][j] + le[l] + ri[j];\n\
    \                    if (cost < min_cost[j]) {\n                        min_l[j]\
    \ = l;\n                        min_cost[j] = cost;\n                    }\n \
    \               }\n            }\n        }\n        perm = to_r;\n    }\n};\n"
  code: "/**\n\u5272\u5F53\u554F\u984C\u3092\u89E3\u304D\uFF0C\u4EE5\u4E0B\u306E\u6761\
    \u4EF6\u3092\u6E80\u305F\u3059le, ri, perm\u3092\u5F97\u308B\n- le[i] <= 0, ri[j]\
    \ >= 0\n- cost[i][j] + le[i] + ri[j] >= 0\n- cost[i][perm[i]] + le[i] + ri[perm[i]]\
    \ = 0\n*/\ntemplate<class D>\nstruct Hungarian {\n    V<D> le, ri;\n    V<int>\
    \ perm;\n\n    Hungarian(const VV<D>& c) {\n        int n = int(c.size()), m =\
    \ int(c[0].size());\n        assert(n <= m);\n        le = V<D>(n, D(0)); ri =\
    \ V<D>(m, D(0));\n        perm = V<int>(n);\n        V<int> to_r(n, -1), to_l(m,\
    \ -1);\n\n        for (int s = 0; s < n; s++) {\n            V<char> l_u(n), r_u(m);\n\
    \            l_u[s] = true;\n            V<int> tr(m, -1), min_l(m, s);\n    \
    \        V<D> min_cost(m);\n            for (int j = 0; j < m; j++) min_cost[j]\
    \ = c[s][j] + le[s] + ri[j];\n            while (true) {\n                int\
    \ r = -1;\n                D d = numeric_limits<D>::max();\n                for\
    \ (int j = 0; j < m; j++) {\n                    if (!r_u[j] && min_cost[j] <\
    \ d) {\n                        r = j;\n                        d = min_cost[j];\n\
    \                    }\n                }\n                for (int i = 0; i <\
    \ n; i++) if (l_u[i]) le[i] -= d;\n                for (int j = 0; j < m; j++)\
    \ {\n                    if (r_u[j]) ri[j] += d;\n                    else min_cost[j]\
    \ -= d;\n                }\n                tr[r] = min_l[r];\n              \
    \  int l = to_l[r];\n                if (l == -1) {\n                    while\
    \ (r != -1) {\n                        int nl = tr[r], nr = to_r[nl];\n      \
    \                  to_l[r] = nl; to_r[nl] = r;\n                        r = nr;\n\
    \                    }\n                    break;\n                }\n      \
    \          l_u[l] = r_u[r] = true;\n                for (int j = 0; j < m; j++)\
    \ {\n                    D cost = c[l][j] + le[l] + ri[j];\n                 \
    \   if (cost < min_cost[j]) {\n                        min_l[j] = l;\n       \
    \                 min_cost[j] = cost;\n                    }\n               \
    \ }\n            }\n        }\n        perm = to_r;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/hungarian.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/hungarian.hpp
layout: document
redirect_from:
- /library/src/graph/hungarian.hpp
- /library/src/graph/hungarian.hpp.html
title: src/graph/hungarian.hpp
---
