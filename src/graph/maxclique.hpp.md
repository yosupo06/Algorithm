---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/max_clique.test.cpp
    title: src/max_clique.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n\ntemplate <int N, class E> struct\
    \ MaxClique {\n    using B = bitset<N>;\n    int n;\n    V<B> g, col_buf;\n  \
    \  V<int> clique, now;\n    struct P {\n        int id, col, deg;\n    };\n  \
    \  VV<P> rems;\n    void dfs(int dps = 0) {\n        if (clique.size() < now.size())\
    \ clique = now;\n        auto& rem = rems[dps];\n        sort(rem.begin(), rem.end(),\
    \ [&](P a, P b) { return a.deg > b.deg; });\n        int max_c = 1;\n        for\
    \ (auto& p : rem) {\n            p.col = 0;\n            while ((g[p.id] & col_buf[p.col]).any())\
    \ p.col++;\n            max_c = max(max_c, p.id + 1);\n            col_buf[p.col].set(p.id);\n\
    \        }\n        for (int i = 0; i < max_c; i++) col_buf[i].reset();\n    \
    \    sort(rem.begin(), rem.end(), [&](P a, P b) { return a.col < b.col; });\n\n\
    \        while (!rem.empty()) {\n            auto p = rem.back();\n          \
    \  if (now.size() + p.col + 1 <= clique.size()) break;\n\n            auto& nrem\
    \ = rems[dps + 1];\n            nrem.clear();\n            B bs = B();\n     \
    \       for (auto q : rem) {\n                if (g[p.id][q.id]) {\n         \
    \           nrem.push_back({q.id, -1, 0});\n                    bs.set(q.id);\n\
    \                }\n            }\n            for (auto& q : nrem) {\n      \
    \          q.deg = int((bs & g[q.id]).count());\n            }\n            now.push_back(p.id);\n\
    \            dfs(dps + 1);\n            now.pop_back();\n\n            rem.pop_back();\n\
    \        }\n    }\n\n    MaxClique(VV<E> _g) : n(int(_g.size())), g(n), col_buf(n),\
    \ rems(n + 1) {\n        for (int i = 0; i < n; i++) {\n            rems[0].push_back({i,\
    \ -1, int(_g[i].size())});\n            for (auto e : _g[i]) g[i][e.to] = 1;\n\
    \        }\n        dfs();\n    }\n};\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/graph/maxclique.hpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/max_clique.test.cpp
documentation_of: src/graph/maxclique.hpp
layout: document
redirect_from:
- /library/src/graph/maxclique.hpp
- /library/src/graph/maxclique.hpp.html
title: src/graph/maxclique.hpp
---
