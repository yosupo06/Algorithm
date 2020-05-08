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


# :warning: src/graph/bidirectedcut.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/bidirectedcut.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class D, D INF>
struct BidirectedCut {
    D sum = INF;
    template<class E>
    BidirectedCut(VV<E> g) {
        int n = (int)g.size();
        int m_a = -1, m_b = -1;
        V<D> dist_base(n, 0);
        for (int m = n; m > 1; m--) {
            int a, b;
            auto dist = dist_base;
            for (int i = 0; i < m; i++) {
                a = b; b = max_element(begin(dist), end(dist)) - begin(dist);
                if (i == m-1) sum = min(sum, dist[b]);
                dist[b] = -INF;
                for (E &e: g[b]) {
                    if (e.to == m_b) e.to = m_a;
                    if (dist[e.to] == -INF) continue;
                    dist[e.to] += e.dist;
                }
            }
            //merge a, b
            m_a = a; m_b = b;
            g[a].insert(end(g[a]), begin(g[b]), end(g[b]));
            g[b].clear();
            dist_base[b] = -INF;
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/bidirectedcut.hpp"
template<class D, D INF>
struct BidirectedCut {
    D sum = INF;
    template<class E>
    BidirectedCut(VV<E> g) {
        int n = (int)g.size();
        int m_a = -1, m_b = -1;
        V<D> dist_base(n, 0);
        for (int m = n; m > 1; m--) {
            int a, b;
            auto dist = dist_base;
            for (int i = 0; i < m; i++) {
                a = b; b = max_element(begin(dist), end(dist)) - begin(dist);
                if (i == m-1) sum = min(sum, dist[b]);
                dist[b] = -INF;
                for (E &e: g[b]) {
                    if (e.to == m_b) e.to = m_a;
                    if (dist[e.to] == -INF) continue;
                    dist[e.to] += e.dist;
                }
            }
            //merge a, b
            m_a = a; m_b = b;
            g[a].insert(end(g[a]), begin(g[b]), end(g[b]));
            g[b].clear();
            dist_base[b] = -INF;
        }
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

