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


# :heavy_check_mark: src/string/run.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ec86b6e05e7d09e98d071ea841edf05f">src/string</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/string/run.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 19:01:40+09:00




## Depends on

* :question: <a href="../base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="zalgo.hpp.html">src/string/zalgo.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/run.test.cpp.html">src/run.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"
#include "string/zalgo.hpp"

template<class Str>
struct RunExec {
    VV<pair<int, int>> runs;

    int n;
    Str a;

    V<int> rev(V<int> l) {
        reverse(l.begin(), l.end());
        return l;
    }

    V<int> sub_a(int l, int r) { return {a.begin() + l, a.begin() + r}; }
    V<int> concat(V<int> l, const V<int>& r) {
        l.insert(l.end(), r.begin(), r.end());
        return l;
    }

    void run(int l, int r, int f) {
        if (l + 1 == r) return;
        int md = (l + r + f) / 2;
        run(l, md, f);
        run(md, r, f);
        auto z1 = z_algo(rev(sub_a(l, md)));
        auto z2 = z_algo(concat(sub_a(md, r), sub_a(l, r)));
        for (int i = md - 1; i >= l; i--) {
            int l1 = min(i - l, z1[md - i]);
            int l2 = min(r - md, z2[(r - l) - (md - i)]);
            int le = i - l1, ri = md + l2, peri = md - i;
            if (ri - le >= 2 * peri) runs[md - i].push_back({i - l1, md + l2});
        }
    }
    
    RunExec(Str _a) : a(_a) {
        n = int(a.size());
        runs.resize(n / 2 + 1);
        reverse(a.begin(), a.end());
        run(0, n, 0);
        for (auto& run : runs) {
            for (auto& p : run) {
                tie(p.first, p.second) = make_pair(n - p.second, n - p.first);
            }
        }
        reverse(a.begin(), a.end());
        run(0, n, 1);

        set<pair<int, int>> vis;
        for (int ph = 1; ph <= n / 2; ph++) {
            auto& run = runs[ph];
            sort(run.begin(), run.end(),
                 [&](pair<int, int> lhs, pair<int, int> rhs) {
                     if (lhs.first != rhs.first) return lhs.first < rhs.first;
                     return lhs.second > rhs.second;
                 });
            V<pair<int, int>> res;
            for (auto p : run) {
                if (!res.empty() && p.second <= res.back().second) continue;
                res.push_back(p);
            }
            run = res;
            res.clear();
            for (auto p : run) {
                if (vis.count(p)) continue;
                vis.insert(p);
                res.push_back(p);
            }
            run = res;
        }
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

