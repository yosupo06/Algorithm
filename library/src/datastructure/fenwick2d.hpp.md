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


# :heavy_check_mark: src/datastructure/fenwick2d.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/fenwick2d.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:50:28+09:00




## Depends on

* :heavy_check_mark: <a href="../base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="fenwick.hpp.html">src/datastructure/fenwick.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/fenwick_2d_rectangle_sum.test.cpp.html">src/fenwick_2d_rectangle_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"
#include "datastructure/fenwick.hpp"

template <class D, class I> struct Fenwick2D {
    using P = pair<I, I>;
    V<P> points;
    VV<I> ys;
    V<Fenwick<D>> fws;
    int lg, sz;
    Fenwick2D(V<P> _points) : points(_points) {
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        int n = int(points.size());
        lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        ys = VV<I>(2 * sz);
        for (int i = 0; i < n; i++) ys[sz + i].push_back(points[i].second);
        for (int i = sz - 1; i >= 1; i--) {
            ys[i] = V<I>(ys[2 * i].size() + ys[2 * i + 1].size());
            merge(ys[2 * i].begin(), ys[2 * i].end(), ys[2 * i + 1].begin(),
                  ys[2 * i + 1].end(), ys[i].begin());
        }
        fws = V<Fenwick<D>>(2 * sz);
        for (int i = 1; i < 2 * sz; i++) {
            fws[i] = Fenwick<D>(int(ys[i].size()));
        }
    }

    void add(P p, D x) {
        int k =
            int(lower_bound(points.begin(), points.end(), p) - points.begin());
        k += sz;
        while (k) {
            int yid = int(lower_bound(ys[k].begin(), ys[k].end(), p.second) -
                          ys[k].begin());
            fws[k].add(yid, x);
            k >>= 1;
        }
    }

    D sum(int a, int b, I lw, I up, int l, int r, int k) {
        if (b <= l || r <= a) return D(0);
        if (a <= l && r <= b) {
            int lid = int(lower_bound(ys[k].begin(), ys[k].end(), lw) -
                          ys[k].begin());
            int uid = int(lower_bound(ys[k].begin(), ys[k].end(), up) -
                          ys[k].begin());
            return fws[k].sum(lid, uid);
        }
        int mid = (l + r) / 2;
        return sum(a, b, lw, up, l, mid, 2 * k) +
               sum(a, b, lw, up, mid, r, 2 * k + 1);
    }

    D sum(P lw, P up) {
        int a = int(lower_bound(points.begin(), points.end(), lw.first,
                                [&](P p, I x) { return p.first < x; }) -
                    points.begin());
        int b = int(lower_bound(points.begin(), points.end(), up.first,
                                [&](P p, I x) { return p.first < x; }) -
                    points.begin());
        return sum(a, b, lw.second, up.second, 0, sz, 1);
    }
};

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

