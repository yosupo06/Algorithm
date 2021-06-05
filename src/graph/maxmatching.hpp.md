---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf
  bundledCode: "#line 1 \"src/graph/maxmatching.hpp\"\n// Gabow Edmond's blossom algorithm\n\
    // Reference: https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf\ntemplate\
    \ <class E> struct MaxMatching {\n    int n;\n    const VV<E>& g;\n    V<int>\
    \ mt;\n\n    using P = pair<int, int>;\n    V<int> is_ev, gr_buf;\n    V<P> nx;\n\
    \    int st;\n    int group(int x) {\n        if (gr_buf[x] == -1 || is_ev[gr_buf[x]]\
    \ != st) return gr_buf[x];\n        return gr_buf[x] = group(gr_buf[x]);\n   \
    \ }\n\n    void match(int p, int b) {\n        int d = mt[p];\n        mt[p] =\
    \ b;\n        if (d == -1 || mt[d] != p) return;\n        if (nx[p].second ==\
    \ -1) {\n            mt[d] = nx[p].first;\n            match(nx[p].first, d);\n\
    \        } else {\n            match(nx[p].first, nx[p].second);\n           \
    \ match(nx[p].second, nx[p].first);\n        }\n    }\n\n    bool arg() {\n  \
    \      is_ev[st] = st;\n        gr_buf[st] = -1;\n        nx[st] = P(-1, -1);\n\
    \        queue<int> q;\n        q.push(st);\n        while (q.size()) {\n    \
    \        int a = q.front();\n            q.pop();\n            for (auto e : g[a])\
    \ {\n                int b = e.to;\n                if (b == st) continue;\n \
    \               if (mt[b] == -1) {\n                    mt[b] = a;\n         \
    \           match(a, b);\n                    return true;\n                }\n\
    \                if (is_ev[b] == st) {\n                    int x = group(a),\
    \ y = group(b);\n                    if (x == y) continue;\n                 \
    \   int z = -1;\n                    while (x != -1 || y != -1) {\n          \
    \              if (y != -1) swap(x, y);\n                        if (nx[x] ==\
    \ P(a, b)) {\n                            z = x;\n                           \
    \ break;\n                        }\n                        nx[x] = P(a, b);\n\
    \                        x = group(nx[mt[x]].first);\n                    }\n\
    \                    for (int v : {group(a), group(b)}) {\n                  \
    \      while (v != z) {\n                            q.push(v);\n            \
    \                is_ev[v] = st;\n                            gr_buf[v] = z;\n\
    \                            v = group(nx[mt[v]].first);\n                   \
    \     }\n                    }\n                } else if (is_ev[mt[b]] != st)\
    \ {\n                    is_ev[mt[b]] = st;\n                    nx[b] = P(-1,\
    \ -1);\n                    nx[mt[b]] = P(a, -1);\n                    gr_buf[mt[b]]\
    \ = b;\n                    q.push(mt[b]);\n                }\n            }\n\
    \        }\n        return false;\n    }\n    MaxMatching(const VV<E>& _g)\n \
    \       : n(int(_g.size())), g(_g), mt(n, -1), is_ev(n, -1), gr_buf(n), nx(n)\
    \ {\n        for (int i = 0; i < n; i++) {\n            for (auto e: g[i]) {\n\
    \                int j = e.to;\n                if (mt[i] == -1 && mt[j] == -1)\
    \ {\n                    mt[i] = mt[j];\n                    mt[j] = mt[i];\n\
    \                }\n            }\n        }\n        for (st = 0; st < n; st++)\n\
    \            if (mt[st] == -1) arg();\n    }\n};\n"
  code: "// Gabow Edmond's blossom algorithm\n// Reference: https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf\n\
    template <class E> struct MaxMatching {\n    int n;\n    const VV<E>& g;\n   \
    \ V<int> mt;\n\n    using P = pair<int, int>;\n    V<int> is_ev, gr_buf;\n   \
    \ V<P> nx;\n    int st;\n    int group(int x) {\n        if (gr_buf[x] == -1 ||\
    \ is_ev[gr_buf[x]] != st) return gr_buf[x];\n        return gr_buf[x] = group(gr_buf[x]);\n\
    \    }\n\n    void match(int p, int b) {\n        int d = mt[p];\n        mt[p]\
    \ = b;\n        if (d == -1 || mt[d] != p) return;\n        if (nx[p].second ==\
    \ -1) {\n            mt[d] = nx[p].first;\n            match(nx[p].first, d);\n\
    \        } else {\n            match(nx[p].first, nx[p].second);\n           \
    \ match(nx[p].second, nx[p].first);\n        }\n    }\n\n    bool arg() {\n  \
    \      is_ev[st] = st;\n        gr_buf[st] = -1;\n        nx[st] = P(-1, -1);\n\
    \        queue<int> q;\n        q.push(st);\n        while (q.size()) {\n    \
    \        int a = q.front();\n            q.pop();\n            for (auto e : g[a])\
    \ {\n                int b = e.to;\n                if (b == st) continue;\n \
    \               if (mt[b] == -1) {\n                    mt[b] = a;\n         \
    \           match(a, b);\n                    return true;\n                }\n\
    \                if (is_ev[b] == st) {\n                    int x = group(a),\
    \ y = group(b);\n                    if (x == y) continue;\n                 \
    \   int z = -1;\n                    while (x != -1 || y != -1) {\n          \
    \              if (y != -1) swap(x, y);\n                        if (nx[x] ==\
    \ P(a, b)) {\n                            z = x;\n                           \
    \ break;\n                        }\n                        nx[x] = P(a, b);\n\
    \                        x = group(nx[mt[x]].first);\n                    }\n\
    \                    for (int v : {group(a), group(b)}) {\n                  \
    \      while (v != z) {\n                            q.push(v);\n            \
    \                is_ev[v] = st;\n                            gr_buf[v] = z;\n\
    \                            v = group(nx[mt[v]].first);\n                   \
    \     }\n                    }\n                } else if (is_ev[mt[b]] != st)\
    \ {\n                    is_ev[mt[b]] = st;\n                    nx[b] = P(-1,\
    \ -1);\n                    nx[mt[b]] = P(a, -1);\n                    gr_buf[mt[b]]\
    \ = b;\n                    q.push(mt[b]);\n                }\n            }\n\
    \        }\n        return false;\n    }\n    MaxMatching(const VV<E>& _g)\n \
    \       : n(int(_g.size())), g(_g), mt(n, -1), is_ev(n, -1), gr_buf(n), nx(n)\
    \ {\n        for (int i = 0; i < n; i++) {\n            for (auto e: g[i]) {\n\
    \                int j = e.to;\n                if (mt[i] == -1 && mt[j] == -1)\
    \ {\n                    mt[i] = mt[j];\n                    mt[j] = mt[i];\n\
    \                }\n            }\n        }\n        for (st = 0; st < n; st++)\n\
    \            if (mt[st] == -1) arg();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/maxmatching.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/maxmatching.hpp
layout: document
redirect_from:
- /library/src/graph/maxmatching.hpp
- /library/src/graph/maxmatching.hpp.html
title: src/graph/maxmatching.hpp
---
