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


# :heavy_check_mark: src/rollinghash_zalgo.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/rollinghash_zalgo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-24 20:34:49+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

* :heavy_check_mark: <a href="../../library/src/base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../../library/src/math/comb.hpp.html">src/math/comb.hpp</a>
* :heavy_check_mark: <a href="../../library/src/math/modint61.hpp.html">src/math/modint61.hpp</a>
* :heavy_check_mark: <a href="../../library/src/string/rollinghash.hpp.html">src/string/rollinghash.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/fast_io.hpp.html">src/util/fast_io.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/random.hpp.html">src/util/random.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "string/rollinghash.hpp"

int main() {
    H::init(TEN(6));
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    int n = int(s.size());
    V<H> hs = {H()};
    for (char c: s) {
        H nh = hs.back() + H(c);
        hs.push_back(nh);
    }
    dbg(H::powB[3]);
    for (int i = 0; i < n; i++) {
        int lw = 0, up = n - i + 1;
        while (up - lw > 1) {
            int md = (lw + up) / 2;
            if (hs[md] == hs[i + md].strip_left(hs[i])) {
                lw = md;
            } else {
                up = md;
            }
        }
        pr.write(lw);
        pr.write(' ');
    }
    pr.writeln();
}

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
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 162, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: math/comb.hpp: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

