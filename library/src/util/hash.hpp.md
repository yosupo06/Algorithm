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


# :question: src/util/hash.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#6433a1a19c7364347102f741d8b9cffd">src/util</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/util/hash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-26 02:54:27+09:00




## Depends on

* :question: <a href="../base.hpp.html">src/base.hpp</a>
* :question: <a href="random.hpp.html">src/util/random.hpp</a>


## Required by

* :question: <a href="../datastructure/hashmap.hpp.html">src/datastructure/hashmap.hpp</a>
* :question: <a href="../datastructure/hashset.hpp.html">src/datastructure/hashset.hpp</a>
* :x: <a href="../graph/treedecomp.hpp.html">src/graph/treedecomp.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/hashmap.test.cpp.html">src/hashmap.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hashmap_remove.test.cpp.html">src/hashmap_remove.test.cpp</a>
* :x: <a href="../../../verify/src/hashset.test.cpp.html">src/hashset.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hashset_hashmap.test.cpp.html">src/hashset_hashmap.test.cpp</a>
* :x: <a href="../../../verify/src/treedecomp_width2.test.cpp.html">src/treedecomp_width2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"
#include "util/random.hpp"

// Reference: Lemire, Daniel., and Owen, Kaser. "Strongly Universal String Hashing Is Fast."
template <uint N = 4> struct Hasher {
  private:
    static ull offset;
    static array<ull, N> seed;

    template <uint I = 0>
    struct Encoder {
        ull now = offset;
        Encoder<I + 1> update(uint x) {
            return Encoder<I + 1>{now + x * seed[I]};
        }
        Encoder<I + 1> update(int x) {
            return update(uint(x));
        }
        Encoder<I + 2> update(ull x) {
            return Encoder<I + 2>{now + uint(x) * seed[I] + (x >> 32) * seed[I + 1]};
        }
        Encoder<I + 2> update(ll x) {
            return update(ll(x));
        }
        uint digest() const {
            static_assert(I <= N);
            return uint(now >> 32);
        }
    };

  public:
    static uint hash(uint x) { return Encoder<>{}.update(x).digest(); }
    static uint hash(ull x) { return Encoder<>{}.update(x).digest(); }
    static uint hash(int x) { return hash(uint(x)); }
    static uint hash(ll x) { return hash(ull(x)); }
    template <class T, class U> static uint hash(const pair<T, U>& p) {
        return Encoder<>{}.update(p.first).update(p.second).digest();
    }
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

