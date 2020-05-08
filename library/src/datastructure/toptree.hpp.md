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


# :warning: src/datastructure/toptree.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/toptree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct TTNode {
    using NP = TTNode*;

    bool rev = false;
    array<array<NP, 2>, 2> ch = {};  // tree, light-tree
    NP p = nullptr, lt = nullptr;

    struct D {
        ll cnt = 0, pd = 0, upd = 0, dwd = 0;
        // l is parent of r
        static D merge_h(const D& l, const D& r) {
            return {l.cnt + r.cnt, l.pd + r.pd, l.upd + r.upd + l.pd * r.cnt,
                    l.dwd + r.dwd + r.pd * l.cnt};
        }
        // l and r is parallel
        static D merge_w(const D& l, const D& r) {
            assert(!l.pd && !r.pd && !l.dwd && !r.dwd);
            return {l.cnt + r.cnt, 0, l.upd + r.upd, 0};
        }
        // add parent for r(subtrees)
        static D join(const D& l, const D& r) {
            assert(l.upd == l.dwd);
            return {l.cnt + r.cnt, l.pd, l.upd + r.upd + l.pd * r.cnt,
                    l.dwd + r.upd + l.pd * r.cnt};
        }
        D rev() { return D{cnt, pd, dwd, upd}; }
        D to_subs() { return D{cnt, 0, upd, 0}; }
    };
    D single = D(), sub = D(), subs = D();

    NP search(ll nw, ll f) {
        // search heavy
        assert(sub.cnt >= nw);
        push();
        if (ch[0][1] && ch[0][1]->sub.cnt >= nw) return ch[0][1]->search(nw, f);
        if (ch[0][1]) nw -= ch[0][1]->sub.cnt;
        if (single.cnt + (lt ? lt->subs.cnt : 0) >= nw) {
            if (!lt || lt->subs.cnt < f) return this;
            auto q = lt->search_light(f);
            if (!q) return this;
            return q;
        }
        nw -= single.cnt;
        if (lt) nw -= lt->subs.cnt;
        assert(ch[0][0]);
        return ch[0][0]->search(nw, f);
    }
    NP search_light(ll f) {
        assert(subs.cnt >= f);
        if (sub.cnt >= f) {
            return search(f, f);
        }
        push();
        if (ch[1][0] && ch[1][0]->subs.cnt >= f)
            return ch[1][0]->search_light(f);
        if (ch[1][1] && ch[1][1]->subs.cnt >= f)
            return ch[1][1]->search_light(f);
        expose();
        return nullptr;
    }
    void init_node(ll cnt, ll d) {
        single.cnt = cnt;
        single.pd = d;
        single.upd = single.dwd = cnt * d;
        update();
    }
    void update_subs() {
        subs = sub.to_subs();
        if (ch[1][0]) subs = D::merge_w(ch[1][0]->subs, subs);
        if (ch[1][1]) subs = D::merge_w(subs, ch[1][1]->subs);
    }
    void update() {
        assert(!rev);
        sub = single;
        if (lt) sub = D::join(single, lt->subs);
        if (ch[0][0]) sub = D::merge_h(ch[0][0]->sub, sub);
        if (ch[0][1]) sub = D::merge_h(sub, ch[0][1]->sub);
        update_subs();
    }
    void revdata() {
        rev ^= true;
        swap(ch[0][0], ch[0][1]);  // Important
        sub = sub.rev();
        update_subs();
    }
    void push() {
        if (rev) {
            if (ch[0][0]) ch[0][0]->revdata();
            if (ch[0][1]) ch[0][1]->revdata();
            rev = false;
        }
    }
    // optimize? : template<int ty>
    int pos(int ty) {
        if (p) {
            if (p->ch[ty][0] == this) return 0;
            if (p->ch[ty][1] == this) return 1;
        }
        return -1;
    }
    static void con(NP p, NP& cp, NP ch) {
        cp = ch;
        if (ch) ch->p = p;
    }
    void rot(int ty) {
        int ps = pos(ty);
        NP _p = p, q = p->p;
        if (ty == 0) {
            ch[1] = _p->ch[1];
            _p->ch[1].fill(nullptr);
            for (auto& x : ch[1])
                if (x) x->p = this;
        }
        con(_p, _p->ch[ty][ps], ch[ty][1 - ps]);
        con(this, ch[ty][1 - ps], _p);
        _p->update();
        update();
        p = q;
        if (!q) return;
        if (q->lt == _p) q->lt = this;
        for (auto& v : q->ch)
            for (auto& x : v)
                if (x == _p) x = this;
        q->update();
    }
    void splay(int ty) {
        int ps;
        while ((ps = pos(ty)) != -1) {
            int pps = p->pos(ty);
            if (pps == -1) {
                rot(ty);
            } else if (ps == pps) {
                p->rot(ty);
                rot(ty);
            } else {
                rot(ty);
                rot(ty);
            }
        }
    }
    void expose() {
        supush();
        splay(0);
        splay(1);
        if (NP z = ch[0][1]) {
            z->push();
            con(z, z->ch[1][1], lt);
            lt = z;
            ch[0][1] = nullptr;
            z->update();
            update();
        }
        NP u = p;
        while (u) {
            u->splay(0);
            u->splay(1);
            NP ur = u->lt;
            if (auto r = u->ch[0][1]) {
                // swap ur, r
                r->push();
                r->ch[1] = ur->ch[1];
                ur->ch[1].fill(nullptr);
                for (auto& x : r->ch[1])
                    if (x) x->p = r;
                r->update();
                u->lt = r;
            } else if (!ur->ch[1][0]) {
                // use ur->ch[1][1]
                con(u, u->lt, ur->ch[1][1]);
            } else {
                // use prev(ur) in light-tree
                NP q = ur->ch[1][0];
                con(u, u->lt, q);
                q->push();
                while (q->ch[1][1]) {
                    q = q->ch[1][1];
                    q->push();
                }
                q->splay(1);
                con(q, q->ch[1][1], ur->ch[1][1]);
                q->update();
            }
            ur->ch[1].fill(nullptr);
            ur->update();
            u->ch[0][1] = ur;
            u->update();
            u = u->p;
        }
        splay(0);
    }
    void supush() {
        if (p) p->supush();
        push();
    }
    void link(NP r) {
        evert();
        r->expose();
        assert(!r->ch[0][1]);
        con(r, r->ch[0][1], this);
        r->update();
    }
    void cut() {
        expose();
        assert(ch[0][0]);
        ch[0][0]->p = nullptr;
        ch[0][0] = nullptr;
        update();
    }
    void evert() {
        expose();
        revdata();
        expose();
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/toptree.hpp"
struct TTNode {
    using NP = TTNode*;

    bool rev = false;
    array<array<NP, 2>, 2> ch = {};  // tree, light-tree
    NP p = nullptr, lt = nullptr;

    struct D {
        ll cnt = 0, pd = 0, upd = 0, dwd = 0;
        // l is parent of r
        static D merge_h(const D& l, const D& r) {
            return {l.cnt + r.cnt, l.pd + r.pd, l.upd + r.upd + l.pd * r.cnt,
                    l.dwd + r.dwd + r.pd * l.cnt};
        }
        // l and r is parallel
        static D merge_w(const D& l, const D& r) {
            assert(!l.pd && !r.pd && !l.dwd && !r.dwd);
            return {l.cnt + r.cnt, 0, l.upd + r.upd, 0};
        }
        // add parent for r(subtrees)
        static D join(const D& l, const D& r) {
            assert(l.upd == l.dwd);
            return {l.cnt + r.cnt, l.pd, l.upd + r.upd + l.pd * r.cnt,
                    l.dwd + r.upd + l.pd * r.cnt};
        }
        D rev() { return D{cnt, pd, dwd, upd}; }
        D to_subs() { return D{cnt, 0, upd, 0}; }
    };
    D single = D(), sub = D(), subs = D();

    NP search(ll nw, ll f) {
        // search heavy
        assert(sub.cnt >= nw);
        push();
        if (ch[0][1] && ch[0][1]->sub.cnt >= nw) return ch[0][1]->search(nw, f);
        if (ch[0][1]) nw -= ch[0][1]->sub.cnt;
        if (single.cnt + (lt ? lt->subs.cnt : 0) >= nw) {
            if (!lt || lt->subs.cnt < f) return this;
            auto q = lt->search_light(f);
            if (!q) return this;
            return q;
        }
        nw -= single.cnt;
        if (lt) nw -= lt->subs.cnt;
        assert(ch[0][0]);
        return ch[0][0]->search(nw, f);
    }
    NP search_light(ll f) {
        assert(subs.cnt >= f);
        if (sub.cnt >= f) {
            return search(f, f);
        }
        push();
        if (ch[1][0] && ch[1][0]->subs.cnt >= f)
            return ch[1][0]->search_light(f);
        if (ch[1][1] && ch[1][1]->subs.cnt >= f)
            return ch[1][1]->search_light(f);
        expose();
        return nullptr;
    }
    void init_node(ll cnt, ll d) {
        single.cnt = cnt;
        single.pd = d;
        single.upd = single.dwd = cnt * d;
        update();
    }
    void update_subs() {
        subs = sub.to_subs();
        if (ch[1][0]) subs = D::merge_w(ch[1][0]->subs, subs);
        if (ch[1][1]) subs = D::merge_w(subs, ch[1][1]->subs);
    }
    void update() {
        assert(!rev);
        sub = single;
        if (lt) sub = D::join(single, lt->subs);
        if (ch[0][0]) sub = D::merge_h(ch[0][0]->sub, sub);
        if (ch[0][1]) sub = D::merge_h(sub, ch[0][1]->sub);
        update_subs();
    }
    void revdata() {
        rev ^= true;
        swap(ch[0][0], ch[0][1]);  // Important
        sub = sub.rev();
        update_subs();
    }
    void push() {
        if (rev) {
            if (ch[0][0]) ch[0][0]->revdata();
            if (ch[0][1]) ch[0][1]->revdata();
            rev = false;
        }
    }
    // optimize? : template<int ty>
    int pos(int ty) {
        if (p) {
            if (p->ch[ty][0] == this) return 0;
            if (p->ch[ty][1] == this) return 1;
        }
        return -1;
    }
    static void con(NP p, NP& cp, NP ch) {
        cp = ch;
        if (ch) ch->p = p;
    }
    void rot(int ty) {
        int ps = pos(ty);
        NP _p = p, q = p->p;
        if (ty == 0) {
            ch[1] = _p->ch[1];
            _p->ch[1].fill(nullptr);
            for (auto& x : ch[1])
                if (x) x->p = this;
        }
        con(_p, _p->ch[ty][ps], ch[ty][1 - ps]);
        con(this, ch[ty][1 - ps], _p);
        _p->update();
        update();
        p = q;
        if (!q) return;
        if (q->lt == _p) q->lt = this;
        for (auto& v : q->ch)
            for (auto& x : v)
                if (x == _p) x = this;
        q->update();
    }
    void splay(int ty) {
        int ps;
        while ((ps = pos(ty)) != -1) {
            int pps = p->pos(ty);
            if (pps == -1) {
                rot(ty);
            } else if (ps == pps) {
                p->rot(ty);
                rot(ty);
            } else {
                rot(ty);
                rot(ty);
            }
        }
    }
    void expose() {
        supush();
        splay(0);
        splay(1);
        if (NP z = ch[0][1]) {
            z->push();
            con(z, z->ch[1][1], lt);
            lt = z;
            ch[0][1] = nullptr;
            z->update();
            update();
        }
        NP u = p;
        while (u) {
            u->splay(0);
            u->splay(1);
            NP ur = u->lt;
            if (auto r = u->ch[0][1]) {
                // swap ur, r
                r->push();
                r->ch[1] = ur->ch[1];
                ur->ch[1].fill(nullptr);
                for (auto& x : r->ch[1])
                    if (x) x->p = r;
                r->update();
                u->lt = r;
            } else if (!ur->ch[1][0]) {
                // use ur->ch[1][1]
                con(u, u->lt, ur->ch[1][1]);
            } else {
                // use prev(ur) in light-tree
                NP q = ur->ch[1][0];
                con(u, u->lt, q);
                q->push();
                while (q->ch[1][1]) {
                    q = q->ch[1][1];
                    q->push();
                }
                q->splay(1);
                con(q, q->ch[1][1], ur->ch[1][1]);
                q->update();
            }
            ur->ch[1].fill(nullptr);
            ur->update();
            u->ch[0][1] = ur;
            u->update();
            u = u->p;
        }
        splay(0);
    }
    void supush() {
        if (p) p->supush();
        push();
    }
    void link(NP r) {
        evert();
        r->expose();
        assert(!r->ch[0][1]);
        con(r, r->ch[0][1], this);
        r->update();
    }
    void cut() {
        expose();
        assert(ch[0][0]);
        ch[0][0]->p = nullptr;
        ch[0][0] = nullptr;
        update();
    }
    void evert() {
        expose();
        revdata();
        expose();
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

