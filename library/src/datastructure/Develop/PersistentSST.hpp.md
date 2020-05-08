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


# :warning: src/datastructure/Develop/PersistentSST.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#6ded3f220a7ec9530d5ce67338fd1fda">src/datastructure/Develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/Develop/PersistentSST.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Node {
    using NP = const Node*;

    int ma, lz;

    /*
     init_node, update, push
    */
    void init_node() {
        ma = lz = 0;
    }
    void update() {
        ma = max(l->ma, r->ma);
    }
    void push() {
        if (!lz) continue;
        auto nl = make(l);
        auto nr = make(r);
        if (lz) {
            nl->lzdata(lz);
            nr->lzdata(lz);
            lz = 0;
        }
        l = nl;
        r = nr;
    }
    /// pushはconstに関わらず呼んで良い
    void push() const {
        const_cast<Node*>(this)->push();
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }

    NP add(int a, int b, int x) const {
        if (b <= 0 or sz <= a) return this;
        if (a <= 0 and sz <= b) {
            auto n = make(this);
            n->lzdata(x);
            return n;
        }
        push();
        auto n = make(this);
        auto n->l = l->add(a, b, x);
        auto n->r = r->add(a - sz/2, b - sz/2, x);
        n->update();
        return n;
    }
    int get(int a, int b) const {
        if (b <= 0 or sz <= a) return -1;
        if (a <= 0 and sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));
    }

    NP l, r;
    int sz;
    Node() {}
    Node(int sz) : sz(sz) {
        init_node();
        if (sz == 1) return;
        l = new Node(sz/2);
        r = new Node(sz - sz/2);
        update();
    }
    static Node* make(NP x) {
        auto n = new Node();
        *n = *x;
        return n;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/Develop/PersistentSST.hpp"
struct Node {
    using NP = const Node*;

    int ma, lz;

    /*
     init_node, update, push
    */
    void init_node() {
        ma = lz = 0;
    }
    void update() {
        ma = max(l->ma, r->ma);
    }
    void push() {
        if (!lz) continue;
        auto nl = make(l);
        auto nr = make(r);
        if (lz) {
            nl->lzdata(lz);
            nr->lzdata(lz);
            lz = 0;
        }
        l = nl;
        r = nr;
    }
    /// pushはconstに関わらず呼んで良い
    void push() const {
        const_cast<Node*>(this)->push();
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }

    NP add(int a, int b, int x) const {
        if (b <= 0 or sz <= a) return this;
        if (a <= 0 and sz <= b) {
            auto n = make(this);
            n->lzdata(x);
            return n;
        }
        push();
        auto n = make(this);
        auto n->l = l->add(a, b, x);
        auto n->r = r->add(a - sz/2, b - sz/2, x);
        n->update();
        return n;
    }
    int get(int a, int b) const {
        if (b <= 0 or sz <= a) return -1;
        if (a <= 0 and sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));
    }

    NP l, r;
    int sz;
    Node() {}
    Node(int sz) : sz(sz) {
        init_node();
        if (sz == 1) return;
        l = new Node(sz/2);
        r = new Node(sz - sz/2);
        update();
    }
    static Node* make(NP x) {
        auto n = new Node();
        *n = *x;
        return n;
    }
};

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

