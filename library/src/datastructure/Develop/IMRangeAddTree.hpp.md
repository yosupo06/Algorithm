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


# :warning: src/datastructure/Develop/IMRangeAddTree.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#6ded3f220a7ec9530d5ce67338fd1fda">src/datastructure/Develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/Develop/IMRangeAddTree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * 永続化されている、範囲add、範囲sum、区間コピーが可能なRBST
 * 
 * GCは実装されていない
 *
 * Verify: ARC グラフではない
 */
struct STree {
    using D = ll;
    struct Node;
 
    using NP = const Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        D v, sm, lz;
        Node() : l(nullptr), r(nullptr), sz(0) {}
        Node(D vv) :l(last), r(last), sz(1) {
            v = vv;
            sm = 0;
            lz = 0;
        }
        static Node* make(NP x) {
            pool[pc] = *x;
            pc++;
            return &pool[pc-1];
        }
        static Node* make(D v) {
            pool[pc] = Node(v);
            pc++;
            return &pool[pc-1];
        }
        void push() {
            auto nl = make(l);
            auto nr = make(r);
            if (nl->sz) {
                nl->lzdata(lz);
            }
            if (nr->sz) {
                nr->lzdata(lz);
            }
            lz = 0;
            l = nl;
            r = nr;
        }
        /// pushはconstに関わらず呼んで良い
        void push() const {
            const_cast<Node*>(this)->push();
        }
        void update() {
            sz = 1+l->sz+r->sz;
            sm = v;
            if (l->sz) {
                sm += l->sm;
            }
            if (r->sz) {
                sm += r->sm;
            }
        }
        void lzdata(D x) {
            v += x;
            sm += sz*x;
            lz += x;
        }
    };
    NP n;

    //200,000,000とは200MBの意
    static const int PLS = 200000000 / sizeof(Node);
    static int pc;
    static Node pool[PLS];

    static void get(NP n, D d[]) {
        if (!n->sz) return;
        n->push();
        get(n->l, d);
        d[n->l->sz] = n->v;
        get(n->r, d + (n->l->sz+1));
    }
    void get(D d[]) {
        get(n, d);
    }

    void add(int l, int r, D x) {
        auto a = split(n, l);
        auto b = split(a.second, r-l);
        auto u = Node::make(b.first);
        u->lzdata(x);
        n = merge(merge(a.first, u), b.second);
    }
    D sum(int l, int r) {
        auto a = split(n, l);
        auto b = split(a.second, r-l);
        auto u = b.first;
        return u->sm;
    }

    static NP built(int l, int r, D d[]) {
        if (l == r) return last;
        int md = (l+r)/2;
        auto x = Node::make(d[md]);
        x->l = built(l, md, d);
        x->r = built(md+1, r, d);
        x->update();
        return x;
    }
 
    STree() : n(last) {}
    STree(NP n) : n(n) {}
    STree(int sz, D d[]) {
        n = built(0, sz, d);
    }

    int sz() {
        return n->sz;
    }     
    static uint xor128(){
        static uint x=123456789,y=362436069,z=521288629,w=88675123;
        uint t;
        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
    }
    static NP merge(NP l, NP r) {
        if (!l->sz) return r;
        if (!r->sz) return l;
        l->push(); r->push();
        auto nl = Node::make(l);
        auto nr = Node::make(r);
        if ((int)(xor128() % (nl->sz + nr->sz)) < nl->sz) {
            nl->r = merge(nl->r, nr);
            nl->update();
            return nl;
        } else {
            nr->l = merge(nl, nr->l);
            nr->update();
            return nr;
        }
    }
    STree merge(STree r) {
        return STree(merge(n, r.n));
    }
    static pair<NP, NP> split(NP x, int k) {
        if (!x->sz) return {last, last};
        x->push();
        auto nx = Node::make(x);
        if (k <= nx->l->sz) {
            auto y = split(nx->l, k);
            nx->l = y.second;
            nx->update();
            y.second = nx;
            return y;
        } else {
            auto y = split(x->r, k- x->l->sz -1);
            nx->r = y.first;
            nx->update();
            y.first = nx;
            return y;
        }
    }
    pair<STree, STree> split(int k) {
        auto u = split(n, k);
        return pair<STree, STree>(STree(u.first), STree(u.second));
    }
};
STree::Node STree::last_d = STree::Node();
STree::NP STree::last = &last_d;
STree::Node STree::pool[STree::PLS];
int STree::pc = 0;
 
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/Develop/IMRangeAddTree.hpp"
/**
 * 永続化されている、範囲add、範囲sum、区間コピーが可能なRBST
 * 
 * GCは実装されていない
 *
 * Verify: ARC グラフではない
 */
struct STree {
    using D = ll;
    struct Node;
 
    using NP = const Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        D v, sm, lz;
        Node() : l(nullptr), r(nullptr), sz(0) {}
        Node(D vv) :l(last), r(last), sz(1) {
            v = vv;
            sm = 0;
            lz = 0;
        }
        static Node* make(NP x) {
            pool[pc] = *x;
            pc++;
            return &pool[pc-1];
        }
        static Node* make(D v) {
            pool[pc] = Node(v);
            pc++;
            return &pool[pc-1];
        }
        void push() {
            auto nl = make(l);
            auto nr = make(r);
            if (nl->sz) {
                nl->lzdata(lz);
            }
            if (nr->sz) {
                nr->lzdata(lz);
            }
            lz = 0;
            l = nl;
            r = nr;
        }
        /// pushはconstに関わらず呼んで良い
        void push() const {
            const_cast<Node*>(this)->push();
        }
        void update() {
            sz = 1+l->sz+r->sz;
            sm = v;
            if (l->sz) {
                sm += l->sm;
            }
            if (r->sz) {
                sm += r->sm;
            }
        }
        void lzdata(D x) {
            v += x;
            sm += sz*x;
            lz += x;
        }
    };
    NP n;

    //200,000,000とは200MBの意
    static const int PLS = 200000000 / sizeof(Node);
    static int pc;
    static Node pool[PLS];

    static void get(NP n, D d[]) {
        if (!n->sz) return;
        n->push();
        get(n->l, d);
        d[n->l->sz] = n->v;
        get(n->r, d + (n->l->sz+1));
    }
    void get(D d[]) {
        get(n, d);
    }

    void add(int l, int r, D x) {
        auto a = split(n, l);
        auto b = split(a.second, r-l);
        auto u = Node::make(b.first);
        u->lzdata(x);
        n = merge(merge(a.first, u), b.second);
    }
    D sum(int l, int r) {
        auto a = split(n, l);
        auto b = split(a.second, r-l);
        auto u = b.first;
        return u->sm;
    }

    static NP built(int l, int r, D d[]) {
        if (l == r) return last;
        int md = (l+r)/2;
        auto x = Node::make(d[md]);
        x->l = built(l, md, d);
        x->r = built(md+1, r, d);
        x->update();
        return x;
    }
 
    STree() : n(last) {}
    STree(NP n) : n(n) {}
    STree(int sz, D d[]) {
        n = built(0, sz, d);
    }

    int sz() {
        return n->sz;
    }     
    static uint xor128(){
        static uint x=123456789,y=362436069,z=521288629,w=88675123;
        uint t;
        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
    }
    static NP merge(NP l, NP r) {
        if (!l->sz) return r;
        if (!r->sz) return l;
        l->push(); r->push();
        auto nl = Node::make(l);
        auto nr = Node::make(r);
        if ((int)(xor128() % (nl->sz + nr->sz)) < nl->sz) {
            nl->r = merge(nl->r, nr);
            nl->update();
            return nl;
        } else {
            nr->l = merge(nl, nr->l);
            nr->update();
            return nr;
        }
    }
    STree merge(STree r) {
        return STree(merge(n, r.n));
    }
    static pair<NP, NP> split(NP x, int k) {
        if (!x->sz) return {last, last};
        x->push();
        auto nx = Node::make(x);
        if (k <= nx->l->sz) {
            auto y = split(nx->l, k);
            nx->l = y.second;
            nx->update();
            y.second = nx;
            return y;
        } else {
            auto y = split(x->r, k- x->l->sz -1);
            nx->r = y.first;
            nx->update();
            y.first = nx;
            return y;
        }
    }
    pair<STree, STree> split(int k) {
        auto u = split(n, k);
        return pair<STree, STree>(STree(u.first), STree(u.second));
    }
};
STree::Node STree::last_d = STree::Node();
STree::NP STree::last = &last_d;
STree::Node STree::pool[STree::PLS];
int STree::pc = 0;
 

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

