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


# :warning: src/tree/centroid.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#3698aa34afa89577c63cbcf539eb96f7">src/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/tree/centroid.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Required by

* :warning: <a href="../graph/balancedseparator.hpp.html">src/graph/balancedseparator.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

struct Centroid {
    int r;
    VV<int> tr;
    V<int> par;
};

template <class E> struct CentroidExec : Centroid {
    int n;
    const VV<E>& g;
    V<bool> used;

    using P = pair<int, int>;
    V<P> info;  //(child max, child)

    int dfs(int p, int b) {
        int sz = 1;
        info[p] = P(0, -1);
        for (E e : g[p]) {
            int d = e.to;
            if (d == b || used[d]) continue;
            int csz = dfs(d, p);
            sz += csz;
            info[p] = max(info[p], P(csz, d));
        }
        return sz;
    }
    int init(int p, int b) {
        int sz = dfs(p, -1);
        while (info[p].first > sz / 2) p = info[p].second;
        par[p] = b;
        used[p] = true;
        for (E e : g[p]) {
            int d = e.to;
            if (used[d]) continue;
            tr[p].push_back(init(d, p));
        }
        return p;
    }
    CentroidExec(const VV<E>& _g) : n(int(_g.size())), g(_g), used(n), info(n) {
        tr = VV<int>(n);
        par = V<int>(n);
        r = init(0, -1);
    }
};

template <class E> Centroid get_centroid(const VV<E>& g) {
    return CentroidExec<E>(g);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/tree/centroid.hpp"

struct Centroid {
    int r;
    VV<int> tr;
    V<int> par;
};

template <class E> struct CentroidExec : Centroid {
    int n;
    const VV<E>& g;
    V<bool> used;

    using P = pair<int, int>;
    V<P> info;  //(child max, child)

    int dfs(int p, int b) {
        int sz = 1;
        info[p] = P(0, -1);
        for (E e : g[p]) {
            int d = e.to;
            if (d == b || used[d]) continue;
            int csz = dfs(d, p);
            sz += csz;
            info[p] = max(info[p], P(csz, d));
        }
        return sz;
    }
    int init(int p, int b) {
        int sz = dfs(p, -1);
        while (info[p].first > sz / 2) p = info[p].second;
        par[p] = b;
        used[p] = true;
        for (E e : g[p]) {
            int d = e.to;
            if (used[d]) continue;
            tr[p].push_back(init(d, p));
        }
        return p;
    }
    CentroidExec(const VV<E>& _g) : n(int(_g.size())), g(_g), used(n), info(n) {
        tr = VV<int>(n);
        par = V<int>(n);
        r = init(0, -1);
    }
};

template <class E> Centroid get_centroid(const VV<E>& g) {
    return CentroidExec<E>(g);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

