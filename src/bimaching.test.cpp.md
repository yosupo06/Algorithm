---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/simplequeue.hpp
    title: src/datastructure/simplequeue.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/bimaching.hpp
    title: src/graph/bimaching.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/csr.hpp
    title: src/graph/csr.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: datastructure/simplequeue.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n\
    #include \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"graph/bimaching.hpp\"\
    \n\nint main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n    int l,\
    \ r, m;\n    sc.read(l, r, m);\n    V<pair<int, int>> edges(m);\n    for (int\
    \ i = 0; i < m; i++) {\n        sc.read(edges[i].first, edges[i].second);\n  \
    \  }\n    BipartiteMaching bm(l, r, edges);\n    V<pair<int, int>> ans;\n    for\
    \ (int i = 0; i < l; i++) {\n        if (bm.lmt[i] != -1) {\n            ans.push_back({i,\
    \ bm.lmt[i]});\n        }\n    }\n    pr.writeln(ans.size());\n    for (auto p\
    \ : ans) {\n        pr.writeln(p.first, p.second);\n    }\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/graph/bimaching.hpp
  - src/datastructure/simplequeue.hpp
  - src/graph/csr.hpp
  isVerificationFile: true
  path: src/bimaching.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/bimaching.test.cpp
layout: document
redirect_from:
- /verify/src/bimaching.test.cpp
- /verify/src/bimaching.test.cpp.html
title: src/bimaching.test.cpp
---
