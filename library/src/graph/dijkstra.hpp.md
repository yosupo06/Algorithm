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


# :warning: src/graph/dijkstra.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/dijkstra.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class D> struct MinDist {
    V<D> dist;
    V<int> from;
};

template <class D, class E>
MinDist<D> mindist(const VV<E>& g, int s, D inf = numeric_limits<D>::max()) {
    int n = (int)g.size();
    V<D> dist = V<D>(n, inf);
    V<int> from = V<int>(n);
    struct P {
        D key;
        int to;
        bool operator<(P r) const { return key > r.key; }
    };
    priority_queue<P> q;
    q.push(P{0, s});
    dist[s] = D(0);
    while (!q.empty()) {
        P p = q.top();
        q.pop();
        if (dist[p.to] < p.key) continue;
        for (E e : g[p.to]) {
            if (p.key + e.dist < dist[e.to]) {
                dist[e.to] = p.key + e.dist;
                from[e.to] = p.to;
                q.push(P{dist[e.to], e.to});
            }
        }
    }
    return MinDist<D>{dist, from};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/dijkstra.hpp"
template <class D> struct MinDist {
    V<D> dist;
    V<int> from;
};

template <class D, class E>
MinDist<D> mindist(const VV<E>& g, int s, D inf = numeric_limits<D>::max()) {
    int n = (int)g.size();
    V<D> dist = V<D>(n, inf);
    V<int> from = V<int>(n);
    struct P {
        D key;
        int to;
        bool operator<(P r) const { return key > r.key; }
    };
    priority_queue<P> q;
    q.push(P{0, s});
    dist[s] = D(0);
    while (!q.empty()) {
        P p = q.top();
        q.pop();
        if (dist[p.to] < p.key) continue;
        for (E e : g[p.to]) {
            if (p.key + e.dist < dist[e.to]) {
                dist[e.to] = p.key + e.dist;
                from[e.to] = p.to;
                q.push(P{dist[e.to], e.to});
            }
        }
    }
    return MinDist<D>{dist, from};
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

