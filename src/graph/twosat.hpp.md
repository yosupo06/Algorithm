---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/graph/scc.hpp
    title: src/graph/scc.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/scc.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"graph/scc.hpp\"\n\nstruct TwoSat {\n    V<bool>\
    \ res;\n\n    struct Edge { int to; };\n    VV<Edge> g;\n\n    //(a == a_exp)\
    \ || (b == b_exp)\n    void add_cond(int a, bool a_exp, int b, bool b_exp) {\n\
    \        g[2 * a + (a_exp ? 0 : 1)].push_back(Edge{2 * b + (b_exp ? 1 : 0)});\n\
    \        g[2 * b + (b_exp ? 0 : 1)].push_back(Edge{2 * a + (a_exp ? 1 : 0)});\n\
    \    }\n    bool exec() {\n        int n = int(res.size());\n        auto s =\
    \ get_scc(g);\n        for (int i = 0; i < n; i++) {\n            if (s.id[2 *\
    \ i] == s.id[2 * i + 1]) return false;\n            res[i] = s.id[2 * i] < s.id[2\
    \ * i + 1];\n        }\n        return true;\n    }\n    TwoSat() {}\n    TwoSat(int\
    \ n) {\n        g = VV<Edge>(2 * n);\n        res = V<bool>(n);\n    }\n};\n"
  dependsOn:
  - src/graph/scc.hpp
  isVerificationFile: false
  path: src/graph/twosat.hpp
  requiredBy: []
  timestamp: '2020-05-22 19:22:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/twosat.hpp
layout: document
redirect_from:
- /library/src/graph/twosat.hpp
- /library/src/graph/twosat.hpp.html
title: src/graph/twosat.hpp
---
