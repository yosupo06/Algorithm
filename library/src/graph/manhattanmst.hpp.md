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


# :warning: src/graph/manhattanmst.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/manhattanmst.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T>
V<pair<int, int>> manhattan_mst(V<pair<T, T>> ps,
                                T inf = numeric_limits<T>::max()) {
    V<pair<int, int>> edges;
    int n = int(ps.size());
    V<int> ids(n);
    iota(ids.begin(), ids.end(), 0);
    for (int ph = 0; ph < 4; ph++) {
        sort(ids.begin(), ids.end(), [&](auto i, auto j) {
            T ixy = (ps[i].first + ps[i].second),
              jxy = (ps[j].first + ps[j].second);
            return tie(ixy, ps[i].second) > tie(jxy, ps[j].second);
        });
        V<T> xv;
        for (int i = 0; i < n; i++) xv.push_back(ps[i].first);
        sort(xv.begin(), xv.end());
        xv.erase(unique(xv.begin(), xv.end()), xv.end());
        using P = pair<T, int>;
        V<P> fen(n, P(-inf, -1));
        for (int id : ids) {
            auto xi = int(lower_bound(xv.begin(), xv.end(), ps[id].first) -
                          xv.begin());
            P ma = P(-inf, -1);
            {
                int i = xi + 1;
                while (i > 0) {
                    if (ma.first <= fen[i - 1].first) ma = fen[i - 1];
                    i -= i & -i;
                }
            }
            if (ma.second != -1) edges.push_back({id, ma.second});
            {
                T x = ps[id].first - ps[id].second;
                int i = xi + 1;
                while (i <= n) {
                    if (fen[i - 1].first <= x) fen[i - 1] = P(x, id);
                    i += i & -i;
                }
            }
        }

        for (auto& p : ps) {
            swap(p.first, p.second);
        }
        if (ph == 1) {
            for (auto& p : ps) {
                p.second *= -1;
            }
        }
    }
    auto dist = [&](int i, int j) {
        return abs(ps[i].first - ps[j].first) +
               abs(ps[i].second - ps[j].second);
    };
    sort(edges.begin(), edges.end(), [&](auto x, auto y) {
        return dist(x.first, x.second) < dist(y.first, y.second);
    });
    auto uf = UnionFind(n);
    V<pair<int, int>> res;
    for (auto p : edges) {
        if (uf.same(p.first, p.second)) continue;
        res.push_back(p);
        uf.merge(p.first, p.second);
    }
    return res;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/manhattanmst.hpp"
template <class T>
V<pair<int, int>> manhattan_mst(V<pair<T, T>> ps,
                                T inf = numeric_limits<T>::max()) {
    V<pair<int, int>> edges;
    int n = int(ps.size());
    V<int> ids(n);
    iota(ids.begin(), ids.end(), 0);
    for (int ph = 0; ph < 4; ph++) {
        sort(ids.begin(), ids.end(), [&](auto i, auto j) {
            T ixy = (ps[i].first + ps[i].second),
              jxy = (ps[j].first + ps[j].second);
            return tie(ixy, ps[i].second) > tie(jxy, ps[j].second);
        });
        V<T> xv;
        for (int i = 0; i < n; i++) xv.push_back(ps[i].first);
        sort(xv.begin(), xv.end());
        xv.erase(unique(xv.begin(), xv.end()), xv.end());
        using P = pair<T, int>;
        V<P> fen(n, P(-inf, -1));
        for (int id : ids) {
            auto xi = int(lower_bound(xv.begin(), xv.end(), ps[id].first) -
                          xv.begin());
            P ma = P(-inf, -1);
            {
                int i = xi + 1;
                while (i > 0) {
                    if (ma.first <= fen[i - 1].first) ma = fen[i - 1];
                    i -= i & -i;
                }
            }
            if (ma.second != -1) edges.push_back({id, ma.second});
            {
                T x = ps[id].first - ps[id].second;
                int i = xi + 1;
                while (i <= n) {
                    if (fen[i - 1].first <= x) fen[i - 1] = P(x, id);
                    i += i & -i;
                }
            }
        }

        for (auto& p : ps) {
            swap(p.first, p.second);
        }
        if (ph == 1) {
            for (auto& p : ps) {
                p.second *= -1;
            }
        }
    }
    auto dist = [&](int i, int j) {
        return abs(ps[i].first - ps[j].first) +
               abs(ps[i].second - ps[j].second);
    };
    sort(edges.begin(), edges.end(), [&](auto x, auto y) {
        return dist(x.first, x.second) < dist(y.first, y.second);
    });
    auto uf = UnionFind(n);
    V<pair<int, int>> res;
    for (auto p : edges) {
        if (uf.same(p.first, p.second)) continue;
        res.push_back(p);
        uf.merge(p.first, p.second);
    }
    return res;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

