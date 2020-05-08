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


# :warning: src/graph/matroidintersection.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/matroidintersection.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

/*
elements: matroid elements
on: used elements
f: lambda, f(on, g1(i, j), g2(i, j))と呼ばれるので
そのまま足せる要素についてg(i, -1)を呼び、交換できるペアについてg(i, j)を呼ぶ
*/
template <class E, class F>
bool matroid_intersection(const V<E>& elements, V<bool>& on, F& f) {
    int m = int(elements.size());
    assert(int(on.size()) == m);
    VV<int> g(m);
    V<bool> st(m), ed(m);
    f(on,
      [&](int u, int v) {
          assert(0 <= u && u < m && !on[u]);
          if (v == -1)
              st[u] = true;
          else {
              assert(0 <= v && v < m && on[v]);
              g[v].push_back(u);
          }
      },
      [&](int u, int v) {
          assert(0 <= u && u < m && !on[u]);
          if (v == -1)
              ed[u] = true;
          else {
              assert(0 <= v && v < m && on[v]);
              g[u].push_back(v);
          }
      });
    V<int> prev(m, -1);
    V<int> dist(m, TEN(9));
    queue<int> que;
    for (int i = 0; i < m; i++) {
        if (st[i]) {
            dist[i] = 0;
            que.push(i);
        }
    }

    while (que.size()) {
        int p = que.front();
        que.pop();
        if (ed[p]) {
            int now = p;
            while (now != -1) {
                on[now] = !on[now];
                now = prev[now];
            }
            return true;
        }
        for (int d : g[p]) {
            if (dist[d] > dist[p] + 1) {
                dist[d] = dist[p] + 1;
                prev[d] = p;
                que.push(d);
            }
        }
    }
    return false;
}
template <class E, class F>
V<bool> matroid_intersection(const V<E>& elements, F f) {
    int m = int(elements.size());
    V<bool> on(m);
    while (matroid_intersection(elements, on, f)) {
    }
    return on;
}

/*
void CFHello2020G {
    // forest * choise
    auto used =
        matroid_intersection(es, [&](const V<bool>& on, auto g1, auto g2) {
            auto base = UnionFind(n);
            V<int> cnt(n);
            for (int l = 0; l < m; l++) {
                if (!on[l]) continue;
                base.merge(es[l].from, es[l].to);
                cnt[es[l].id]++;
            }
            for (int r = 0; r < m; r++) {
                if (on[r]) continue;
                if (!base.same(es[r].from, es[r].to)) g1(r, -1);
                if (cnt[es[r].id] == 0) g2(r, -1);
            }
            for (int l = 0; l < m; l++) {
                if (!on[l]) continue;
                auto uf = UnionFind(n);
                for (int i = 0; i < m; i++) {
                    if (!on[i] || i == l) continue;
                    uf.merge(es[i].from, es[i].to);
                }
                for (int r = 0; r < m; r++) {
                    if (on[r]) continue;
                    if (!uf.same(es[r].from, es[r].to)) g1(r, l);
                    if (es[l].id == es[r].id) g2(r, l);
                }
            }
        });
}*/

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/graph/matroidintersection.hpp"

/*
elements: matroid elements
on: used elements
f: lambda, f(on, g1(i, j), g2(i, j))と呼ばれるので
そのまま足せる要素についてg(i, -1)を呼び、交換できるペアについてg(i, j)を呼ぶ
*/
template <class E, class F>
bool matroid_intersection(const V<E>& elements, V<bool>& on, F& f) {
    int m = int(elements.size());
    assert(int(on.size()) == m);
    VV<int> g(m);
    V<bool> st(m), ed(m);
    f(on,
      [&](int u, int v) {
          assert(0 <= u && u < m && !on[u]);
          if (v == -1)
              st[u] = true;
          else {
              assert(0 <= v && v < m && on[v]);
              g[v].push_back(u);
          }
      },
      [&](int u, int v) {
          assert(0 <= u && u < m && !on[u]);
          if (v == -1)
              ed[u] = true;
          else {
              assert(0 <= v && v < m && on[v]);
              g[u].push_back(v);
          }
      });
    V<int> prev(m, -1);
    V<int> dist(m, TEN(9));
    queue<int> que;
    for (int i = 0; i < m; i++) {
        if (st[i]) {
            dist[i] = 0;
            que.push(i);
        }
    }

    while (que.size()) {
        int p = que.front();
        que.pop();
        if (ed[p]) {
            int now = p;
            while (now != -1) {
                on[now] = !on[now];
                now = prev[now];
            }
            return true;
        }
        for (int d : g[p]) {
            if (dist[d] > dist[p] + 1) {
                dist[d] = dist[p] + 1;
                prev[d] = p;
                que.push(d);
            }
        }
    }
    return false;
}
template <class E, class F>
V<bool> matroid_intersection(const V<E>& elements, F f) {
    int m = int(elements.size());
    V<bool> on(m);
    while (matroid_intersection(elements, on, f)) {
    }
    return on;
}

/*
void CFHello2020G {
    // forest * choise
    auto used =
        matroid_intersection(es, [&](const V<bool>& on, auto g1, auto g2) {
            auto base = UnionFind(n);
            V<int> cnt(n);
            for (int l = 0; l < m; l++) {
                if (!on[l]) continue;
                base.merge(es[l].from, es[l].to);
                cnt[es[l].id]++;
            }
            for (int r = 0; r < m; r++) {
                if (on[r]) continue;
                if (!base.same(es[r].from, es[r].to)) g1(r, -1);
                if (cnt[es[r].id] == 0) g2(r, -1);
            }
            for (int l = 0; l < m; l++) {
                if (!on[l]) continue;
                auto uf = UnionFind(n);
                for (int i = 0; i < m; i++) {
                    if (!on[i] || i == l) continue;
                    uf.merge(es[i].from, es[i].to);
                }
                for (int r = 0; r < m; r++) {
                    if (on[r]) continue;
                    if (!uf.same(es[r].from, es[r].to)) g1(r, l);
                    if (es[l].id == es[r].id) g2(r, l);
                }
            }
        });
}*/

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

