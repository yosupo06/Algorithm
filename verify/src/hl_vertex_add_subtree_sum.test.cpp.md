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


# :heavy_check_mark: src/hl_vertex_add_subtree_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/hl_vertex_add_subtree_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/src/base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../../library/src/datastructure/segtree.hpp.html">src/datastructure/segtree.hpp</a>
* :heavy_check_mark: <a href="../../library/src/tree/hl.hpp.html">src/tree/hl.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/fast_io.hpp.html">src/util/fast_io.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "base.hpp"
#include "datastructure/segtree.hpp"
#include "tree/hl.hpp"
#include "util/fast_io.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int n, q;
    sc.read(n, q);
    V<ll> a(n);
    for (int i = 0; i < n; i++) {
        sc.read(a[i]);
    }
    struct E {
        int to;
    };
    VV<E> g(n);
    for (int i = 1; i < n; i++) {
        int p;
        sc.read(p);
        g[i].push_back({p});
        g[p].push_back({i});
    }
    auto hl = get_hl(g, 0);
    auto seg =
        get_simple_seg(V<ll>(n, 0), 0LL, [&](ll x, ll y) { return x + y; });
    for (int i = 0; i < n; i++) {
        seg.set(hl.ord(i).i, a[i]);
    }
    for (int i = 0; i < q; i++) {
        int t;
        sc.read(t);
        if (t == 0) {
            int p;
            ll x;
            sc.read(p, x);
            seg.set(hl.ord(p).i, seg.single(hl.ord(p).i) + x);
        } else {
            int u;
            sc.read(u);
            ll sm = seg.sum(hl.ord(u).i, hl.subtree_out(u).i);
            pr.writeln(sm);
        }
    }
    return 0;
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

