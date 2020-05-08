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


# :warning: src/datastructure/Develop/SplayTMSet.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#6ded3f220a7ec9530d5ce67338fd1fda">src/datastructure/Develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/Develop/SplayTMSet.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Tree {
    using D = int;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last, la;
    struct Node {
        NP p, l, r;
        int sz;
        D v;
        Node(D v) :p(nullptr), l(last), r(last), sz(1), v(v) {}
        Node(NP p, NP l, NP r, int sz = 0) : p(p), l(l), r(r), sz(sz) {}
        bool is_root() {
            return p == nullptr;
        }
        void rotr() {
            NP q = p, qq = q->p;
            q->l = r; r->p = q;
            r = q; q->p = this;
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void rotl() {
            NP q = p, qq = q->p;
            q->r = l; l->p = q;
            l = q; q->p = this;
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void splay() {
            assert(this != last);
            while (!is_root()) {
                NP q = p;
                if (q->is_root()) {
                    if (q->l == this) rotr();
                    else rotl();
                    continue;
                }
                NP r = q->p;
                if (r->l == q) {
                    if (q->l == this) {q->rotr(); rotr();}
                    else {rotl(); rotr();}
                } else {
                    if (q->r == this) {q->rotl(); rotl();}
                    else {rotr(); rotl();}
                }
            }
        }
        void push() {
 
        }
        NP update() {
            if (this == last) return this;
            sz = 1+l->sz+r->sz;
            return this;
        }
    } *n;
    static NP merge(NP l, NP r) {
        if (l == last) {
            return r;
        }
        while (l->r != last) {
            l = l->r;
        }
        l->splay();
        l->r = r;
        r->p = l;
        return l->update();
    }
    static pair<NP, NP> split(NP x, int k) {
        assert(0 <= k && k <= x->sz);
        if (k == x->sz) {
            return {x, last};
        }
        while (k != x->l->sz) {
            if (k < x->l->sz) {
                x = x->l;
            } else {
                k -= x->l->sz+1;
                x = x->r;
            }
        }

        x->splay();
        NP l = x->l;
        l->p = NULL;
        x->l = last;
        return {l, x->update()};
    }
 
    Tree() : n(last) {}
    Tree(NP n) : n(n) {}
    int sz() {
        return n->sz;
    }
    void insert(int k, D v) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(v)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, split(u.second, 1).second);
    }
    int getc(int k) {
        auto u = split(n, k);
        int res = u.second->v;
        n = merge(u.first, u.second);
        return res;
    }
};
Tree::Node Tree::last_d = Tree::Node(NULL, NULL, NULL, 0);
Tree::NP Tree::last = &last_d;
Tree::NP Tree::la;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/Develop/SplayTMSet.hpp"
struct Tree {
    using D = int;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last, la;
    struct Node {
        NP p, l, r;
        int sz;
        D v;
        Node(D v) :p(nullptr), l(last), r(last), sz(1), v(v) {}
        Node(NP p, NP l, NP r, int sz = 0) : p(p), l(l), r(r), sz(sz) {}
        bool is_root() {
            return p == nullptr;
        }
        void rotr() {
            NP q = p, qq = q->p;
            q->l = r; r->p = q;
            r = q; q->p = this;
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void rotl() {
            NP q = p, qq = q->p;
            q->r = l; l->p = q;
            l = q; q->p = this;
            q->update(); update();
            if ((p = qq)) {
                if (qq->l == q) qq->l = this;
                if (qq->r == q) qq->r = this;
                qq->update();
            }
        }
        void splay() {
            assert(this != last);
            while (!is_root()) {
                NP q = p;
                if (q->is_root()) {
                    if (q->l == this) rotr();
                    else rotl();
                    continue;
                }
                NP r = q->p;
                if (r->l == q) {
                    if (q->l == this) {q->rotr(); rotr();}
                    else {rotl(); rotr();}
                } else {
                    if (q->r == this) {q->rotl(); rotl();}
                    else {rotr(); rotl();}
                }
            }
        }
        void push() {
 
        }
        NP update() {
            if (this == last) return this;
            sz = 1+l->sz+r->sz;
            return this;
        }
    } *n;
    static NP merge(NP l, NP r) {
        if (l == last) {
            return r;
        }
        while (l->r != last) {
            l = l->r;
        }
        l->splay();
        l->r = r;
        r->p = l;
        return l->update();
    }
    static pair<NP, NP> split(NP x, int k) {
        assert(0 <= k && k <= x->sz);
        if (k == x->sz) {
            return {x, last};
        }
        while (k != x->l->sz) {
            if (k < x->l->sz) {
                x = x->l;
            } else {
                k -= x->l->sz+1;
                x = x->r;
            }
        }

        x->splay();
        NP l = x->l;
        l->p = NULL;
        x->l = last;
        return {l, x->update()};
    }
 
    Tree() : n(last) {}
    Tree(NP n) : n(n) {}
    int sz() {
        return n->sz;
    }
    void insert(int k, D v) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(v)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, split(u.second, 1).second);
    }
    int getc(int k) {
        auto u = split(n, k);
        int res = u.second->v;
        n = merge(u.first, u.second);
        return res;
    }
};
Tree::Node Tree::last_d = Tree::Node(NULL, NULL, NULL, 0);
Tree::NP Tree::last = &last_d;
Tree::NP Tree::la;

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

