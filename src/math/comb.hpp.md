---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/string/rollinghash.hpp
    title: src/string/rollinghash.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/comb.test.cpp
    title: src/comb.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/rollinghash_zalgo.test.cpp
    title: src/rollinghash_zalgo.test.cpp
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
  code: "#pragma once\n\n#include \"base.hpp\"\n\ntemplate <class Mint>\nV<Mint> powTable(int\
    \ n, Mint x) {\n    V<Mint> table(n + 1);\n    table[0] = Mint(1);\n    for (int\
    \ i = 1; i <= n; i++) {\n        table[i] = table[i - 1] * x;\n    }\n    return\
    \ table;\n}\n\ntemplate<class Mint>\nstruct Comb {\n    int max_n;\n    V<Mint>\
    \ fact, ifact;\n    Comb() {}\n    Comb(int n) : max_n(n) {\n        fact = ifact\
    \ = V<Mint>(n + 1);\n        fact[0] = Mint(1);\n        for (int i = 1; i <=\
    \ n; i++) fact[i] = fact[i - 1] * i;\n        ifact[n] = fact[n].inv();\n    \
    \    for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;\n    }\n\n    Mint\
    \ C(int n, int k) {\n        if (n < k || n < 0) return Mint(0);\n        assert(0\
    \ <= k && k <= n && n <= max_n);\n        return fact[n] * ifact[k] * ifact[n\
    \ - k];\n    }\n\n    // n\u500B\u306E\u533A\u5225\u51FA\u6765\u306A\u3044\u30DC\
    \u30FC\u30EB\u3092k\u500B\u306E\u7BB1\u306B\u5165\u308C\u308B\u5165\u308C\u65B9\
    \n    Mint H(int n, int k) {\n        if (n == 0 && k == 0) return Mint(1);\n\
    \        return C(n + k - 1, n);\n    }\n};\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/math/comb.hpp
  requiredBy:
  - src/string/rollinghash.hpp
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/comb.test.cpp
  - src/rollinghash_zalgo.test.cpp
documentation_of: src/math/comb.hpp
layout: document
redirect_from:
- /library/src/math/comb.hpp
- /library/src/math/comb.hpp.html
title: src/math/comb.hpp
---
