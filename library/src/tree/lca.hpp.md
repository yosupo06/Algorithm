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


# :warning: src/tree/lca.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#3698aa34afa89577c63cbcf539eb96f7">src/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/tree/lca.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

struct LCA {
    int lg;
    VV<int> anc;
    V<int> dps;
    /// lとrの頂点のLCAを求める
    int query(int l, int r) {
        if (dps[l] < dps[r]) swap(l, r);
        int dd = dps[l] - dps[r];
        for (int i = lg - 1; i >= 0; i--) {
            if (dd < (1 << i)) continue;
            dd -= 1 << i;
            l = anc[i][l];
        }
        if (l == r) return l;
        for (int i = lg - 1; i >= 0; i--) {
            if (anc[i][l] == anc[i][r]) continue;
            tie(l, r) = tie(anc[i][l], anc[i][r]);
        }
        return anc[0][l];
    }
    int up(int p, int dist) {
        for (int i = lg - 1; i >= 0; i--) {
            if (dist >= (1 << i)) {
                dist -= 1 << i;
                p = anc[i][p];
            }
        }
        return p;
    }
    int dist(int l, int r) {
        int z = query(l, r);
        return dps[l] + dps[r] - 2 * dps[z];
    }
};

template <class E> struct LCAExec : LCA {
    const VV<E>& g;

    /// 事前処理を行う rはroot頂点のid
    LCAExec(const VV<E>& _g, int r) : g(_g) {
        int N = int(g.size());
        lg = 1;
        while ((1 << lg) < N) lg++;
        anc = VV<int>(lg, V<int>(N, -1));
        dps = V<int>(N);
        dfs(r, -1, 0);
        for (int i = 1; i < lg; i++) {
            for (int j = 0; j < N; j++) {
                anc[i][j] =
                    (anc[i - 1][j] == -1) ? -1 : anc[i - 1][anc[i - 1][j]];
            }
        }
    }

    void dfs(int p, int b, int now) {
        anc[0][p] = b;
        dps[p] = now;
        for (E e : g[p]) {
            if (e.to == b) continue;
            dfs(e.to, p, now + 1);
        }
    }
};

template <class E> LCA get_lca(const VV<E>& g, int r) {
    return LCAExec<E>(g, r);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/tree/lca.hpp"

struct LCA {
    int lg;
    VV<int> anc;
    V<int> dps;
    /// lとrの頂点のLCAを求める
    int query(int l, int r) {
        if (dps[l] < dps[r]) swap(l, r);
        int dd = dps[l] - dps[r];
        for (int i = lg - 1; i >= 0; i--) {
            if (dd < (1 << i)) continue;
            dd -= 1 << i;
            l = anc[i][l];
        }
        if (l == r) return l;
        for (int i = lg - 1; i >= 0; i--) {
            if (anc[i][l] == anc[i][r]) continue;
            tie(l, r) = tie(anc[i][l], anc[i][r]);
        }
        return anc[0][l];
    }
    int up(int p, int dist) {
        for (int i = lg - 1; i >= 0; i--) {
            if (dist >= (1 << i)) {
                dist -= 1 << i;
                p = anc[i][p];
            }
        }
        return p;
    }
    int dist(int l, int r) {
        int z = query(l, r);
        return dps[l] + dps[r] - 2 * dps[z];
    }
};

template <class E> struct LCAExec : LCA {
    const VV<E>& g;

    /// 事前処理を行う rはroot頂点のid
    LCAExec(const VV<E>& _g, int r) : g(_g) {
        int N = int(g.size());
        lg = 1;
        while ((1 << lg) < N) lg++;
        anc = VV<int>(lg, V<int>(N, -1));
        dps = V<int>(N);
        dfs(r, -1, 0);
        for (int i = 1; i < lg; i++) {
            for (int j = 0; j < N; j++) {
                anc[i][j] =
                    (anc[i - 1][j] == -1) ? -1 : anc[i - 1][anc[i - 1][j]];
            }
        }
    }

    void dfs(int p, int b, int now) {
        anc[0][p] = b;
        dps[p] = now;
        for (E e : g[p]) {
            if (e.to == b) continue;
            dfs(e.to, p, now + 1);
        }
    }
};

template <class E> LCA get_lca(const VV<E>& g, int r) {
    return LCAExec<E>(g, r);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

