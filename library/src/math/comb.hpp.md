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


# :heavy_check_mark: src/math/comb.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fb2ef479237c7a939531a404fd0e5cb7">src/math</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/math/comb.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/src/comb.test.cpp.html">src/comb.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

template<class Mint>
struct Comb {
    int max_n;
    V<Mint> fact, ifact;
    Comb() {}
    Comb(int n) : max_n(n) {
        fact = ifact = V<Mint>(n + 1);
        fact[0] = Mint(1);
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    }

    Mint C(int n, int k) {
        if (n < k || n < 0) return Mint(0);
        assert(0 <= k && k <= n && n <= max_n);
        return fact[n] * ifact[k] * ifact[n - k];
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/math/comb.hpp"

template<class Mint>
struct Comb {
    int max_n;
    V<Mint> fact, ifact;
    Comb() {}
    Comb(int n) : max_n(n) {
        fact = ifact = V<Mint>(n + 1);
        fact[0] = Mint(1);
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    }

    Mint C(int n, int k) {
        if (n < k || n < 0) return Mint(0);
        assert(0 <= k && k <= n && n <= max_n);
        return fact[n] * ifact[k] * ifact[n - k];
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

