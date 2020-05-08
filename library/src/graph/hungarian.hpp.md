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


# :warning: src/graph/hungarian.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/hungarian.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
割当問題を解き，以下の条件を満たすle, ri, permを得る
- le[i] <= 0, ri[j] >= 0
- cost[i][j] + le[i] + ri[j] >= 0
- cost[i][perm[i]] + le[i] + ri[perm[i]] = 0
*/
template<class D>
struct Hungarian {
    V<D> le, ri;
    V<int> perm;

    Hungarian(const VV<D>& c) {
        int n = int(c.size()), m = int(c[0].size());
        assert(n <= m);
        le = V<D>(n, D(0)); ri = V<D>(m, D(0));
        perm = V<int>(n);
        V<int> to_r(n, -1), to_l(m, -1);

        for (int s = 0; s < n; s++) {
            V<char> l_u(n), r_u(m);
            l_u[s] = true;
            V<int> tr(m, -1), min_l(m, s);
            V<D> min_cost(m);
            for (int j = 0; j < m; j++) min_cost[j] = c[s][j] + le[s] + ri[j];
            while (true) {
                int r = -1;
                D d = numeric_limits<D>::max();
                for (int j = 0; j < m; j++) {
                    if (!r_u[j] && min_cost[j] < d) {
                        r = j;
                        d = min_cost[j];
                    }
                }
                for (int i = 0; i < n; i++) if (l_u[i]) le[i] -= d;
                for (int j = 0; j < m; j++) {
                    if (r_u[j]) ri[j] += d;
                    else min_cost[j] -= d;
                }
                tr[r] = min_l[r];
                int l = to_l[r];
                if (l == -1) {
                    while (r != -1) {
                        int nl = tr[r], nr = to_r[nl];
                        to_l[r] = nl; to_r[nl] = r;
                        r = nr;
                    }
                    break;
                }
                l_u[l] = r_u[r] = true;
                for (int j = 0; j < m; j++) {
                    D cost = c[l][j] + le[l] + ri[j];
                    if (cost < min_cost[j]) {
                        min_l[j] = l;
                        min_cost[j] = cost;
                    }
                }
            }
        }
        perm = to_r;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/hungarian.hpp"
/**
割当問題を解き，以下の条件を満たすle, ri, permを得る
- le[i] <= 0, ri[j] >= 0
- cost[i][j] + le[i] + ri[j] >= 0
- cost[i][perm[i]] + le[i] + ri[perm[i]] = 0
*/
template<class D>
struct Hungarian {
    V<D> le, ri;
    V<int> perm;

    Hungarian(const VV<D>& c) {
        int n = int(c.size()), m = int(c[0].size());
        assert(n <= m);
        le = V<D>(n, D(0)); ri = V<D>(m, D(0));
        perm = V<int>(n);
        V<int> to_r(n, -1), to_l(m, -1);

        for (int s = 0; s < n; s++) {
            V<char> l_u(n), r_u(m);
            l_u[s] = true;
            V<int> tr(m, -1), min_l(m, s);
            V<D> min_cost(m);
            for (int j = 0; j < m; j++) min_cost[j] = c[s][j] + le[s] + ri[j];
            while (true) {
                int r = -1;
                D d = numeric_limits<D>::max();
                for (int j = 0; j < m; j++) {
                    if (!r_u[j] && min_cost[j] < d) {
                        r = j;
                        d = min_cost[j];
                    }
                }
                for (int i = 0; i < n; i++) if (l_u[i]) le[i] -= d;
                for (int j = 0; j < m; j++) {
                    if (r_u[j]) ri[j] += d;
                    else min_cost[j] -= d;
                }
                tr[r] = min_l[r];
                int l = to_l[r];
                if (l == -1) {
                    while (r != -1) {
                        int nl = tr[r], nr = to_r[nl];
                        to_l[r] = nl; to_r[nl] = r;
                        r = nr;
                    }
                    break;
                }
                l_u[l] = r_u[r] = true;
                for (int j = 0; j < m; j++) {
                    D cost = c[l][j] + le[l] + ri[j];
                    if (cost < min_cost[j]) {
                        min_l[j] = l;
                        min_cost[j] = cost;
                    }
                }
            }
        }
        perm = to_r;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

