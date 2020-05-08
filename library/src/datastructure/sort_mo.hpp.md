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


# :warning: src/datastructure/sort_mo.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/sort_mo.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 普通にsortした方が早くない？困ったね
template <class Q> void sort_mo(V<Q>& ques) {
    auto dist = [&](Q x, Q y) { return abs(x.l - y.l) + abs(x.r - y.r); };
    int n = int(ques.size());
    if (n <= 1) return;

    // ordered by manhattan mst (tsp approx)
    {
        VV<int> tr(n);
        V<pair<int, int>> ps(n);
        for (int i = 0; i < n; i++) {
            ps[i] = {ques[i].l, ques[i].r};
        }
        auto edges = manhattan_mst(ps);
        for (auto e : edges) {
            tr[e.first].push_back(e.second);
            tr[e.second].push_back(e.first);
        }
        V<Q> nques;
        auto dfs = [&](auto self, int p, int b) -> void {
            nques.push_back(ques[p]);
            for (auto d : tr[p]) {
                if (d == b) continue;
                self(self, d, p);
            }
        };
        dfs(dfs, 0, -1);
        ques = nques;
    }
    // 2-opt
    for (int ph = 0; ph < 10; ph++) {
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < min(i + 10, n - 1); j++) {
                ll pre =
                    dist(ques[i - 1], ques[i]) + dist(ques[j], ques[j + 1]);
                ll now =
                    dist(ques[i - 1], ques[j]) + dist(ques[i], ques[j + 1]);
                if (now < pre) {
                    reverse(ques.begin() + i, ques.begin() + j + 1);
                }
            }
        }
    }
    // reverse first
    {
        int mi = TEN(9), idx = -1;
        for (int i = 0; i < n - 1; i++) {
            int nw = abs(ques[i].l - ques[i].r) + dist(ques[0], ques[i + 1]);
            if (nw < mi) {
                mi = nw;
                idx = i;
            }
        }
        reverse(ques.begin(), ques.begin() + idx + 1);
    }
    // reverse last
    {
        int mi = TEN(9), idx = -1;
        for (int i = 1; i < n; i++) {
            int nw = dist(ques[i - 1], ques[n - 1]);
            if (nw < mi) {
                mi = nw;
                idx = i;
            }
        }
        reverse(ques.begin() + idx, ques.end());
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/sort_mo.hpp"
// 普通にsortした方が早くない？困ったね
template <class Q> void sort_mo(V<Q>& ques) {
    auto dist = [&](Q x, Q y) { return abs(x.l - y.l) + abs(x.r - y.r); };
    int n = int(ques.size());
    if (n <= 1) return;

    // ordered by manhattan mst (tsp approx)
    {
        VV<int> tr(n);
        V<pair<int, int>> ps(n);
        for (int i = 0; i < n; i++) {
            ps[i] = {ques[i].l, ques[i].r};
        }
        auto edges = manhattan_mst(ps);
        for (auto e : edges) {
            tr[e.first].push_back(e.second);
            tr[e.second].push_back(e.first);
        }
        V<Q> nques;
        auto dfs = [&](auto self, int p, int b) -> void {
            nques.push_back(ques[p]);
            for (auto d : tr[p]) {
                if (d == b) continue;
                self(self, d, p);
            }
        };
        dfs(dfs, 0, -1);
        ques = nques;
    }
    // 2-opt
    for (int ph = 0; ph < 10; ph++) {
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < min(i + 10, n - 1); j++) {
                ll pre =
                    dist(ques[i - 1], ques[i]) + dist(ques[j], ques[j + 1]);
                ll now =
                    dist(ques[i - 1], ques[j]) + dist(ques[i], ques[j + 1]);
                if (now < pre) {
                    reverse(ques.begin() + i, ques.begin() + j + 1);
                }
            }
        }
    }
    // reverse first
    {
        int mi = TEN(9), idx = -1;
        for (int i = 0; i < n - 1; i++) {
            int nw = abs(ques[i].l - ques[i].r) + dist(ques[0], ques[i + 1]);
            if (nw < mi) {
                mi = nw;
                idx = i;
            }
        }
        reverse(ques.begin(), ques.begin() + idx + 1);
    }
    // reverse last
    {
        int mi = TEN(9), idx = -1;
        for (int i = 1; i < n; i++) {
            int nw = dist(ques[i - 1], ques[n - 1]);
            if (nw < mi) {
                mi = nw;
                idx = i;
            }
        }
        reverse(ques.begin() + idx, ques.end());
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

