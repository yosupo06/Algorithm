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


# :warning: src/datastructure/sparsetable.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/sparsetable.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class D, class OP> struct SparseTable {
    D e;
    OP op;
    VV<D> data;
    SparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int n = int(v.size());
        if (n == 0) return;
        int lg = bsr(uint(n)) + 1;
        data = VV<D>(lg);
        data[0] = v;
        int l = 1;
        for (int s = 1; s < lg; s++) {
            data[s] = V<D>(n);
            for (int i = 0; i < n - l; i++) {
                data[s][i] = op(data[s - 1][i], data[s - 1][i + l]);
            }
            l <<= 1;
        }
    }
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int u = bsr(uint(r - l));
        return op(data[u][l], data[u][r - (1 << u)]);
    }
};
template <class D, class OP>
SparseTable<D, OP> get_sparse_table(V<D> v, D e, OP op) {
    return SparseTable<D, OP>(v, e, op);
}

template <class D, class OP> struct LowMemorySparseTable {
    static constexpr int B = 16;
    V<D> data;
    D e;
    OP op;
    SparseTable<D, OP> st;
    V<D> comp_arr(V<D> v) {
        int n = int(v.size());
        V<D> comp(n / B);
        for (int i = 0; i < n / B; i++) {
            D res = data[i * B];
            for (int j = 1; j < B; j++) {
                res = op(res, data[i * B + j]);
            }
            comp[i] = res;
        }
        return comp;
    }
    LowMemorySparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())
        : data(v), e(_e), op(_op), st(comp_arr(v), _e, _op) {}
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int lb = (l + B - 1) / B, rb = r / B;
        D res = e;
        if (lb >= rb) {
            for (int i = l; i < r; i++) {
                res = op(res, data[i]);
            }
            return res;
        }

        while (l % B) {
            res = op(res, data[l]);
            l++;
        }
        while (r % B) {
            r--;
            res = op(res, data[r]);
        }
        res = op(res, st.query(lb, rb));
        return res;
    }
};
template <class D, class OP>
LowMemorySparseTable<D, OP> get_low_memory_sparse_table(V<D> v, D e, OP op) {
    return LowMemorySparseTable<D, OP>(v, e, op);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/sparsetable.hpp"
template <class D, class OP> struct SparseTable {
    D e;
    OP op;
    VV<D> data;
    SparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int n = int(v.size());
        if (n == 0) return;
        int lg = bsr(uint(n)) + 1;
        data = VV<D>(lg);
        data[0] = v;
        int l = 1;
        for (int s = 1; s < lg; s++) {
            data[s] = V<D>(n);
            for (int i = 0; i < n - l; i++) {
                data[s][i] = op(data[s - 1][i], data[s - 1][i + l]);
            }
            l <<= 1;
        }
    }
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int u = bsr(uint(r - l));
        return op(data[u][l], data[u][r - (1 << u)]);
    }
};
template <class D, class OP>
SparseTable<D, OP> get_sparse_table(V<D> v, D e, OP op) {
    return SparseTable<D, OP>(v, e, op);
}

template <class D, class OP> struct LowMemorySparseTable {
    static constexpr int B = 16;
    V<D> data;
    D e;
    OP op;
    SparseTable<D, OP> st;
    V<D> comp_arr(V<D> v) {
        int n = int(v.size());
        V<D> comp(n / B);
        for (int i = 0; i < n / B; i++) {
            D res = data[i * B];
            for (int j = 1; j < B; j++) {
                res = op(res, data[i * B + j]);
            }
            comp[i] = res;
        }
        return comp;
    }
    LowMemorySparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())
        : data(v), e(_e), op(_op), st(comp_arr(v), _e, _op) {}
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int lb = (l + B - 1) / B, rb = r / B;
        D res = e;
        if (lb >= rb) {
            for (int i = l; i < r; i++) {
                res = op(res, data[i]);
            }
            return res;
        }

        while (l % B) {
            res = op(res, data[l]);
            l++;
        }
        while (r % B) {
            r--;
            res = op(res, data[r]);
        }
        res = op(res, st.query(lb, rb));
        return res;
    }
};
template <class D, class OP>
LowMemorySparseTable<D, OP> get_low_memory_sparse_table(V<D> v, D e, OP op) {
    return LowMemorySparseTable<D, OP>(v, e, op);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

