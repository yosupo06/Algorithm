---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/comb.test.cpp
    title: src/comb.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/inv_of_formal_power_series.test.cpp
    title: src/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/nft_convolution.test.cpp
    title: src/nft_convolution.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/math/modint.hpp\"\n\ntemplate <uint MD> struct ModInt\
    \ {\n    using M = ModInt;\n    static constexpr uint get_mod() { return MD; }\n\
    \    const static M G;\n    uint v;\n    ModInt(ll _v = 0) { set_v(uint(_v % MD\
    \ + MD)); }\n    M& set_v(uint _v) {\n        v = (_v < MD) ? _v : _v - MD;\n\
    \        return *this;\n    }\n    explicit operator bool() const { return v !=\
    \ 0; }\n    M operator-() const { return M() - *this; }\n    M operator+(const\
    \ M& r) const { return M().set_v(v + r.v); }\n    M operator-(const M& r) const\
    \ { return M().set_v(v + MD - r.v); }\n    M operator*(const M& r) const { return\
    \ M().set_v(uint(ull(v) * r.v % MD)); }\n    M operator/(const M& r) const { return\
    \ *this * r.inv(); }\n    M& operator+=(const M& r) { return *this = *this + r;\
    \ }\n    M& operator-=(const M& r) { return *this = *this - r; }\n    M& operator*=(const\
    \ M& r) { return *this = *this * r; }\n    M& operator/=(const M& r) { return\
    \ *this = *this / r; }\n    bool operator==(const M& r) const { return v == r.v;\
    \ }\n    M pow(ll n) const {\n        M x = *this, r = 1;\n        while (n) {\n\
    \            if (n & 1) r *= x;\n            x *= x;\n            n >>= 1;\n \
    \       }\n        return r;\n    }\n    M inv() const { return pow(MD - 2); }\n\
    \    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }\n\
    };\n// using Mint = ModInt<998244353>;\n// template<> const Mint Mint::G = Mint(3);\n"
  code: "#pragma once\n\ntemplate <uint MD> struct ModInt {\n    using M = ModInt;\n\
    \    static constexpr uint get_mod() { return MD; }\n    const static M G;\n \
    \   uint v;\n    ModInt(ll _v = 0) { set_v(uint(_v % MD + MD)); }\n    M& set_v(uint\
    \ _v) {\n        v = (_v < MD) ? _v : _v - MD;\n        return *this;\n    }\n\
    \    explicit operator bool() const { return v != 0; }\n    M operator-() const\
    \ { return M() - *this; }\n    M operator+(const M& r) const { return M().set_v(v\
    \ + r.v); }\n    M operator-(const M& r) const { return M().set_v(v + MD - r.v);\
    \ }\n    M operator*(const M& r) const { return M().set_v(uint(ull(v) * r.v %\
    \ MD)); }\n    M operator/(const M& r) const { return *this * r.inv(); }\n   \
    \ M& operator+=(const M& r) { return *this = *this + r; }\n    M& operator-=(const\
    \ M& r) { return *this = *this - r; }\n    M& operator*=(const M& r) { return\
    \ *this = *this * r; }\n    M& operator/=(const M& r) { return *this = *this /\
    \ r; }\n    bool operator==(const M& r) const { return v == r.v; }\n    M pow(ll\
    \ n) const {\n        M x = *this, r = 1;\n        while (n) {\n            if\
    \ (n & 1) r *= x;\n            x *= x;\n            n >>= 1;\n        }\n    \
    \    return r;\n    }\n    M inv() const { return pow(MD - 2); }\n    friend ostream&\
    \ operator<<(ostream& os, const M& r) { return os << r.v; }\n};\n// using Mint\
    \ = ModInt<998244353>;\n// template<> const Mint Mint::G = Mint(3);\n"
  dependsOn: []
  isVerificationFile: false
  path: src/math/modint.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/inv_of_formal_power_series.test.cpp
  - src/nft_convolution.test.cpp
  - src/comb.test.cpp
documentation_of: src/math/modint.hpp
layout: document
redirect_from:
- /library/src/math/modint.hpp
- /library/src/math/modint.hpp.html
title: src/math/modint.hpp
---
