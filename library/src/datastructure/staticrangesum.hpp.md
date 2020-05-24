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


# :heavy_check_mark: src/datastructure/staticrangesum.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/staticrangesum.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:50:28+09:00




## Depends on

* :question: <a href="../base.hpp.html">src/base.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/staticrangesum_rectangle_sum.test.cpp.html">src/staticrangesum_rectangle_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"

template <class D, class I> struct StaticRangeSum {
    struct P {
        I x, y;
        D val;
    };

    StaticRangeSum(V<P> ps) {
        if (!ps.size()) return;
        sort(ps.begin(), ps.end(), [&](P l, P r) { return l.x < r.x; });
        for (auto p : ps) {
            xs.push_back(p.x);
            ys.push_back(p.y);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int n = int(xs.size());
        int m = int(ys.size());

        lg = 1;
        while ((1 << lg) < m) lg++;

        mid = V<int>(lg);
        bits = VV<int>(lg, V<int>(n + 1));
        sums = VV<D>(lg + 1, V<D>(n + 1));

        struct Q {
            int y;
            D val;
        };
        V<Q> v;
        for (auto p : ps) {
            int y = int(lower_bound(ys.begin(), ys.end(), p.y) - ys.begin());
            v.push_back({y, p.val});
        }
        for (int i = 0; i < n; i++) {
            Q q = v[i];
            sums[lg][i + 1] = sums[lg][i] + q.val;
        }
        for (int lv = lg - 1; lv >= 0; lv--) {
            array<V<Q>, 2> nx;
            for (int i = 0; i < n; i++) {
                Q q = v[i];
                bool f = (q.y >> lv) & 1;
                bits[lv][i + 1] = bits[lv][i] + (f ? 0 : 1);
                nx[f].push_back(q);
            }
            mid[lv] = int(nx[0].size());
            v.clear();
            v.insert(v.end(), nx[0].begin(), nx[0].end());
            v.insert(v.end(), nx[1].begin(), nx[1].end());
            for (int i = 0; i < n; i++) {
                Q q = v[i];
                sums[lv][i + 1] = sums[lv][i] + q.val;
            }
        }
    }
    // (low_x <= x < up_x), (low_y <= y < up_y)なる点の重みの総和
    D sum(I low_x, I low_y, I up_x, I up_y) {
        int _lx = int(lower_bound(xs.begin(), xs.end(), low_x) - xs.begin());
        int _ux = int(lower_bound(xs.begin(), xs.end(), up_x) - xs.begin());
        int _ly = int(lower_bound(ys.begin(), ys.end(), low_y) - ys.begin());
        int _uy = int(lower_bound(ys.begin(), ys.end(), up_y) - ys.begin());
        if (_lx >= _ux || _ly >= _uy) return D(0);
        return sum(_lx, _ux, _uy) - sum(_lx, _ux, _ly);
    }

  private:
    int lg;
    V<I> xs, ys;

    V<int> mid;
    VV<int> bits;
    VV<D> sums;
    D sum(int l, int r, int u) {
        if (u == (1 << lg)) return sums[lg][r] - sums[lg][l];
        D ans = 0;
        for (int lv = lg - 1; lv >= 0; lv--) {
            bool f = (u >> lv) & 1;
            int l0 = bits[lv][l], r0 = bits[lv][r];
            if (f) {
                ans += sums[lv][r0] - sums[lv][l0];
                l = l - l0 + mid[lv];
                r = r - r0 + mid[lv];
            } else {
                l = l0;
                r = r0;
            }
        }
        return ans;
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

