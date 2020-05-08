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


# :warning: src/string/rollinghash.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ec86b6e05e7d09e98d071ea841edf05f">src/string</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/string/rollinghash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
using Mint0 = ModInt<TEN(9) + 7>;
using Mint1 = ModInt<TEN(9) + 9>;

V<Mint0> powB0{1}, powiB0{1};
V<Mint1> powB1{1}, powiB1{1};
Mint0 B0 = rand_int(1, TEN(9)), iB0 = B0.inv();
Mint1 B1 = rand_int(1, TEN(9)), iB1 = B1.inv();
void first() {
    for (int i = 0; i < 2 * TEN(6) + 10000; i++) {
        powB0.push_back(powB0.back() * B0);
        powiB0.push_back(powiB0.back() * iB0);
        powB1.push_back(powB1.back() * B1);
        powiB1.push_back(powiB1.back() * iB1);
    }
}

struct H {
    int le = 0;
    Mint0 h0;
    Mint1 h1;
    H() : le(0), h0(0), h1(0) {}
    H(int _le, Mint0 _h0, Mint1 _h1) : le(_le), h0(_h0), h1(_h1) {}
    H(int c) : le(1), h0(c), h1(c) {}
    // H(l) + H(r) = H(lr)
    H operator+(const H& r) const {
        return H{le + r.le, h0 + r.h0 * powB0[le], h1 + r.h1 * powB1[le]};
    }
    H& operator+=(const H& r) { return *this = *this + r; }

    bool operator==(const H& r) const {
        return le == r.le && h0 == r.h0 && h1 == r.h1;
    }
    bool operator!=(const H& r) const {
        return !(*this == r);
    }
    // H(lr).strip_left(H(l)) = H(r)
    H strip_left(const H& l) const {
        return H{le - l.le, (h0 - l.h0) * powiB0[l.le], (h1 - l.h1) * powiB1[l.le]};
    }
    // H(lr).strip_right(H(r)) = H(l)
    H strip_right(const H& r) const {
        return H{le - r.le, h0 - r.h0 * powB0[le - r.le], h1 - r.h1 * powB1[le - r.le]};
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/string/rollinghash.hpp"
using Mint0 = ModInt<TEN(9) + 7>;
using Mint1 = ModInt<TEN(9) + 9>;

V<Mint0> powB0{1}, powiB0{1};
V<Mint1> powB1{1}, powiB1{1};
Mint0 B0 = rand_int(1, TEN(9)), iB0 = B0.inv();
Mint1 B1 = rand_int(1, TEN(9)), iB1 = B1.inv();
void first() {
    for (int i = 0; i < 2 * TEN(6) + 10000; i++) {
        powB0.push_back(powB0.back() * B0);
        powiB0.push_back(powiB0.back() * iB0);
        powB1.push_back(powB1.back() * B1);
        powiB1.push_back(powiB1.back() * iB1);
    }
}

struct H {
    int le = 0;
    Mint0 h0;
    Mint1 h1;
    H() : le(0), h0(0), h1(0) {}
    H(int _le, Mint0 _h0, Mint1 _h1) : le(_le), h0(_h0), h1(_h1) {}
    H(int c) : le(1), h0(c), h1(c) {}
    // H(l) + H(r) = H(lr)
    H operator+(const H& r) const {
        return H{le + r.le, h0 + r.h0 * powB0[le], h1 + r.h1 * powB1[le]};
    }
    H& operator+=(const H& r) { return *this = *this + r; }

    bool operator==(const H& r) const {
        return le == r.le && h0 == r.h0 && h1 == r.h1;
    }
    bool operator!=(const H& r) const {
        return !(*this == r);
    }
    // H(lr).strip_left(H(l)) = H(r)
    H strip_left(const H& l) const {
        return H{le - l.le, (h0 - l.h0) * powiB0[l.le], (h1 - l.h1) * powiB1[l.le]};
    }
    // H(lr).strip_right(H(r)) = H(l)
    H strip_right(const H& r) const {
        return H{le - r.le, h0 - r.h0 * powB0[le - r.le], h1 - r.h1 * powB1[le - r.le]};
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

