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


# :warning: src/util/hash.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#6433a1a19c7364347102f741d8b9cffd">src/util</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/util/hash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

uint64_t mix(uint64_t h) {
    h ^= h >> 23;
    h *= 0x2127599bf4325c37ULL;
    h ^= h >> 47;
    return h;
}

uint64_t hash_f(ull x, ull seed = 0) {
    const uint64_t m = 0x880355f21e6d1965ULL;
    return mix((seed ^ m ^ mix(x)) * m);
}

template <class T> struct fasthash {};

template <> struct fasthash<int> {
    size_t operator()(int x) const { return hash_f(x); }
};
template <> struct fasthash<uint> {
    size_t operator()(uint x) const { return hash_f(x); }
};
template <> struct fasthash<ll> {
    size_t operator()(ll x) const { return hash_f(x); }
};
template <> struct fasthash<ull> {
    size_t operator()(ull x) const { return hash_f(x); }
};
template<class S, class T> struct fasthash<pair<S, T>> {
    size_t operator()(pair<S, T> p) const {
        return hash_f(p.second, hash_f(p.first));
    }
};

template <class K, class D> using hashmap = gp_hash_table<K, D, fasthash<K>>;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/util/hash.hpp"
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

uint64_t mix(uint64_t h) {
    h ^= h >> 23;
    h *= 0x2127599bf4325c37ULL;
    h ^= h >> 47;
    return h;
}

uint64_t hash_f(ull x, ull seed = 0) {
    const uint64_t m = 0x880355f21e6d1965ULL;
    return mix((seed ^ m ^ mix(x)) * m);
}

template <class T> struct fasthash {};

template <> struct fasthash<int> {
    size_t operator()(int x) const { return hash_f(x); }
};
template <> struct fasthash<uint> {
    size_t operator()(uint x) const { return hash_f(x); }
};
template <> struct fasthash<ll> {
    size_t operator()(ll x) const { return hash_f(x); }
};
template <> struct fasthash<ull> {
    size_t operator()(ull x) const { return hash_f(x); }
};
template<class S, class T> struct fasthash<pair<S, T>> {
    size_t operator()(pair<S, T> p) const {
        return hash_f(p.second, hash_f(p.first));
    }
};

template <class K, class D> using hashmap = gp_hash_table<K, D, fasthash<K>>;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

