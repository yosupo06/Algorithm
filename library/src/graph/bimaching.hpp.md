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


# :heavy_check_mark: src/graph/bimaching.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/bimaching.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Depends on

* :heavy_check_mark: <a href="../datastructure/simplequeue.hpp.html">src/datastructure/simplequeue.hpp</a>
* :heavy_check_mark: <a href="csr.hpp.html">src/graph/csr.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/bimaching.test.cpp.html">src/bimaching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "datastructure/simplequeue.hpp"
#include "graph/csr.hpp"

struct BipartiteMaching {
  public:
    int n, m;
    V<int> lmt, rmt;

    BipartiteMaching(int _n, int _m, V<pair<int, int>> edges)
        : n(_n), m(_m), lmt(n, -1), rmt(m, -1), dist(m) {
        for (auto e : edges) {
            int l, r;
            tie(l, r) = e;
            if (lmt[l] == -1 && rmt[r] == -1) {
                lmt[l] = r;
                rmt[r] = l;
            }
        }
        lg = CSR(n, edges);
        for (auto& e : edges) swap(e.first, e.second);
        rg = CSR(m, edges);

        while (true) {
            bfs();
            // if (trg_dist >= 20) break;
            if (trg_dist == TEN(9)) break;
            bool f = dfs();
            assert(f);
        }
    }

  private:
    CSR lg, rg;

    int trg_dist;
    V<int> dist;
    SimpleQueue<int> que;
    void bfs() {
        trg_dist = TEN(9);
        que.clear();
        for (int i = 0; i < m; i++) {
            if (rmt[i] == -1) {
                dist[i] = 0;
                que.push(i);
            } else {
                dist[i] = TEN(9);
            }
        }
        while (!que.empty()) {
            int q = que.front();
            que.pop();
            int distq = dist[q];
            for (int pid = rg.start[q]; pid < rg.start[q + 1]; pid++) {
                int p = rg.to[pid];
                int next = lmt[p];
                if (next == -1) {
                    trg_dist = distq + 1;
                    return;
                }
                if (dist[next] == TEN(9)) {
                    dist[next] = distq + 1;
                    que.push(next);
                }
            }
        }
    }
    bool dfs() {
        bool update = false;
        for (int i = 0; i < n; i++) {
            if (lmt[i] == -1 && dfs(i, trg_dist)) {
                update = true;
            }
        }
        return update;
    }
    bool dfs(int p, int distp) {
        int st = lg.start[p], ls = lg.start[p + 1];
        for (int qid = st; qid < ls; qid++) {
            int q = lg.to[qid];
            if (distp - 1 == dist[q]) {
                int next = rmt[q];
                if (next != -1) {
                    dist[q] = TEN(9);
                    if (!dfs(next, distp - 1)) continue;
                }
                lmt[p] = q;
                rmt[q] = p;
                return true;
            }
        }
        return false;
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: datastructure/simplequeue.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

