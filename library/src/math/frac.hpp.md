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


# :warning: src/math/frac.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fb2ef479237c7a939531a404fd0e5cb7">src/math</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/math/frac.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-22 19:22:07+09:00




## Depends on

* :heavy_check_mark: <a href="../bitop.hpp.html">src/bitop.hpp</a>
* :warning: <a href="primitive.hpp.html">src/math/primitive.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "math/primitive.hpp"


template <class I> struct Frac {
    I a, b;  // a / b
    Frac(I _a = 0) : a(_a), b(1) {}
    Frac(I _a, I _b) {
        I g = gcd(_a, _b);
        if (_b < 0) g = -g;
        a = _a / g;
        b = _b / g;
    }
    Frac operator-() const {
        Frac f;
        f.a = -a;
        f.b = b;
        return f;
    }
    Frac operator+(const Frac& r) const { return {r.b * a + b * r.a, b * r.b}; }
    Frac operator-(const Frac& r) const { return *this + (-r); }
    Frac operator*(const Frac& r) const { return {a * r.a, b * r.b}; }
    Frac operator/(const Frac& r) const { return {a * r.b, b * r.a}; }
    Frac& operator+=(const Frac& r) { return *this = *this + r; }
    Frac& operator-=(const Frac& r) { return *this = *this - r; }
    Frac& operator*=(const Frac& r) { return *this = *this * r; }
    Frac& operator/=(const Frac& r) { return *this = *this / r; }
    bool operator<(const Frac& r) const { return a * r.b < b * r.a; }
    bool operator>(const Frac& r) const { return r < *this; }
    bool operator<=(const Frac& r) const { return !(r < *this); }
    bool operator>=(const Frac& r) const { return !(*this < r); }
    bool operator==(const Frac& r) const {
        return !(*this < r) && !(r < *this);
    }
    bool operator!=(const Frac& r) const { return !(*this == r); }

    static Frac rec(Frac x, Frac y, Frac l, Frac r) {
        auto flip = [&](Frac& f) { f = Frac(1) - f; };
        auto cross = [&](const Frac& f, const Frac& g) {
            return f.a * g.b - f.b * g.a;
        };
        Frac m = {l.a + r.a, l.b + r.b};
        if (x < m && m < y) return m;
        bool s = !(x < m);
        if (s) {
            flip(l);
            flip(r);
            flip(m);
            flip(x);
            flip(y);
            swap(l, r);
            swap(x, y);
        }
        I k = cross(r, y) / cross(y, l) + 1;
        Frac p = {k * l.a + r.a, k * l.b + r.b};
        if (x < p) {
            if (s) flip(p);
            return p;
        }
        Frac q = rec(x, y, p, {(k - 1) * l.a + r.a, (k - 1) * l.b + r.b});
        if (s) flip(q);
        return q;
    }
    static Frac in_bet(Frac x, Frac y) {
        if (y < x) swap(x, y);
        Frac ret;
        I num = x.a >= 0 ? x.a / x.b : -((x.b - 1 - x.a) / x.b);
        x.a -= x.b * num;
        y.a -= y.b * num;
        if (Frac{1, 1} < y)
            ret = Frac{1, 1};
        else
            ret = rec(x, y, Frac{0, 1}, Frac{1, 1});
        ret.a += ret.b * num;
        return ret;
    }
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
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/primitive.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

