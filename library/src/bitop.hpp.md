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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: src/bitop.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/bitop.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Required by

* :warning: <a href="datastructure/bitvector.hpp.html">src/datastructure/bitvector.hpp</a>
* :warning: <a href="datastructure/fastset.hpp.html">src/datastructure/fastset.hpp</a>
* :heavy_check_mark: <a href="math/dynamicmodint.hpp.html">src/math/dynamicmodint.hpp</a>
* :warning: <a href="math/matrix.hpp.html">src/math/matrix.hpp</a>
* :heavy_check_mark: <a href="math/nft.hpp.html">src/math/nft.hpp</a>
* :warning: <a href="nft_convolution.cpp.html">src/nft_convolution.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/src/comb.test.cpp.html">src/comb.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/inv_of_formal_power_series.test.cpp.html">src/inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/modint.test.cpp.html">src/modint.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/bitop.hpp"
// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

