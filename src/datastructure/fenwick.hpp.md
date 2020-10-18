---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/datastructure/fenwick2d.hpp
    title: src/datastructure/fenwick2d.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/fenwick_2d_rectangle_sum.test.cpp
    title: src/fenwick_2d_rectangle_sum.test.cpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n\ntemplate <class T> struct Fenwick\
    \ {\n    int n;\n    V<T> seg;\n    Fenwick(int _n = 0) : n(_n), seg(n) {}\n \
    \   /// i\u756A\u76EE\u306E\u8981\u7D20\u306Bx\u3092\u8FFD\u52A0\u3059\u308B\n\
    \    void add(int i, T x) {\n        i++;\n        while (i <= n) {\n        \
    \    seg[i - 1] += x;\n            i += i & -i;\n        }\n    }\n    /// [0,\
    \ i)\u306Esum\n    T sum(int i) {\n        assert(0 <= i && i <= n);\n       \
    \ T s = 0;\n        while (i > 0) {\n            s += seg[i - 1];\n          \
    \  i -= i & -i;\n        }\n        return s;\n    }\n    /// [a, b)\u306Esum\n\
    \    T sum(int a, int b) {\n        assert(0 <= a && a <= b && b <= n);\n    \
    \    return sum(b) - sum(a);\n    }\n    /// sum[0, idx) >= x\u306A\u308B\u6700\
    \u5C0F\u306Eidx(sum[0, n) < x \u306A\u3089 n+1)\n    int sum_lower_bound(T x)\
    \ {\n        if (x <= 0) return 0;\n        int res = 0, len = 1;\n        while\
    \ (2 * len <= n) len *= 2;\n        for (; len >= 1; len /= 2) {\n           \
    \ if (res + len <= n && seg[res + len - 1] < x) {\n                res += len;\n\
    \                x -= seg[res - 1];\n            }\n        }\n        return\
    \ res + 1;\n    }\n};\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/datastructure/fenwick.hpp
  requiredBy:
  - src/datastructure/fenwick2d.hpp
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/fenwick_2d_rectangle_sum.test.cpp
documentation_of: src/datastructure/fenwick.hpp
layout: document
redirect_from:
- /library/src/datastructure/fenwick.hpp
- /library/src/datastructure/fenwick.hpp.html
title: src/datastructure/fenwick.hpp
---
