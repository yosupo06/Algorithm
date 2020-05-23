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


# :heavy_check_mark: src/datastructure/segtree.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/segtree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:08:12+09:00




## Depends on

* :question: <a href="../base.hpp.html">src/base.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/hl_vertex_add_path_sum.test.cpp.html">src/hl_vertex_add_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hl_vertex_add_subtree_sum.test.cpp.html">src/hl_vertex_add_subtree_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "base.hpp"

template <class D, class Op> struct SimpleSeg {
    D e;
    Op op;
    int n, sz, lg;  // size(extended to 2^i), lg
    V<D> d;

    SimpleSeg(const V<D>& v, D _e, Op _op) : e(_e), op(_op) {
        n = int(v.size());
        lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d = V<D>(2 * sz, e);
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 0; i--) {
            update(i);
        }
    }

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    void set(int p, D x) {
        assert(0 <= p && p < n);
        p += sz;
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    D single(int p) const {
        assert(0 <= p && p < n);
        return d[p + sz];
    }

    D sum(int a, int b) const {
        assert(a <= b);
        D sml = e, smr = e;
        a += sz;
        b += sz;

        while (a < b) {
            if (a & 1) sml = op(sml, d[a++]);
            if (b & 1) smr = op(d[--b], smr);
            a >>= 1;
            b >>= 1;
        }
        return op(sml, smr);
    }

    D all_sum() const {
        return d[1];
    }

    // min i s.t. f(d[a] + d[a+1] + ... d[i]) == true (or return n + 1)
    template <class Comp> int search_left(int a, Comp f) {
        a += sz;
        D sm = e;
        if (f(e)) return a;
        while (true) {
            if (f(op(sm, d[a]))) {
                while (a < sz) {
                    a *= 2;
                    if (!f(op(sm, d[a]))) {
                        sm = op(sm, d[a]);
                        a++;
                    }
                }
                a = a + 1 - sz;
                return a;
            }
            if (a & 1) {
                sm = op(sm, d[a]);
                a++;
                if ((a & -a) == a) break;
            }
            a >>= 1;
        }
        return n + 1;
    }
};

template <class D, class Op>
SimpleSeg<D, Op> get_simple_seg(V<D> v, D e, Op op) {
    return SimpleSeg<D, Op>(v, e, op);
}

template <class D, class L, class OpDD, class OpDL, class OpLL> struct SegTree {
    D e_d;
    L e_l;
    OpDD op_dd;
    OpDL op_dl;
    OpLL op_ll;
    int sz, lg;  //(2^lgに拡張後の)サイズ, lg
    V<D> d;
    V<L> lz;

    SegTree(const V<D>& v,
            D _e_d,
            L _e_l,
            OpDD _op_dd,
            OpDL _op_dl,
            OpLL _op_ll)
        : e_d(_e_d), e_l(_e_l), op_dd(_op_dd), op_dl(_op_dl), op_ll(_op_ll) {
        int n = int(v.size());
        lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d = V<D>(2 * sz, e_d);
        lz = V<L>(2 * sz, e_l);
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 0; i--) {
            update(i);
        }
    }

    void all_add(int k, L x) {
        d[k] = op_dl(d[k], x);
        lz[k] = op_ll(lz[k], x);
    }
    void push(int k) {
        all_add(2 * k, lz[k]);
        all_add(2 * k + 1, lz[k]);
        lz[k] = e_l;
    }
    void update(int k) { d[k] = op_dd(d[2 * k], d[2 * k + 1]); }

    void set(int p, D x) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    void add(int a, int b, L x, int l, int r, int k) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            all_add(k, x);
            return;
        }
        push(k);
        int mid = (l + r) / 2;
        add(a, b, x, l, mid, 2 * k);
        add(a, b, x, mid, r, 2 * k + 1);
        update(k);
    }
    void add(int a, int b, L x) { add(a, b, x, 0, sz, 1); }

    D single(int p) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }

    D sum(int a, int b, int l, int r, int k) {
        if (b <= l || r <= a) return e_d;
        if (a <= l && r <= b) return d[k];
        push(k);
        int mid = (l + r) / 2;
        return op_dd(sum(a, b, l, mid, 2 * k), sum(a, b, mid, r, 2 * k + 1));
    }
    D sum(int a, int b) { return sum(a, b, 0, sz, 1); }

    D all_sum() const { return d[1]; }
};

template <class D, class L, class OpDD, class OpDL, class OpLL>
SegTree<D, L, OpDD, OpDL, OpLL> get_seg(V<D> v,
                                        D e_d,
                                        L e_l,
                                        OpDD op_dd,
                                        OpDL op_dl,
                                        OpLL op_ll) {
    return SegTree<D, L, OpDD, OpDL, OpLL>(v, e_d, e_l, op_dd, op_dl, op_ll);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 172, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 162, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: base.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

