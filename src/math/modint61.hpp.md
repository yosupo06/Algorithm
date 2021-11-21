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
    path: src/modint61.test.cpp
    title: src/modint61.test.cpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n\n// ModInt of 2^61 - 1\nstruct ModInt61\
    \ {\n    static constexpr ull MD = (1ULL << 61) - 1;\n    using M = ModInt61;\n\
    \    static constexpr ull get_mod() { return MD; }\n    const static M G;\n  \
    \  ull v;\n    ModInt61(ll _v = 0) { set_v(_v % MD + MD); }\n    M& set_v(ull\
    \ _v) {\n        v = (_v < MD) ? _v : _v - MD;\n        return *this;\n    }\n\
    \    explicit operator bool() const { return v != 0; }\n    M operator-() const\
    \ { return M() - *this; }\n    M operator+(const M& r) const { return M().set_v(v\
    \ + r.v); }\n    M operator-(const M& r) const { return M().set_v(v + MD - r.v);\
    \ }\n    M operator*(const M& r) const {\n        __uint128_t z = __uint128_t(v)\
    \ * r.v;        \n        return M().set_v(ull((z & ((1ULL << 61) - 1)) + (z >>\
    \ 61)));\n    }\n    M operator/(const M& r) const { return *this * r.inv(); }\n\
    \    M& operator+=(const M& r) { return *this = *this + r; }\n    M& operator-=(const\
    \ M& r) { return *this = *this - r; }\n    M& operator*=(const M& r) { return\
    \ *this = *this * r; }\n    M& operator/=(const M& r) { return *this = *this /\
    \ r; }\n    bool operator==(const M& r) const { return v == r.v; }\n    M pow(ll\
    \ n) const {\n        M x = *this, r = 1;\n        while (n) {\n            if\
    \ (n & 1) r *= x;\n            x *= x;\n            n >>= 1;\n        }\n    \
    \    return r;\n    }\n    M inv() const { return pow(MD - 2); }\n    friend ostream&\
    \ operator<<(ostream& os, const M& r) { return os << r.v; }\n};\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/math/modint61.hpp
  requiredBy:
  - src/string/rollinghash.hpp
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/rollinghash_zalgo.test.cpp
  - src/modint61.test.cpp
documentation_of: src/math/modint61.hpp
layout: document
redirect_from:
- /library/src/math/modint61.hpp
- /library/src/math/modint61.hpp.html
title: src/math/modint61.hpp
---
