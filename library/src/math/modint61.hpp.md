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


# :heavy_check_mark: src/math/modint61.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fb2ef479237c7a939531a404fd0e5cb7">src/math</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/math/modint61.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 18:23:53+09:00




## Depends on

* :question: <a href="../base.hpp.html">src/base.hpp</a>


## Required by

* :heavy_check_mark: <a href="../string/rollinghash.hpp.html">src/string/rollinghash.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/modint61.test.cpp.html">src/modint61.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/rollinghash_zalgo.test.cpp.html">src/rollinghash_zalgo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"

// ModInt of 2^61 - 1
struct ModInt61 {
    static constexpr ull MD = (1ULL << 61) - 1;
    using M = ModInt61;
    static constexpr ull get_mod() { return MD; }
    const static M G;
    ull v;
    ModInt61(ll _v = 0) { set_v(_v % MD + MD); }
    M& set_v(ull _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const {
        __uint128_t z = __uint128_t(v) * r.v;        
        return M().set_v(ull((z & ((1ULL << 61) - 1)) + (z >> 61)));
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
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 307, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 187, in _resolve
    raise BundleErrorAt(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

