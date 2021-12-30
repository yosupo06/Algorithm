---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/staticrangesum.hpp
    title: src/datastructure/staticrangesum.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"datastructure/staticrangesum.hpp\"\
    \n\nint main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n    int n,\
    \ q;\n    sc.read(n, q);\n    V<StaticRangeSum<ll, int>::P> ps(n);\n    for (int\
    \ i = 0; i < n; i++) {\n        sc.read(ps[i].x, ps[i].y, ps[i].val);\n    }\n\
    \    auto srs = StaticRangeSum<ll, int>(ps);\n    for (int i = 0; i < q; i++)\
    \ {\n        int l, d, r, u;\n        sc.read(l, d, r, u);\n        pr.writeln(srs.sum(l,\
    \ d, r, u));\n    }\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/datastructure/staticrangesum.hpp
  isVerificationFile: true
  path: src/staticrangesum_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/staticrangesum_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/src/staticrangesum_rectangle_sum.test.cpp
- /verify/src/staticrangesum_rectangle_sum.test.cpp.html
title: src/staticrangesum_rectangle_sum.test.cpp
---
