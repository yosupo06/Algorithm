---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: src/math/dynamicmodint.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fb2ef479237c7a939531a404fd0e5cb7">src/math</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/math/dynamicmodint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Depends on

* :heavy_check_mark: <a href="../bitop.hpp.html">src/bitop.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/comb.test.cpp.html">src/comb.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/modint.test.cpp.html">src/modint.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../bitop.hpp"


struct DynamicModInt {
    using M = DynamicModInt;

  private:
    static uint MD;
    static ull iMD;
    uint v = 0;

  public:
    static void set_mod(uint _MD) {
        assert(2 <= _MD);
        MD = _MD;
        iMD = ull(-1) / _MD + 1;
    }
    DynamicModInt() {}
    DynamicModInt(ll _v) { set_v(uint(_v % MD + MD)); }
    uint val() const { return v; }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    /*
    u32 fact_fast(u32 n, u32 mod) {
      u64 imod = u64(-1) / mod + 1; // ceil((1<<64) / mod);
      auto mul_mod = [&](u32 a, u32 b) {
        u64 c = u64(a) * b;
        u64 d = (__uint128_t(c) * imod) >> 64;
        u64 e = (c - d * mod + mod);
        //return e;
        return (e < mod) ? e : e - mod;
      };
      u32 ret = 1;
      for (int i = 1; i <= n; ++i) ret = mul_mod(ret, i);
      return ret;
    }
    */
    M operator*(const M& r) const {
        ull c = ull(v) * r.v;
        ull d = (__uint128_t(c) * iMD) >> 64;
        return M().set_v(uint(c - d * MD + MD));
    }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const {
        pair<uint, ll> p = {MD, 0}, q = {v, 1};
        while (q.first) {
            uint t = p.first / q.first;
            p.first -= t * q.first;
            p.second -= t * q.second;
            swap(p, q);
        }
        return M(p.second);
    }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
uint DynamicModInt::MD;
ull DynamicModInt::iMD;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/math/dynamicmodint.hpp"

#line 2 "src/bitop.hpp"
// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }
#line 4 "src/math/dynamicmodint.hpp"


struct DynamicModInt {
    using M = DynamicModInt;

  private:
    static uint MD;
    static ull iMD;
    uint v = 0;

  public:
    static void set_mod(uint _MD) {
        assert(2 <= _MD);
        MD = _MD;
        iMD = ull(-1) / _MD + 1;
    }
    DynamicModInt() {}
    DynamicModInt(ll _v) { set_v(uint(_v % MD + MD)); }
    uint val() const { return v; }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    /*
    u32 fact_fast(u32 n, u32 mod) {
      u64 imod = u64(-1) / mod + 1; // ceil((1<<64) / mod);
      auto mul_mod = [&](u32 a, u32 b) {
        u64 c = u64(a) * b;
        u64 d = (__uint128_t(c) * imod) >> 64;
        u64 e = (c - d * mod + mod);
        //return e;
        return (e < mod) ? e : e - mod;
      };
      u32 ret = 1;
      for (int i = 1; i <= n; ++i) ret = mul_mod(ret, i);
      return ret;
    }
    */
    M operator*(const M& r) const {
        ull c = ull(v) * r.v;
        ull d = (__uint128_t(c) * iMD) >> 64;
        return M().set_v(uint(c - d * MD + MD));
    }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const {
        pair<uint, ll> p = {MD, 0}, q = {v, 1};
        while (q.first) {
            uint t = p.first / q.first;
            p.first -= t * q.first;
            p.second -= t * q.second;
            swap(p, q);
        }
        return M(p.second);
    }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
uint DynamicModInt::MD;
ull DynamicModInt::iMD;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

