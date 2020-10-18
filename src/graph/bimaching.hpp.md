---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/datastructure/simplequeue.hpp
    title: src/datastructure/simplequeue.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/csr.hpp
    title: src/graph/csr.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/bimaching.test.cpp
    title: src/bimaching.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: datastructure/simplequeue.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n#include \"datastructure/simplequeue.hpp\"\n#include \"graph/csr.hpp\"\
    \n\nstruct BipartiteMaching {\n  public:\n    int n, m;\n    V<int> lmt, rmt;\n\
    \n    BipartiteMaching(int _n, int _m, V<pair<int, int>> edges)\n        : n(_n),\
    \ m(_m), lmt(n, -1), rmt(m, -1), dist(m) {\n        for (auto e : edges) {\n \
    \           int l, r;\n            tie(l, r) = e;\n            if (lmt[l] == -1\
    \ && rmt[r] == -1) {\n                lmt[l] = r;\n                rmt[r] = l;\n\
    \            }\n        }\n        lg = CSR(n, edges);\n        for (auto& e :\
    \ edges) swap(e.first, e.second);\n        rg = CSR(m, edges);\n\n        while\
    \ (true) {\n            bfs();\n            // if (trg_dist >= 20) break;\n  \
    \          if (trg_dist == TEN(9)) break;\n            bool f = dfs();\n     \
    \       assert(f);\n        }\n    }\n\n  private:\n    CSR lg, rg;\n\n    int\
    \ trg_dist;\n    V<int> dist;\n    SimpleQueue<int> que;\n    void bfs() {\n \
    \       trg_dist = TEN(9);\n        que.clear();\n        for (int i = 0; i <\
    \ m; i++) {\n            if (rmt[i] == -1) {\n                dist[i] = 0;\n \
    \               que.push(i);\n            } else {\n                dist[i] =\
    \ TEN(9);\n            }\n        }\n        while (!que.empty()) {\n        \
    \    int q = que.front();\n            que.pop();\n            int distq = dist[q];\n\
    \            for (int pid = rg.start[q]; pid < rg.start[q + 1]; pid++) {\n   \
    \             int p = rg.to[pid];\n                int next = lmt[p];\n      \
    \          if (next == -1) {\n                    trg_dist = distq + 1;\n    \
    \                return;\n                }\n                if (dist[next] ==\
    \ TEN(9)) {\n                    dist[next] = distq + 1;\n                   \
    \ que.push(next);\n                }\n            }\n        }\n    }\n    bool\
    \ dfs() {\n        bool update = false;\n        for (int i = 0; i < n; i++) {\n\
    \            if (lmt[i] == -1 && dfs(i, trg_dist)) {\n                update =\
    \ true;\n            }\n        }\n        return update;\n    }\n    bool dfs(int\
    \ p, int distp) {\n        int st = lg.start[p], ls = lg.start[p + 1];\n     \
    \   for (int qid = st; qid < ls; qid++) {\n            int q = lg.to[qid];\n \
    \           if (distp - 1 == dist[q]) {\n                int next = rmt[q];\n\
    \                if (next != -1) {\n                    dist[q] = TEN(9);\n  \
    \                  if (!dfs(next, distp - 1)) continue;\n                }\n \
    \               lmt[p] = q;\n                rmt[q] = p;\n                return\
    \ true;\n            }\n        }\n        return false;\n    }\n};\n"
  dependsOn:
  - src/datastructure/simplequeue.hpp
  - src/graph/csr.hpp
  isVerificationFile: false
  path: src/graph/bimaching.hpp
  requiredBy: []
  timestamp: '2020-07-12 20:41:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/bimaching.test.cpp
documentation_of: src/graph/bimaching.hpp
layout: document
redirect_from:
- /library/src/graph/bimaching.hpp
- /library/src/graph/bimaching.hpp.html
title: src/graph/bimaching.hpp
---
