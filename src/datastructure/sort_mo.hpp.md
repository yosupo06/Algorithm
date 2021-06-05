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
  bundledCode: "#line 1 \"src/datastructure/sort_mo.hpp\"\n// \u666E\u901A\u306Bsort\u3057\
    \u305F\u65B9\u304C\u65E9\u304F\u306A\u3044\uFF1F\u56F0\u3063\u305F\u306D\ntemplate\
    \ <class Q> void sort_mo(V<Q>& ques) {\n    auto dist = [&](Q x, Q y) { return\
    \ abs(x.l - y.l) + abs(x.r - y.r); };\n    int n = int(ques.size());\n    if (n\
    \ <= 1) return;\n\n    // ordered by manhattan mst (tsp approx)\n    {\n     \
    \   VV<int> tr(n);\n        V<pair<int, int>> ps(n);\n        for (int i = 0;\
    \ i < n; i++) {\n            ps[i] = {ques[i].l, ques[i].r};\n        }\n    \
    \    auto edges = manhattan_mst(ps);\n        for (auto e : edges) {\n       \
    \     tr[e.first].push_back(e.second);\n            tr[e.second].push_back(e.first);\n\
    \        }\n        V<Q> nques;\n        auto dfs = [&](auto self, int p, int\
    \ b) -> void {\n            nques.push_back(ques[p]);\n            for (auto d\
    \ : tr[p]) {\n                if (d == b) continue;\n                self(self,\
    \ d, p);\n            }\n        };\n        dfs(dfs, 0, -1);\n        ques =\
    \ nques;\n    }\n    // 2-opt\n    for (int ph = 0; ph < 10; ph++) {\n       \
    \ for (int i = 1; i < n; i++) {\n            for (int j = i + 1; j < min(i + 10,\
    \ n - 1); j++) {\n                ll pre =\n                    dist(ques[i -\
    \ 1], ques[i]) + dist(ques[j], ques[j + 1]);\n                ll now =\n     \
    \               dist(ques[i - 1], ques[j]) + dist(ques[i], ques[j + 1]);\n   \
    \             if (now < pre) {\n                    reverse(ques.begin() + i,\
    \ ques.begin() + j + 1);\n                }\n            }\n        }\n    }\n\
    \    // reverse first\n    {\n        int mi = TEN(9), idx = -1;\n        for\
    \ (int i = 0; i < n - 1; i++) {\n            int nw = abs(ques[i].l - ques[i].r)\
    \ + dist(ques[0], ques[i + 1]);\n            if (nw < mi) {\n                mi\
    \ = nw;\n                idx = i;\n            }\n        }\n        reverse(ques.begin(),\
    \ ques.begin() + idx + 1);\n    }\n    // reverse last\n    {\n        int mi\
    \ = TEN(9), idx = -1;\n        for (int i = 1; i < n; i++) {\n            int\
    \ nw = dist(ques[i - 1], ques[n - 1]);\n            if (nw < mi) {\n         \
    \       mi = nw;\n                idx = i;\n            }\n        }\n       \
    \ reverse(ques.begin() + idx, ques.end());\n    }\n}\n"
  code: "// \u666E\u901A\u306Bsort\u3057\u305F\u65B9\u304C\u65E9\u304F\u306A\u3044\
    \uFF1F\u56F0\u3063\u305F\u306D\ntemplate <class Q> void sort_mo(V<Q>& ques) {\n\
    \    auto dist = [&](Q x, Q y) { return abs(x.l - y.l) + abs(x.r - y.r); };\n\
    \    int n = int(ques.size());\n    if (n <= 1) return;\n\n    // ordered by manhattan\
    \ mst (tsp approx)\n    {\n        VV<int> tr(n);\n        V<pair<int, int>> ps(n);\n\
    \        for (int i = 0; i < n; i++) {\n            ps[i] = {ques[i].l, ques[i].r};\n\
    \        }\n        auto edges = manhattan_mst(ps);\n        for (auto e : edges)\
    \ {\n            tr[e.first].push_back(e.second);\n            tr[e.second].push_back(e.first);\n\
    \        }\n        V<Q> nques;\n        auto dfs = [&](auto self, int p, int\
    \ b) -> void {\n            nques.push_back(ques[p]);\n            for (auto d\
    \ : tr[p]) {\n                if (d == b) continue;\n                self(self,\
    \ d, p);\n            }\n        };\n        dfs(dfs, 0, -1);\n        ques =\
    \ nques;\n    }\n    // 2-opt\n    for (int ph = 0; ph < 10; ph++) {\n       \
    \ for (int i = 1; i < n; i++) {\n            for (int j = i + 1; j < min(i + 10,\
    \ n - 1); j++) {\n                ll pre =\n                    dist(ques[i -\
    \ 1], ques[i]) + dist(ques[j], ques[j + 1]);\n                ll now =\n     \
    \               dist(ques[i - 1], ques[j]) + dist(ques[i], ques[j + 1]);\n   \
    \             if (now < pre) {\n                    reverse(ques.begin() + i,\
    \ ques.begin() + j + 1);\n                }\n            }\n        }\n    }\n\
    \    // reverse first\n    {\n        int mi = TEN(9), idx = -1;\n        for\
    \ (int i = 0; i < n - 1; i++) {\n            int nw = abs(ques[i].l - ques[i].r)\
    \ + dist(ques[0], ques[i + 1]);\n            if (nw < mi) {\n                mi\
    \ = nw;\n                idx = i;\n            }\n        }\n        reverse(ques.begin(),\
    \ ques.begin() + idx + 1);\n    }\n    // reverse last\n    {\n        int mi\
    \ = TEN(9), idx = -1;\n        for (int i = 1; i < n; i++) {\n            int\
    \ nw = dist(ques[i - 1], ques[n - 1]);\n            if (nw < mi) {\n         \
    \       mi = nw;\n                idx = i;\n            }\n        }\n       \
    \ reverse(ques.begin() + idx, ques.end());\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/sort_mo.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/sort_mo.hpp
layout: document
redirect_from:
- /library/src/datastructure/sort_mo.hpp
- /library/src/datastructure/sort_mo.hpp.html
title: src/datastructure/sort_mo.hpp
---
