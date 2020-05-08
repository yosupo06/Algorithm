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


# :warning: src/graph/retrograde.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/retrograde.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * d[i] = 
 *   -1:このマスからスタートすると先手が負ける
 *    0:?
 *    1:このマスからスタートすると先手が勝つ
 */
template<class E>
void retrograde(const Graph<E> &g, const Graph<E> &rg, vector<int> &d) {
    int V = (int)g.size();
    vector<int> count(V);
    for (int i = 0; i < V; i++) {
        count[i] = (int)g[i].size();
    }
    for (int i = 0; i < V; i++) {
        if (d[i] == 1) {
            for (E e: rg[i]) {
                count[e.to]--;
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (d[i] == -1) {
            for (E e: rg[i]) {
                if (d[e.to]) continue;
                d[e.to] = 1;
                for (E f: rg[e.to]) {
                    count[f.to]--;
                }
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (count[i]) continue;
        q.push(i);
    }
    while (q.size()) {
        int p = q.front(); q.pop();
        if (d[p]) continue;
        d[p] = -1;
        for (E e: rg[p]) {
            if (d[e.to]) continue;
            d[e.to] = 1;
            for (E f: rg[e.to]) {
                count[f.to]--;
                if (!count[f.to]) {
                    q.push(f.to);
                }
            }
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/retrograde.hpp"
/**
 * d[i] = 
 *   -1:このマスからスタートすると先手が負ける
 *    0:?
 *    1:このマスからスタートすると先手が勝つ
 */
template<class E>
void retrograde(const Graph<E> &g, const Graph<E> &rg, vector<int> &d) {
    int V = (int)g.size();
    vector<int> count(V);
    for (int i = 0; i < V; i++) {
        count[i] = (int)g[i].size();
    }
    for (int i = 0; i < V; i++) {
        if (d[i] == 1) {
            for (E e: rg[i]) {
                count[e.to]--;
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (d[i] == -1) {
            for (E e: rg[i]) {
                if (d[e.to]) continue;
                d[e.to] = 1;
                for (E f: rg[e.to]) {
                    count[f.to]--;
                }
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (count[i]) continue;
        q.push(i);
    }
    while (q.size()) {
        int p = q.front(); q.pop();
        if (d[p]) continue;
        d[p] = -1;
        for (E e: rg[p]) {
            if (d[e.to]) continue;
            d[e.to] = 1;
            for (E f: rg[e.to]) {
                count[f.to]--;
                if (!count[f.to]) {
                    q.push(f.to);
                }
            }
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

