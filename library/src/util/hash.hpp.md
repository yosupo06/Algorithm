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


# :heavy_check_mark: src/util/hash.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#6433a1a19c7364347102f741d8b9cffd">src/util</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/util/hash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-24 19:01:57+09:00




## Depends on

* :heavy_check_mark: <a href="../base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="random.hpp.html">src/util/random.hpp</a>


## Required by

* :heavy_check_mark: <a href="../datastructure/hashmap.hpp.html">src/datastructure/hashmap.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/hashmap.test.cpp.html">src/hashmap.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hashmap_remove.test.cpp.html">src/hashmap_remove.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"
#include "util/random.hpp"

// Reference: Lemire, Daniel., and Owen, Kaser. "Strongly Universal String Hashing Is Fast."
template <uint N = 4> struct Hasher {
    static ull offset;
    static array<ull, N> seed;

    static uint hash(uint x) { return (offset + x * seed[0]) >> 32; }
    static uint hash(ull x) {
        return (offset + uint(x) * seed[0] + (x >> 32) * seed[1]) >> 32;
    }
    static uint hash(int x) { return hash(uint(x)); }
    static uint hash(ll x) { return hash(ull(x)); }
};

template <uint N>
ull Hasher<N>::offset = global_runtime_gen().uniform(0ULL, ull(-1));

template <uint N>
array<ull, N> Hasher<N>::seed = []() {
    array<ull, N> seed;
    for (uint i = 0; i < N; i++) {
        seed[i] = global_runtime_gen().uniform(0ULL, ull(-1));
    }
    return seed;
}();

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 172, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 162, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

