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
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/rollinghash_zalgo.test.cpp
    title: src/rollinghash_zalgo.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/comb.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n#include \"math/comb.hpp\"\n#include \"math/modint61.hpp\"\
    \n#include \"util/random.hpp\"\n\nstruct H {\n  private:\n    static ModInt61\
    \ B;\n    static ModInt61 iB;\n    static V<ModInt61> powB, powiB;\n\n  public:\n\
    \    static void init(int n) {\n        powB = powTable(n, B);\n        powiB\
    \ = powTable(n, iB);\n    }\n    int le = 0;\n    ModInt61 h;\n    H() : le(0),\
    \ h(0) {}\n    H(int _le, ModInt61 _h) : le(_le), h(_h) {}\n    H(int c) : le(1),\
    \ h(c) {}\n    // H(l) + H(r) = H(lr)\n    H operator+(const H& r) const { return\
    \ H{le + r.le, h + r.h * powB[le]}; }\n    H& operator+=(const H& r) { return\
    \ *this = *this + r; }\n\n    bool operator==(const H& r) const { return le ==\
    \ r.le && h == r.h; }\n    bool operator!=(const H& r) const { return !(*this\
    \ == r); }\n    // H(lr).strip_left(H(l)) = H(r)\n    H strip_left(const H& l)\
    \ const {\n        return H{le - l.le, (h - l.h) * powiB[l.le]};\n    }\n    //\
    \ H(lr).strip_right(H(r)) = H(l)\n    H strip_right(const H& r) const {\n    \
    \    return H{le - r.le, h - r.h * powB[le - r.le]};\n    }\n};\nModInt61 H::B\
    \ =\n    ModInt61(global_runtime_gen().uniform(0ULL, ModInt61::get_mod() - 1));\n\
    ModInt61 H::iB = H::B.inv();\nV<ModInt61> H::powB, H::powiB;\n"
  dependsOn:
  - src/math/comb.hpp
  - src/base.hpp
  - src/math/modint61.hpp
  - src/util/random.hpp
  isVerificationFile: false
  path: src/string/rollinghash.hpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/rollinghash_zalgo.test.cpp
documentation_of: src/string/rollinghash.hpp
layout: document
redirect_from:
- /library/src/string/rollinghash.hpp
- /library/src/string/rollinghash.hpp.html
title: src/string/rollinghash.hpp
---
