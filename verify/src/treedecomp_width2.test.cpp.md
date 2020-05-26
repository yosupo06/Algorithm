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


# :heavy_check_mark: src/treedecomp_width2.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/treedecomp_width2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-26 03:02:59+09:00


* see: <a href="https://judge.yosupo.jp/problem/tree_decomposition_width_2">https://judge.yosupo.jp/problem/tree_decomposition_width_2</a>


## Depends on

* :heavy_check_mark: <a href="../../library/src/base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../../library/src/datastructure/hashmap.hpp.html">src/datastructure/hashmap.hpp</a>
* :heavy_check_mark: <a href="../../library/src/datastructure/hashset.hpp.html">src/datastructure/hashset.hpp</a>
* :heavy_check_mark: <a href="../../library/src/datastructure/simplequeue.hpp.html">src/datastructure/simplequeue.hpp</a>
* :heavy_check_mark: <a href="../../library/src/graph/primitive.hpp.html">src/graph/primitive.hpp</a>
* :heavy_check_mark: <a href="../../library/src/graph/treedecomp.hpp.html">src/graph/treedecomp.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/fast_io.hpp.html">src/util/fast_io.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/hash.hpp.html">src/util/hash.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/random.hpp.html">src/util/random.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/tree_decomposition_width_2"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "graph/treedecomp.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    string s;
    sc.read(s, s);
    int n, m;
    sc.read(n, m);
    VV<SimpleEdge> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        sc.read(a, b); a--; b--;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    auto td = decomp_width2(g);
    int K = int(td.bags.size());
    if (K == 0) {
        pr.writeln(-1);
        return 0;
    }
    pr.writeln("s", "td", K, 2, n);

    for (int i = 0; i < K; i++) {
        pr.write("b", i + 1);
        for (int j: td.bags[i]) {
            pr.write(' ');
            pr.write(j + 1);
        }
        pr.writeln();
    }
    for (int i = 0; i < K; i++) {
        for (auto e: td.tr[i]) {
            int j = e.to;
            if (i < j) {
                pr.writeln(i + 1, j + 1);
            }
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
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 307, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 307, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 187, in _resolve
    raise BundleErrorAt(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

