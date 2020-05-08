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


# :heavy_check_mark: src/datastructure/linkcuttree.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/linkcuttree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/src/lctree_lca.test.cpp.html">src/lctree_lca.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/lctree_vertex_add_path_sum.test.cpp.html">src/lctree_vertex_add_path_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class N> struct LCNode {
    using NP = LCNode*;
    using D = typename N::D;
    NP p = nullptr, l = nullptr, r = nullptr;
    int sz = 1;
    bool rev = false;
    D v = N::e_d(), sm = N::e_d();

    void single_set(D x) {
        v = x;
        update();
    }
    void single_add(D x) {
        v = N::op_dd(v, x);
        update();
    }

    void init_node(D _v) {
        v = _v;
        sm = _v;
    }
    void update() {
        sz = 1;
        if (l) sz += l->sz;
        if (r) sz += r->sz;
        sm = l ? N::op_dd(l->sm, v) : v;
        if (r) sm = N::op_dd(sm, r->sm);
    }
    void push() {
        if (rev) {
            if (l) l->revdata();
            if (r) r->revdata();
            rev = false;
        }
    }
    void revdata() {
        rev ^= true;
        swap(l, r);
        sm = N::rev(sm);
    }

    inline int pos() {
        if (p) {
            if (p->l == this) return -1;
            if (p->r == this) return 1;
        }
        return 0;
    }
    void rot() {
        NP q = p->p;
        int pps = p->pos();
        if (pps == -1) q->l = this;
        if (pps == 1) q->r = this;
        if (p->l == this) {
            p->l = r;
            if (r) r->p = p;
            r = p;
        } else {
            p->r = l;
            if (l) l->p = p;
            l = p;
        }
        p->p = this;
        p->update();
        update();
        p = q;
        if (q) q->update();
    }
    void all_push() {
        if (pos()) p->all_push();
        push();
    }
    void splay() {
        all_push();
        int ps;
        while ((ps = pos())) {
            int pps = p->pos();
            if (!pps) {
                rot();
            } else if (ps == pps) {
                p->rot();
                rot();
            } else {
                rot();
                rot();
            }
        }
    }
    void expose() {
        NP u = this, ur = nullptr;
        do {
            u->splay();
            u->r = ur;
            u->update();
            ur = u;
        } while ((u = u->p));
        splay();
    }
    // 親としてnpを接続する
    void link(NP np) {
        evert();
        np->expose();
        p = np;
    }
    // 親から自分を切り離す
    void cut() {
        expose();
        assert(l);
        l->p = nullptr;
        l = nullptr;
        update();
    }
    void evert() {
        expose();
        revdata();
    }

    NP lca(NP n) {
        n->expose();
        expose();
        NP t = n;
        while (n->p != nullptr) {
            if (!n->pos()) t = n->p;
            n = n->p;
        }
        return (this == n) ? t : nullptr;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/linkcuttree.hpp"
template <class N> struct LCNode {
    using NP = LCNode*;
    using D = typename N::D;
    NP p = nullptr, l = nullptr, r = nullptr;
    int sz = 1;
    bool rev = false;
    D v = N::e_d(), sm = N::e_d();

    void single_set(D x) {
        v = x;
        update();
    }
    void single_add(D x) {
        v = N::op_dd(v, x);
        update();
    }

    void init_node(D _v) {
        v = _v;
        sm = _v;
    }
    void update() {
        sz = 1;
        if (l) sz += l->sz;
        if (r) sz += r->sz;
        sm = l ? N::op_dd(l->sm, v) : v;
        if (r) sm = N::op_dd(sm, r->sm);
    }
    void push() {
        if (rev) {
            if (l) l->revdata();
            if (r) r->revdata();
            rev = false;
        }
    }
    void revdata() {
        rev ^= true;
        swap(l, r);
        sm = N::rev(sm);
    }

    inline int pos() {
        if (p) {
            if (p->l == this) return -1;
            if (p->r == this) return 1;
        }
        return 0;
    }
    void rot() {
        NP q = p->p;
        int pps = p->pos();
        if (pps == -1) q->l = this;
        if (pps == 1) q->r = this;
        if (p->l == this) {
            p->l = r;
            if (r) r->p = p;
            r = p;
        } else {
            p->r = l;
            if (l) l->p = p;
            l = p;
        }
        p->p = this;
        p->update();
        update();
        p = q;
        if (q) q->update();
    }
    void all_push() {
        if (pos()) p->all_push();
        push();
    }
    void splay() {
        all_push();
        int ps;
        while ((ps = pos())) {
            int pps = p->pos();
            if (!pps) {
                rot();
            } else if (ps == pps) {
                p->rot();
                rot();
            } else {
                rot();
                rot();
            }
        }
    }
    void expose() {
        NP u = this, ur = nullptr;
        do {
            u->splay();
            u->r = ur;
            u->update();
            ur = u;
        } while ((u = u->p));
        splay();
    }
    // 親としてnpを接続する
    void link(NP np) {
        evert();
        np->expose();
        p = np;
    }
    // 親から自分を切り離す
    void cut() {
        expose();
        assert(l);
        l->p = nullptr;
        l = nullptr;
        update();
    }
    void evert() {
        expose();
        revdata();
    }

    NP lca(NP n) {
        n->expose();
        expose();
        NP t = n;
        while (n->p != nullptr) {
            if (!n->pos()) t = n->p;
            n = n->p;
        }
        return (this == n) ? t : nullptr;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

