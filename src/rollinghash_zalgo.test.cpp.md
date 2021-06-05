---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/comb.hpp
    title: src/math/comb.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/modint61.hpp
    title: src/math/modint61.hpp
  - icon: ':heavy_check_mark:'
    path: src/string/rollinghash.hpp
    title: src/string/rollinghash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/comb.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"string/rollinghash.hpp\"\
    \n\nint main() {\n    H::init(TEN(6));\n    Scanner sc(stdin);\n    Printer pr(stdout);\n\
    \    string s;\n    sc.read(s);\n    int n = int(s.size());\n    V<H> hs = {H()};\n\
    \    for (char c: s) {\n        H nh = hs.back() + H(c);\n        hs.push_back(nh);\n\
    \    }\n    dbg(H::powB[3]);\n    for (int i = 0; i < n; i++) {\n        int lw\
    \ = 0, up = n - i + 1;\n        while (up - lw > 1) {\n            int md = (lw\
    \ + up) / 2;\n            if (hs[md] == hs[i + md].strip_left(hs[i])) {\n    \
    \            lw = md;\n            } else {\n                up = md;\n      \
    \      }\n        }\n        pr.write(lw);\n        pr.write(' ');\n    }\n  \
    \  pr.writeln();\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/string/rollinghash.hpp
  - src/math/comb.hpp
  - src/math/modint61.hpp
  - src/util/random.hpp
  isVerificationFile: true
  path: src/rollinghash_zalgo.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/rollinghash_zalgo.test.cpp
layout: document
redirect_from:
- /verify/src/rollinghash_zalgo.test.cpp
- /verify/src/rollinghash_zalgo.test.cpp.html
title: src/rollinghash_zalgo.test.cpp
---
