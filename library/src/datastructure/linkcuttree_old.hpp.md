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


# :warning: src/datastructure/linkcuttree_old.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/linkcuttree_old.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct LCNode {
    using NP = LCNode*;
    static NP last;
    ll d, dsm, ma;
    ll lz;
    NP init_last() {
        sz = 0; // Important
        lz = 0; // Important
        d = dsm = ma = 0;
        return this;
    }
    void init_node(int d) {
        sz = 1; rev = false; // Important
        lz = 0; // Important
        this->d = dsm = ma = d;
    }
    void update() {
        sz = 1 + l->sz + r->sz; // Important
        dsm = d + l->dsm + r->dsm;
        ma = max(d, max(l->ma, r->ma));
    }
    void push() {
        assert(this != last);
        if (rev) { // Important
            if (l != last) {
                l->revdata();
            }
            if (r != last) {
                r->revdata();
            }
            rev = false;
        }
        if (lz) {
            if (l != last) {
                l->lzdata(lz);
            }
            if (r != last) {
                r->lzdata(lz);
            }
            lz = 0;
        }
    }
    void revdata() {
        rev ^= true; swap(l, r); // Important
    }
    void lzdata(ll x) {
        d += x;
        dsm += x;
        ma += x;
        lz += x;
    }
    
    NP p, l, r;
    int sz;
    bool rev;
    LCNode() : p(nullptr), l(last), r(last) {}
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
        p->update(); update();
        p = q;
        if (q) q->update();
    }
    void splay() {
        supush();
        int ps;
        while ((ps = pos())) {
            int pps = p->pos();
            if (!pps) {
                rot();
            } else if (ps == pps) {
                p->rot(); rot();
            } else {
                rot(); rot();
            }
        }
    }
    void expose() {
        assert(this != last);
        NP u = this, ur = last;
        do {
            u->splay();
            u->r = ur;
            u->update();
            ur = u;
        } while ((u = u->p));
        splay();
    }
    void supush() {
        if (pos()) p->supush();
        push();
    }
    void link(NP r) {
        evert(); r->expose();
        p = r;
    }
    void cut() {
        expose();
        l->p = NULL;
        l = last;
        update();
    }
    void evert() {
        expose(); revdata();
    }

    //tree func
    NP parent() {
        expose();
        NP u = this->l;
        if (u == last) return last;
        u->push();
        while (u->r != last) {
            u = u->r;
            u->push();
        }
        u->expose();
        return u;
    }

    NP root() {
        expose();
        NP u = this;
        while (u->l != last) {
            u = u->l;
            u->push();
        }
        u->expose();
        return u;
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
LCNode::NP LCNode::last = (new LCNode())->init_last();

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/linkcuttree_old.hpp"
struct LCNode {
    using NP = LCNode*;
    static NP last;
    ll d, dsm, ma;
    ll lz;
    NP init_last() {
        sz = 0; // Important
        lz = 0; // Important
        d = dsm = ma = 0;
        return this;
    }
    void init_node(int d) {
        sz = 1; rev = false; // Important
        lz = 0; // Important
        this->d = dsm = ma = d;
    }
    void update() {
        sz = 1 + l->sz + r->sz; // Important
        dsm = d + l->dsm + r->dsm;
        ma = max(d, max(l->ma, r->ma));
    }
    void push() {
        assert(this != last);
        if (rev) { // Important
            if (l != last) {
                l->revdata();
            }
            if (r != last) {
                r->revdata();
            }
            rev = false;
        }
        if (lz) {
            if (l != last) {
                l->lzdata(lz);
            }
            if (r != last) {
                r->lzdata(lz);
            }
            lz = 0;
        }
    }
    void revdata() {
        rev ^= true; swap(l, r); // Important
    }
    void lzdata(ll x) {
        d += x;
        dsm += x;
        ma += x;
        lz += x;
    }
    
    NP p, l, r;
    int sz;
    bool rev;
    LCNode() : p(nullptr), l(last), r(last) {}
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
        p->update(); update();
        p = q;
        if (q) q->update();
    }
    void splay() {
        supush();
        int ps;
        while ((ps = pos())) {
            int pps = p->pos();
            if (!pps) {
                rot();
            } else if (ps == pps) {
                p->rot(); rot();
            } else {
                rot(); rot();
            }
        }
    }
    void expose() {
        assert(this != last);
        NP u = this, ur = last;
        do {
            u->splay();
            u->r = ur;
            u->update();
            ur = u;
        } while ((u = u->p));
        splay();
    }
    void supush() {
        if (pos()) p->supush();
        push();
    }
    void link(NP r) {
        evert(); r->expose();
        p = r;
    }
    void cut() {
        expose();
        l->p = NULL;
        l = last;
        update();
    }
    void evert() {
        expose(); revdata();
    }

    //tree func
    NP parent() {
        expose();
        NP u = this->l;
        if (u == last) return last;
        u->push();
        while (u->r != last) {
            u = u->r;
            u->push();
        }
        u->expose();
        return u;
    }

    NP root() {
        expose();
        NP u = this;
        while (u->l != last) {
            u = u->l;
            u->push();
        }
        u->expose();
        return u;
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
LCNode::NP LCNode::last = (new LCNode())->init_last();

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

