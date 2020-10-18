---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/staticrangeunion.hpp\"\nstruct StaticRangeUnion\
    \ {\n    using P = pair<int, int>;\n    int n;\n    VV<P> ques;\n    StaticRangeUnion(int\
    \ _n = 0) : n(_n), ques(n + 1) {}\n    void merge(int a, int b, int di) {\n  \
    \      if (di == 0) return;\n        ques[min(di, n)].push_back({a, b});\n   \
    \ }\n    UnionFind exec() {\n        UnionFind uf(n);\n        V<P> que;\n   \
    \     for (int di = n; di >= 1; di--) {\n            for (auto p : ques[di]) que.push_back(p);\n\
    \            V<P> nque;\n            for (auto p : que) {\n                if\
    \ (uf.same(p.first, p.second)) continue;\n                uf.merge(p.first, p.second);\n\
    \                nque.push_back({p.first + 1, p.second + 1});\n            }\n\
    \            que = nque;\n        }\n        return uf;\n    }\n};\n"
  code: "struct StaticRangeUnion {\n    using P = pair<int, int>;\n    int n;\n  \
    \  VV<P> ques;\n    StaticRangeUnion(int _n = 0) : n(_n), ques(n + 1) {}\n   \
    \ void merge(int a, int b, int di) {\n        if (di == 0) return;\n        ques[min(di,\
    \ n)].push_back({a, b});\n    }\n    UnionFind exec() {\n        UnionFind uf(n);\n\
    \        V<P> que;\n        for (int di = n; di >= 1; di--) {\n            for\
    \ (auto p : ques[di]) que.push_back(p);\n            V<P> nque;\n            for\
    \ (auto p : que) {\n                if (uf.same(p.first, p.second)) continue;\n\
    \                uf.merge(p.first, p.second);\n                nque.push_back({p.first\
    \ + 1, p.second + 1});\n            }\n            que = nque;\n        }\n  \
    \      return uf;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/staticrangeunion.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/staticrangeunion.hpp
layout: document
redirect_from:
- /library/src/datastructure/staticrangeunion.hpp
- /library/src/datastructure/staticrangeunion.hpp.html
title: src/datastructure/staticrangeunion.hpp
---
