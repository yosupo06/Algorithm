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


# :warning: src/datastructure/disjointtable.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/disjointtable.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class D, class OP> struct DisjointTable {
    D e;
    OP op;
    VV<D> data;
    DisjointTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int lg = 1;
        while ((1 << lg) < int(v.size())) lg++;
        int n = 1 << lg;
        v.resize(n, e);
        data = VV<D>(lg, V<D>(n));
        data[0] = v;
        for (int h = 1; h < lg; h++) {
            int u = (1 << h);
            for (int i = 0; i < n / (2 * u); i++) {
                int base = i * (2 * u) + u;
                D res;
                res = e;
                for (int j = base - 1; j >= base - u; j--) {
                    res = op(v[j], res);
                    data[h][j] = res;
                }
                res = e;
                for (int j = base; j < base + u; j++) {
                    res = op(res, v[j]);
                    data[h][j] = res;
                }
            }
        }
    }
    D query(int l, int r) {
        r--;
        if (l > r) return e;
        if (l == r) return data[0][l];
        int u = bsr(uint(l ^ r));
        return op(data[u][l], data[u][r]);
    }
};

template <class D, class OP>
DisjointTable<D, OP> get_disjoint_table(V<D> v, D e, OP op) {
    return DisjointTable<D, OP>(v, e, op);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/disjointtable.hpp"
template <class D, class OP> struct DisjointTable {
    D e;
    OP op;
    VV<D> data;
    DisjointTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int lg = 1;
        while ((1 << lg) < int(v.size())) lg++;
        int n = 1 << lg;
        v.resize(n, e);
        data = VV<D>(lg, V<D>(n));
        data[0] = v;
        for (int h = 1; h < lg; h++) {
            int u = (1 << h);
            for (int i = 0; i < n / (2 * u); i++) {
                int base = i * (2 * u) + u;
                D res;
                res = e;
                for (int j = base - 1; j >= base - u; j--) {
                    res = op(v[j], res);
                    data[h][j] = res;
                }
                res = e;
                for (int j = base; j < base + u; j++) {
                    res = op(res, v[j]);
                    data[h][j] = res;
                }
            }
        }
    }
    D query(int l, int r) {
        r--;
        if (l > r) return e;
        if (l == r) return data[0][l];
        int u = bsr(uint(l ^ r));
        return op(data[u][l], data[u][r]);
    }
};

template <class D, class OP>
DisjointTable<D, OP> get_disjoint_table(V<D> v, D e, OP op) {
    return DisjointTable<D, OP>(v, e, op);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

