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


# :warning: src/graph/directedmst.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/directedmst.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class E>
struct DirectedMST {
    decltype(E::dist) cost = 0;
    V<E> mine; // min edge
    DirectedMST(const Graph<E> &g, int r) {
        int n = (int)g.size();
        mine = vector<E>(n);
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            assert((int)g[i].size());
            mine[i] = *min_element(g[i].begin(), g[i].end(),
                [](const E &l, const E &r){return l.dist < r.dist;});
            cost += mine[i].dist;
        }
        V<int> i2g(n, -1); i2g[r] = 0;
        int gc = 1;
        for (int i = 0; i < n; i++) {
            if (i2g[i] != -1) continue;
            int j = i;
            do {
                i2g[j] = gc++;
            } while (j = mine[j].to, i2g[j] == -1);
            if (i2g[j] < i2g[i]) continue;
            //roop
            int k = j;
            do {
                i2g[k] = i2g[j];
            } while(k = mine[k].to, k != j);
            gc = i2g[j]+1;
        }
        if (gc == n) return;
        Graph<E> ng(gc);
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            for (E e: g[i]) {
                if (i2g[e.to] == i2g[i]) continue;
                e.to = i2g[e.to];
                e.dist -= mine[i].dist;
                ng[i2g[i]].push_back(e);
            }
        }
        auto nme = DirectedMST(ng, 0).mine;
        vector<bool> ok(gc, false);
        for (int i = 0; i < n; i++) {
            if (i == r or ok[i2g[i]]) continue;
            for (E e: g[i]) {
                if (e.dist - mine[i].dist == nme[i2g[i]].dist) {
                    ok[i2g[i]] = true;
                    mine[i] = e;
                    cost += nme[i2g[i]].dist;
                    break;
                }
            }
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/directedmst.hpp"
template<class E>
struct DirectedMST {
    decltype(E::dist) cost = 0;
    V<E> mine; // min edge
    DirectedMST(const Graph<E> &g, int r) {
        int n = (int)g.size();
        mine = vector<E>(n);
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            assert((int)g[i].size());
            mine[i] = *min_element(g[i].begin(), g[i].end(),
                [](const E &l, const E &r){return l.dist < r.dist;});
            cost += mine[i].dist;
        }
        V<int> i2g(n, -1); i2g[r] = 0;
        int gc = 1;
        for (int i = 0; i < n; i++) {
            if (i2g[i] != -1) continue;
            int j = i;
            do {
                i2g[j] = gc++;
            } while (j = mine[j].to, i2g[j] == -1);
            if (i2g[j] < i2g[i]) continue;
            //roop
            int k = j;
            do {
                i2g[k] = i2g[j];
            } while(k = mine[k].to, k != j);
            gc = i2g[j]+1;
        }
        if (gc == n) return;
        Graph<E> ng(gc);
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            for (E e: g[i]) {
                if (i2g[e.to] == i2g[i]) continue;
                e.to = i2g[e.to];
                e.dist -= mine[i].dist;
                ng[i2g[i]].push_back(e);
            }
        }
        auto nme = DirectedMST(ng, 0).mine;
        vector<bool> ok(gc, false);
        for (int i = 0; i < n; i++) {
            if (i == r or ok[i2g[i]]) continue;
            for (E e: g[i]) {
                if (e.dist - mine[i].dist == nme[i2g[i]].dist) {
                    ok[i2g[i]] = true;
                    mine[i] = e;
                    cost += nme[i2g[i]].dist;
                    break;
                }
            }
        }
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

