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


# :heavy_check_mark: src/max_clique.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/max_clique.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00


* see: <a href="https://judge.yosupo.jp/problem/maximum_independent_set">https://judge.yosupo.jp/problem/maximum_independent_set</a>


## Depends on

* :heavy_check_mark: <a href="../../library/src/base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../../library/src/graph/maxclique.hpp.html">src/graph/maxclique.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/fast_io.hpp.html">src/util/fast_io.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "graph/maxclique.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int n, m;
    sc.read(n, m);
    VV<int> graph(n, V<int>(n, 1));
    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        sc.read(a, b);
        graph[a][b] = graph[b][a] = 0;
    }

    struct E {
        int to;
    };
    VV<E> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) g[i].push_back({j});
        }
    }

    auto answer = MaxClique<40, E>(g).clique;

    int x = int(answer.size());
    pr.writeln(x);
    for (int i = 0; i < x; i++) {
        pr.write(answer[i]);
        if (i != x - 1) pr.write(" ");
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

