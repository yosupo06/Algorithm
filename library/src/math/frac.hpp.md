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
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
#line 1 "src/math/frac.hpp"
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

<a href="../../../index.html">Back to top page</a>

