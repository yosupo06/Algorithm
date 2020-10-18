---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/segtree.hpp
    title: src/datastructure/segtree.hpp
  - icon: ':heavy_check_mark:'
    path: src/tree/hl.hpp
    title: src/tree/hl.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    \n#include \"base.hpp\"\n#include \"datastructure/segtree.hpp\"\n#include \"tree/hl.hpp\"\
    \n#include \"util/fast_io.hpp\"\n\nint main() {\n    Scanner sc(stdin);\n    Printer\
    \ pr(stdout);\n    int n, q;\n    sc.read(n, q);\n    V<ll> a(n);\n    for (int\
    \ i = 0; i < n; i++) {\n        sc.read(a[i]);\n    }\n    struct E {\n      \
    \  int to;\n    };\n    VV<E> g(n);\n    for (int i = 0; i < n - 1; i++) {\n \
    \       int u, v;\n        sc.read(u, v);\n        g[u].push_back({v});\n    \
    \    g[v].push_back({u});\n    }\n    auto hl = get_hl(g, 0);\n    auto seg =\n\
    \        get_simple_seg(V<ll>(n, 0), 0LL, [&](ll x, ll y) { return x + y; });\n\
    \    for (int i = 0; i < n; i++) {\n        seg.set(hl.ord(i).i, a[i]);\n    }\n\
    \    for (int i = 0; i < q; i++) {\n        int t;\n        sc.read(t);\n    \
    \    if (t == 0) {\n            int p;\n            ll x;\n            sc.read(p,\
    \ x);\n            seg.set(hl.ord(p).i, seg.single(hl.ord(p).i) + x);\n      \
    \  } else {\n            int u, v;\n            sc.read(u, v);\n            int\
    \ l = hl.lca(u, v);\n            ll sm = seg.single(hl.ord(l).i);\n          \
    \  hl.get_path(l, u, [&](HL::I x, HL::I y) { sm += seg.sum(x.i, y.i + 1); });\n\
    \            hl.get_path(l, v, [&](HL::I x, HL::I y) { sm += seg.sum(x.i, y.i\
    \ + 1); });\n            pr.writeln(sm);\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/datastructure/segtree.hpp
  - src/tree/hl.hpp
  - src/util/fast_io.hpp
  isVerificationFile: true
  path: src/hl_vertex_add_path_sum.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/hl_vertex_add_path_sum.test.cpp
layout: document
redirect_from:
- /verify/src/hl_vertex_add_path_sum.test.cpp
- /verify/src/hl_vertex_add_path_sum.test.cpp.html
title: src/hl_vertex_add_path_sum.test.cpp
---
