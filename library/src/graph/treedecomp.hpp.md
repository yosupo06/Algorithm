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


# :heavy_check_mark: src/graph/treedecomp.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/treedecomp.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-26 03:02:59+09:00




## Depends on

* :heavy_check_mark: <a href="../base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../datastructure/hashmap.hpp.html">src/datastructure/hashmap.hpp</a>
* :heavy_check_mark: <a href="../datastructure/hashset.hpp.html">src/datastructure/hashset.hpp</a>
* :heavy_check_mark: <a href="../datastructure/simplequeue.hpp.html">src/datastructure/simplequeue.hpp</a>
* :heavy_check_mark: <a href="primitive.hpp.html">src/graph/primitive.hpp</a>
* :heavy_check_mark: <a href="../util/hash.hpp.html">src/util/hash.hpp</a>
* :heavy_check_mark: <a href="../util/random.hpp.html">src/util/random.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/treedecomp_width2.test.cpp.html">src/treedecomp_width2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"
#include "graph/primitive.hpp"
#include "datastructure/hashset.hpp"
#include "datastructure/hashmap.hpp"
#include "datastructure/simplequeue.hpp"

struct TreeDecomp {
    VV<SimpleEdge> tr;
    VV<int> bags;
};


template <class E>
TreeDecomp decomp_width2(VV<E> _g) {
    int n = int(_g.size());
    assert(n);

    V<HashSet<int>> g(n);
    for (int i = 0; i < n; i++) {
        for (auto e : _g[i]) {
            int j = e.to;
            g[i].insert(j);
        }
    }

    V<int> deg(n);
    V<bool> alive(n, true);
    SimpleQueue<int> que;
    for (int i = 0; i < n; i++) {
        deg[i] = int(g[i].size());
        que.push(i);
    }

    struct Event {
        int deg;
        int a, b, c;
    };
    V<Event> events;

    V<int> nears;
    auto remove = [&](int p) {
        assert(alive[p]);
        alive[p] = false;
        for (int i: nears) {
            assert(alive[i]);
            g[i].erase(p);
            deg[i]--;
            que.push(i);
        }
    };
    while (que.size()) {
        int p = que.front();
        que.pop();
        int d = deg[p];
        if (!alive[p] || d >= 3) continue;
        nears = g[p].to_vec();
        assert(int(nears.size()) == d);
        if (d == 0) {
            events.push_back({0, p, -1, -1});
        }
        if (d == 1) {
            events.push_back({1, p, nears[0], -1});
        }
        if (d == 2) {
            int u = nears[0];
            int v = nears[1];
            events.push_back({2, p, u, v});
            g[u].insert(v);
            g[v].insert(u);
            deg[u] = int(g[u].size());
            deg[v] = int(g[v].size());
        }
        remove(p);
    }

    for (int i = 0; i < n; i++) {
        if (alive[i]) {
            return TreeDecomp{};
        }
    }

    TreeDecomp td;
    V<int> par;
    V<int> node_pos(n, -1);
    HashMap<pair<int, int>, int> edge_pos;
    reverse(events.begin(), events.end());
    for (auto event : events) {
        int id = int(td.bags.size());
        if (event.deg == 0) {
            td.bags.push_back({event.a});
            par.push_back(id - 1);
        }
        if (event.deg == 1) {
            td.bags.push_back({event.a, event.b});
            par.push_back(node_pos[event.b]);
        }
        if (event.deg == 2) {
            td.bags.push_back({event.a, event.b, event.c});
            par.push_back(edge_pos.get(minmax(event.b, event.c)));
        }
        for (int x : td.bags.back()) {
            node_pos[x] = id;
        }
        for (int x : td.bags.back()) {
            for (int y : td.bags.back()) {
                if (x < y) edge_pos.set({x, y}, id);
            }
        }
    }
    int K = int(td.bags.size());
    td.tr = VV<SimpleEdge>(K);
    for (int i = 1; i < K; i++) {
        td.tr[par[i]].push_back({i});
        td.tr[i].push_back({par[i]});
    }
    return td;
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

