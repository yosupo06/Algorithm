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
<script type="text/javascript" src="../../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../../assets/css/copy-button.css" />


# :warning: src/datastructure/Develop/AADynamic.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#6ded3f220a7ec9530d5ce67338fd1fda">src/datastructure/Develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/Develop/AADynamic.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct AA {
    using NP = AA*;

    int ma, lz;
    void init_node() {
        ma = lz = 0;
    }
    void update() {
        assert(!lz);
        sz = l->sz + r->sz;
        ma = max(l->ma, r->ma);
    }
    void push() {
        assert(l && r);
        assert(l->sz && r->sz);
        if (lz) {
            l->lzdata(lz);
            r->lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }
    void add(int a, int b, int x) {
        if (b <= 0 || sz <= a) return;
        if (a <= 0 && sz <= b) {
            lzdata(x);
            return;
        }
        push();
        l->add(a, b, x);
        r->add(a - l->sz, b - l->sz, x);
        update();
    }
    int get(int a, int b) {
        if (b <= 0 || sz <= a) return -1;
        if (a <= 0 && sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a - l->sz, b - l->sz));
    }

    NP l, r;
    int sz; int lv;
    bool isL; // is last
    AA(int sz) : l(nullptr), r(nullptr), sz(sz), lv(0), isL(true) {
        init_node();
    }    
    static NP make_child(NP n, int k) {
        n->l = new AA(k); n->r = new AA(n->sz - k);
        n->lv = 1;
        n->isL = false;
        n->push();
        return n;
    }
    static NP skew(NP n) {
        if (n->l == nullptr || n->lv != n->l->lv) return n;
        NP L = n->l;
        n->l = L->r;
        n->update();
        L->r = n;
        L->update();
        return L;
    }
    static NP pull(NP n) {
        if (n->r == nullptr || n->lv != n->r->lv) return n;
        if (n->r->r == nullptr || n->lv != n->r->r->lv) return n;
        NP R = n->r;
        n->r = R->l;
        n->update();
        R->l = n;
        R->lv++;
        R->update();
        return R;
    }
    static NP inscut(NP n, int k) {
        if (k == 0 || k == n->sz) return n;
        if (n->isL) {
            return make_child(n, k);
        }
        n->push();
        if (k <= n->l->sz) {
            n->l = inscut(n->l, k);
            n->update();
            return pull(skew(n));
        } else {
            n->r = inscut(n->r, k - n->l->sz);
            n->update();
            return pull(skew(n));
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/Develop/AADynamic.hpp"
struct AA {
    using NP = AA*;

    int ma, lz;
    void init_node() {
        ma = lz = 0;
    }
    void update() {
        assert(!lz);
        sz = l->sz + r->sz;
        ma = max(l->ma, r->ma);
    }
    void push() {
        assert(l && r);
        assert(l->sz && r->sz);
        if (lz) {
            l->lzdata(lz);
            r->lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }
    void add(int a, int b, int x) {
        if (b <= 0 || sz <= a) return;
        if (a <= 0 && sz <= b) {
            lzdata(x);
            return;
        }
        push();
        l->add(a, b, x);
        r->add(a - l->sz, b - l->sz, x);
        update();
    }
    int get(int a, int b) {
        if (b <= 0 || sz <= a) return -1;
        if (a <= 0 && sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a - l->sz, b - l->sz));
    }

    NP l, r;
    int sz; int lv;
    bool isL; // is last
    AA(int sz) : l(nullptr), r(nullptr), sz(sz), lv(0), isL(true) {
        init_node();
    }    
    static NP make_child(NP n, int k) {
        n->l = new AA(k); n->r = new AA(n->sz - k);
        n->lv = 1;
        n->isL = false;
        n->push();
        return n;
    }
    static NP skew(NP n) {
        if (n->l == nullptr || n->lv != n->l->lv) return n;
        NP L = n->l;
        n->l = L->r;
        n->update();
        L->r = n;
        L->update();
        return L;
    }
    static NP pull(NP n) {
        if (n->r == nullptr || n->lv != n->r->lv) return n;
        if (n->r->r == nullptr || n->lv != n->r->r->lv) return n;
        NP R = n->r;
        n->r = R->l;
        n->update();
        R->l = n;
        R->lv++;
        R->update();
        return R;
    }
    static NP inscut(NP n, int k) {
        if (k == 0 || k == n->sz) return n;
        if (n->isL) {
            return make_child(n, k);
        }
        n->push();
        if (k <= n->l->sz) {
            n->l = inscut(n->l, k);
            n->update();
            return pull(skew(n));
        } else {
            n->r = inscut(n->r, k - n->l->sz);
            n->update();
            return pull(skew(n));
        }
    }
};

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

