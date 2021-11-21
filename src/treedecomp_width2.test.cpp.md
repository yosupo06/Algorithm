---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashmap.hpp
    title: src/datastructure/hashmap.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashset.hpp
    title: src/datastructure/hashset.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/simplequeue.hpp
    title: src/datastructure/simplequeue.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/primitive.hpp
    title: src/graph/primitive.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/treedecomp.hpp
    title: src/graph/treedecomp.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/hash.hpp
    title: src/util/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_decomposition_width_2
    links:
    - https://judge.yosupo.jp/problem/tree_decomposition_width_2
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_decomposition_width_2\"\
    \n\n#include \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"graph/treedecomp.hpp\"\
    \n\nint main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n\n    string\
    \ s;\n    sc.read(s, s);\n    int n, m;\n    sc.read(n, m);\n    VV<SimpleEdge>\
    \ g(n);\n    for (int i = 0; i < m; i++) {\n        int a, b;\n        sc.read(a,\
    \ b); a--; b--;\n        g[a].push_back({b});\n        g[b].push_back({a});\n\
    \    }\n\n    auto td = decomp_width2(g);\n    int K = int(td.bags.size());\n\
    \    if (K == 0) {\n        pr.writeln(-1);\n        return 0;\n    }\n    pr.writeln(\"\
    s\", \"td\", K, 2, n);\n\n    for (int i = 0; i < K; i++) {\n        pr.write(\"\
    b\", i + 1);\n        for (int j: td.bags[i]) {\n            pr.write(' ');\n\
    \            pr.write(j + 1);\n        }\n        pr.writeln();\n    }\n    for\
    \ (int i = 0; i < K; i++) {\n        for (auto e: td.tr[i]) {\n            int\
    \ j = e.to;\n            if (i < j) {\n                pr.writeln(i + 1, j + 1);\n\
    \            }\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/graph/treedecomp.hpp
  - src/graph/primitive.hpp
  - src/datastructure/hashset.hpp
  - src/util/hash.hpp
  - src/util/random.hpp
  - src/datastructure/hashmap.hpp
  - src/datastructure/simplequeue.hpp
  isVerificationFile: true
  path: src/treedecomp_width2.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/treedecomp_width2.test.cpp
layout: document
redirect_from:
- /verify/src/treedecomp_width2.test.cpp
- /verify/src/treedecomp_width2.test.cpp.html
title: src/treedecomp_width2.test.cpp
---
