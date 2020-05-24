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


# :x: src/string/rollinghash.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ec86b6e05e7d09e98d071ea841edf05f">src/string</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/string/rollinghash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-24 18:50:28+09:00




## Depends on

* :question: <a href="../base.hpp.html">src/base.hpp</a>
* :question: <a href="../math/comb.hpp.html">src/math/comb.hpp</a>
* :x: <a href="../math/modint61.hpp.html">src/math/modint61.hpp</a>
* :question: <a href="../util/random.hpp.html">src/util/random.hpp</a>


## Verified with

* :x: <a href="../../../verify/src/zalgo_rollinghash.test.cpp.html">src/zalgo_rollinghash.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "math/comb.hpp"
#include "math/modint61.hpp"
#include "util/random.hpp"

struct H {
  private:
    static ModInt61 B;
    static ModInt61 iB;
    static V<ModInt61> powB, powiB;

  public:
    static void init(int n) {
        powB = powTable(n, B);
        powiB = powTable(n, iB);
    }
    int le = 0;
    ModInt61 h;
    H() : le(0), h(0) {}
    H(int _le, ModInt61 _h) : le(_le), h(_h) {}
    H(int c) : le(1), h(c) {}
    // H(l) + H(r) = H(lr)
    H operator+(const H& r) const { return H{le + r.le, h + r.h * powB[le]}; }
    H& operator+=(const H& r) { return *this = *this + r; }

    bool operator==(const H& r) const { return le == r.le && h == r.h; }
    bool operator!=(const H& r) const { return !(*this == r); }
    // H(lr).strip_left(H(l)) = H(r)
    H strip_left(const H& l) const {
        return H{le - l.le, (h - l.h) * powiB[l.le]};
    }
    // H(lr).strip_right(H(r)) = H(l)
    H strip_right(const H& r) const {
        return H{le - r.le, h - r.h * powB[le - r.le]};
    }
};
ModInt61 H::B =
    ModInt61(global_random_gen.uniform(0ULL, ModInt61::get_mod() - 1));
ModInt61 H::iB = H::B.inv();
V<ModInt61> H::powB, H::powiB;

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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: math/comb.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

