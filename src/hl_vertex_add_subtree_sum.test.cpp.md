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
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n\n#include \"base.hpp\"\n#include \"datastructure/segtree.hpp\"\n#include \"\
    tree/hl.hpp\"\n#include \"util/fast_io.hpp\"\n\nint main() {\n    Scanner sc(stdin);\n\
    \    Printer pr(stdout);\n    int n, q;\n    sc.read(n, q);\n    V<ll> a(n);\n\
    \    for (int i = 0; i < n; i++) {\n        sc.read(a[i]);\n    }\n    struct\
    \ E {\n        int to;\n    };\n    VV<E> g(n);\n    for (int i = 1; i < n; i++)\
    \ {\n        int p;\n        sc.read(p);\n        g[i].push_back({p});\n     \
    \   g[p].push_back({i});\n    }\n    auto hl = get_hl(g, 0);\n    auto seg =\n\
    \        get_simple_seg(V<ll>(n, 0), 0LL, [&](ll x, ll y) { return x + y; });\n\
    \    for (int i = 0; i < n; i++) {\n        seg.set(hl.ord(i).i, a[i]);\n    }\n\
    \    for (int i = 0; i < q; i++) {\n        int t;\n        sc.read(t);\n    \
    \    if (t == 0) {\n            int p;\n            ll x;\n            sc.read(p,\
    \ x);\n            seg.set(hl.ord(p).i, seg.single(hl.ord(p).i) + x);\n      \
    \  } else {\n            int u;\n            sc.read(u);\n            ll sm =\
    \ seg.sum(hl.ord(u).i, hl.subtree_out(u).i);\n            pr.writeln(sm);\n  \
    \      }\n    }\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/datastructure/segtree.hpp
  - src/tree/hl.hpp
  - src/util/fast_io.hpp
  isVerificationFile: true
  path: src/hl_vertex_add_subtree_sum.test.cpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/hl_vertex_add_subtree_sum.test.cpp
layout: document
redirect_from:
- /verify/src/hl_vertex_add_subtree_sum.test.cpp
- /verify/src/hl_vertex_add_subtree_sum.test.cpp.html
title: src/hl_vertex_add_subtree_sum.test.cpp
---
