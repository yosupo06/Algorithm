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
    path: src/math/modint61.hpp
    title: src/math/modint61.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
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
    aplusb.hpp\"\n\n#include \"base.hpp\"\n#include \"math/modint61.hpp\"\n#include\
    \ \"util/random.hpp\"\n\nusing Mint = ModInt61;\n\nint main() {\n    Random gen\
    \ = Random();\n    for (int ph = 0; ph < 100; ph++) {\n        ull a = gen.uniform(0ULL,\
    \ Mint::get_mod() - 1);\n        ull b = gen.uniform(0ULL, Mint::get_mod() - 1);\n\
    \        ull expect = (__uint128_t(a) + b) % Mint::get_mod();\n        ull actual\
    \ = (Mint(a) + Mint(b)).v;\n        assert(expect == actual);\n    }\n    for\
    \ (int ph = 0; ph < 100; ph++) {\n        ull a = gen.uniform(0ULL, Mint::get_mod()\
    \ - 1);\n        ull b = gen.uniform(0ULL, Mint::get_mod() - 1);\n        ull\
    \ expect = (__uint128_t(a) - b + Mint::get_mod()) % Mint::get_mod();\n       \
    \ ull actual = (Mint(a) - Mint(b)).v;\n        assert(expect == actual);\n   \
    \ }\n    for (int ph = 0; ph < 100; ph++) {\n        ull a = gen.uniform(0ULL,\
    \ Mint::get_mod() - 1);\n        ull b = gen.uniform(0ULL, Mint::get_mod() - 1);\n\
    \        ull expect = __uint128_t(a) * b % Mint::get_mod();\n        ull actual\
    \ = (Mint(a) * Mint(b)).v;\n        assert(expect == actual);\n    }\n    for\
    \ (int ph = 0; ph < 100; ph++) {\n        Mint a = Mint(gen.uniform(0ULL, Mint::get_mod()\
    \ - 1));\n        Mint ia = a.inv();\n        assert((a * ia).v == 1);\n    }\n\
    \    solve_aplusb();\n    return 0;\n}\n"
  dependsOn:
  - src/aplusb.hpp
  - src/base.hpp
  - src/math/modint61.hpp
  - src/util/random.hpp
  isVerificationFile: true
  path: src/modint61.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/modint61.test.cpp
layout: document
redirect_from:
- /verify/src/modint61.test.cpp
- /verify/src/modint61.test.cpp.html
title: src/modint61.test.cpp
---
