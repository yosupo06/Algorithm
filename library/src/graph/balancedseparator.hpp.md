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


# :warning: src/graph/balancedseparator.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/balancedseparator.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-27 03:21:52+09:00




## Depends on

* :heavy_check_mark: <a href="../base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../datastructure/hashmap.hpp.html">src/datastructure/hashmap.hpp</a>
* :heavy_check_mark: <a href="../datastructure/hashset.hpp.html">src/datastructure/hashset.hpp</a>
* :heavy_check_mark: <a href="../datastructure/simplequeue.hpp.html">src/datastructure/simplequeue.hpp</a>
* :heavy_check_mark: <a href="primitive.hpp.html">src/graph/primitive.hpp</a>
* :heavy_check_mark: <a href="treedecomp.hpp.html">src/graph/treedecomp.hpp</a>
* :warning: <a href="../tree/centroid.hpp.html">src/tree/centroid.hpp</a>
* :heavy_check_mark: <a href="../util/hash.hpp.html">src/util/hash.hpp</a>
* :heavy_check_mark: <a href="../util/random.hpp.html">src/util/random.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"
#include "graph/primitive.hpp"
#include "graph/treedecomp.hpp"
#include "tree/centroid.hpp"

struct BalancedSeparator {
    int num_layer;
    VV<SimpleEdge> tr;
    VV<int> bags;
    V<int> lv;
    V<int> pos;
    V<int> par;

    // lca bag of vertex u, v
    int lca(int u, int v) const {
        u = pos[u]; v = pos[v];
        while (u != v) {
//            dbg(u, v, lv[u], lv[v], par[u], par[v]);
            if (lv[u] < lv[v]) swap(u, v);
            u = par[u];
        }
        return u;
    }
};

BalancedSeparator balanced_separator(const TreeDecomp& td) {
    int n = 0;
    for (auto bag: td.bags) {
        for (auto v: bag) {
            n = max(n, v + 1);
        }
    }
    BalancedSeparator bs;
    bs.pos = V<int>(n, -1);

    auto cent = get_centroid(td.tr);

    auto cdfs = [&](auto self, int p, int bk_id, int now_lv) -> int {
        int id = int(bs.tr.size());
        bs.tr.push_back({});
        bs.bags.push_back({});
        bs.par.push_back(bk_id);
        bs.lv.push_back(now_lv);
        for (auto v : td.bags[p]) {
            if (bs.pos[v] != -1) continue;
            bs.pos[v] = id;
            bs.bags[id].push_back(v);
        }

        for (int d : cent.tr[p]) {
            int cid = self(self, d, id, now_lv + 1);
            bs.tr[id].push_back({cid});
        }
        return id;
    };    
    cdfs(cdfs, cent.r, -1, 0);
    bs.num_layer = 0;
    for (int x: bs.lv) bs.num_layer = max(bs.num_layer, x + 1);

    return bs;
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
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 187, in _resolve
    raise BundleErrorAt(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

