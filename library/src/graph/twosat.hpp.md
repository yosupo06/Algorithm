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


# :warning: src/graph/twosat.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/twosat.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-22 19:22:07+09:00




## Depends on

* :warning: <a href="scc.hpp.html">src/graph/scc.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "graph/scc.hpp"

struct TwoSat {
    V<bool> res;

    struct Edge { int to; };
    VV<Edge> g;

    //(a == a_exp) || (b == b_exp)
    void add_cond(int a, bool a_exp, int b, bool b_exp) {
        g[2 * a + (a_exp ? 0 : 1)].push_back(Edge{2 * b + (b_exp ? 1 : 0)});
        g[2 * b + (b_exp ? 0 : 1)].push_back(Edge{2 * a + (a_exp ? 1 : 0)});
    }
    bool exec() {
        int n = int(res.size());
        auto s = get_scc(g);
        for (int i = 0; i < n; i++) {
            if (s.id[2 * i] == s.id[2 * i + 1]) return false;
            res[i] = s.id[2 * i] < s.id[2 * i + 1];
        }
        return true;
    }
    TwoSat() {}
    TwoSat(int n) {
        g = VV<Edge>(2 * n);
        res = V<bool>(n);
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
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/scc.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

