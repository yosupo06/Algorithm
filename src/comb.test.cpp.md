---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/aplusb.hpp
    title: src/aplusb.hpp
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/comb.hpp
    title: src/math/comb.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/dynamicmodint.hpp
    title: src/math/dynamicmodint.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/modint.hpp
    title: src/math/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    base.hpp\"\n#include \"math/modint.hpp\"\n#include \"math/dynamicmodint.hpp\"\n\
    #include \"math/comb.hpp\"\n\n#include \"aplusb.hpp\"\n\nusing Mint = ModInt<TEN(9)\
    \ + 7>;\nusing DMint = DynamicModInt;\nint main() {\n    {\n        Comb<Mint>\
    \ c(100);\n        assert(c.fact[33] * c.ifact[33] == Mint(1));\n        assert(c.fact[100]\
    \ * c.ifact[100] == Mint(1));\n    }\n    {\n        DMint::set_mod(103);\n  \
    \      Comb<DMint> c(100);\n        assert(c.fact[33] * c.ifact[33] == DMint(1));\n\
    \        assert(c.fact[100] * c.ifact[100] == DMint(1));\n    }\n\n    solve_aplusb();\n\
    \    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/math/modint.hpp
  - src/math/dynamicmodint.hpp
  - src/bitop.hpp
  - src/math/comb.hpp
  - src/aplusb.hpp
  isVerificationFile: true
  path: src/comb.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/comb.test.cpp
layout: document
redirect_from:
- /verify/src/comb.test.cpp
- /verify/src/comb.test.cpp.html
title: src/comb.test.cpp
---
