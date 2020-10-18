---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/comb.test.cpp
    title: src/comb.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/modint.test.cpp
    title: src/modint.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/math/dynamicmodint.hpp\"\n\n#line 2 \"src/bitop.hpp\"\
    \n// bit op\nint popcnt(uint x) { return __builtin_popcount(x); }\nint popcnt(ull\
    \ x) { return __builtin_popcountll(x); }\nint bsr(uint x) { return 31 - __builtin_clz(x);\
    \ }\nint bsr(ull x) { return 63 - __builtin_clzll(x); }\nint bsf(uint x) { return\
    \ __builtin_ctz(x); }\nint bsf(ull x) { return __builtin_ctzll(x); }\n#line 4\
    \ \"src/math/dynamicmodint.hpp\"\n\n\nstruct DynamicModInt {\n    using M = DynamicModInt;\n\
    \n  private:\n    static uint MD;\n    static ull iMD;\n    uint v = 0;\n\n  public:\n\
    \    static void set_mod(uint _MD) {\n        assert(2 <= _MD);\n        MD =\
    \ _MD;\n        iMD = ull(-1) / _MD + 1;\n    }\n    DynamicModInt() {}\n    DynamicModInt(ll\
    \ _v) { set_v(uint(_v % MD + MD)); }\n    uint val() const { return v; }\n   \
    \ M& set_v(uint _v) {\n        v = (_v < MD) ? _v : _v - MD;\n        return *this;\n\
    \    }\n    explicit operator bool() const { return v != 0; }\n    M operator-()\
    \ const { return M() - *this; }\n    M operator+(const M& r) const { return M().set_v(v\
    \ + r.v); }\n    M operator-(const M& r) const { return M().set_v(v + MD - r.v);\
    \ }\n    /*\n    u32 fact_fast(u32 n, u32 mod) {\n      u64 imod = u64(-1) / mod\
    \ + 1; // ceil((1<<64) / mod);\n      auto mul_mod = [&](u32 a, u32 b) {\n   \
    \     u64 c = u64(a) * b;\n        u64 d = (__uint128_t(c) * imod) >> 64;\n  \
    \      u64 e = (c - d * mod + mod);\n        //return e;\n        return (e <\
    \ mod) ? e : e - mod;\n      };\n      u32 ret = 1;\n      for (int i = 1; i <=\
    \ n; ++i) ret = mul_mod(ret, i);\n      return ret;\n    }\n    */\n    M operator*(const\
    \ M& r) const {\n        ull c = ull(v) * r.v;\n        ull d = (__uint128_t(c)\
    \ * iMD) >> 64;\n        return M().set_v(uint(c - d * MD + MD));\n    }\n   \
    \ M operator/(const M& r) const { return *this * r.inv(); }\n    M& operator+=(const\
    \ M& r) { return *this = *this + r; }\n    M& operator-=(const M& r) { return\
    \ *this = *this - r; }\n    M& operator*=(const M& r) { return *this = *this *\
    \ r; }\n    M& operator/=(const M& r) { return *this = *this / r; }\n    bool\
    \ operator==(const M& r) const { return v == r.v; }\n    M pow(ll n) const {\n\
    \        M x = *this, r = 1;\n        while (n) {\n            if (n & 1) r *=\
    \ x;\n            x *= x;\n            n >>= 1;\n        }\n        return r;\n\
    \    }\n    M inv() const {\n        pair<uint, ll> p = {MD, 0}, q = {v, 1};\n\
    \        while (q.first) {\n            uint t = p.first / q.first;\n        \
    \    p.first -= t * q.first;\n            p.second -= t * q.second;\n        \
    \    swap(p, q);\n        }\n        return M(p.second);\n    }\n    friend ostream&\
    \ operator<<(ostream& os, const M& r) { return os << r.v; }\n};\nuint DynamicModInt::MD;\n\
    ull DynamicModInt::iMD;\n"
  code: "#pragma once\n\n#include \"../bitop.hpp\"\n\n\nstruct DynamicModInt {\n \
    \   using M = DynamicModInt;\n\n  private:\n    static uint MD;\n    static ull\
    \ iMD;\n    uint v = 0;\n\n  public:\n    static void set_mod(uint _MD) {\n  \
    \      assert(2 <= _MD);\n        MD = _MD;\n        iMD = ull(-1) / _MD + 1;\n\
    \    }\n    DynamicModInt() {}\n    DynamicModInt(ll _v) { set_v(uint(_v % MD\
    \ + MD)); }\n    uint val() const { return v; }\n    M& set_v(uint _v) {\n   \
    \     v = (_v < MD) ? _v : _v - MD;\n        return *this;\n    }\n    explicit\
    \ operator bool() const { return v != 0; }\n    M operator-() const { return M()\
    \ - *this; }\n    M operator+(const M& r) const { return M().set_v(v + r.v); }\n\
    \    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }\n    /*\n\
    \    u32 fact_fast(u32 n, u32 mod) {\n      u64 imod = u64(-1) / mod + 1; // ceil((1<<64)\
    \ / mod);\n      auto mul_mod = [&](u32 a, u32 b) {\n        u64 c = u64(a) *\
    \ b;\n        u64 d = (__uint128_t(c) * imod) >> 64;\n        u64 e = (c - d *\
    \ mod + mod);\n        //return e;\n        return (e < mod) ? e : e - mod;\n\
    \      };\n      u32 ret = 1;\n      for (int i = 1; i <= n; ++i) ret = mul_mod(ret,\
    \ i);\n      return ret;\n    }\n    */\n    M operator*(const M& r) const {\n\
    \        ull c = ull(v) * r.v;\n        ull d = (__uint128_t(c) * iMD) >> 64;\n\
    \        return M().set_v(uint(c - d * MD + MD));\n    }\n    M operator/(const\
    \ M& r) const { return *this * r.inv(); }\n    M& operator+=(const M& r) { return\
    \ *this = *this + r; }\n    M& operator-=(const M& r) { return *this = *this -\
    \ r; }\n    M& operator*=(const M& r) { return *this = *this * r; }\n    M& operator/=(const\
    \ M& r) { return *this = *this / r; }\n    bool operator==(const M& r) const {\
    \ return v == r.v; }\n    M pow(ll n) const {\n        M x = *this, r = 1;\n \
    \       while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n   \
    \         n >>= 1;\n        }\n        return r;\n    }\n    M inv() const {\n\
    \        pair<uint, ll> p = {MD, 0}, q = {v, 1};\n        while (q.first) {\n\
    \            uint t = p.first / q.first;\n            p.first -= t * q.first;\n\
    \            p.second -= t * q.second;\n            swap(p, q);\n        }\n \
    \       return M(p.second);\n    }\n    friend ostream& operator<<(ostream& os,\
    \ const M& r) { return os << r.v; }\n};\nuint DynamicModInt::MD;\null DynamicModInt::iMD;\n"
  dependsOn:
  - src/bitop.hpp
  isVerificationFile: false
  path: src/math/dynamicmodint.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/comb.test.cpp
  - src/modint.test.cpp
documentation_of: src/math/dynamicmodint.hpp
layout: document
redirect_from:
- /library/src/math/dynamicmodint.hpp
- /library/src/math/dynamicmodint.hpp.html
title: src/math/dynamicmodint.hpp
---
