---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/toptree.hpp\"\nstruct TTNode {\n    using\
    \ NP = TTNode*;\n\n    bool rev = false;\n    array<array<NP, 2>, 2> ch = {};\
    \  // tree, light-tree\n    NP p = nullptr, lt = nullptr;\n\n    struct D {\n\
    \        ll cnt = 0, pd = 0, upd = 0, dwd = 0;\n        // l is parent of r\n\
    \        static D merge_h(const D& l, const D& r) {\n            return {l.cnt\
    \ + r.cnt, l.pd + r.pd, l.upd + r.upd + l.pd * r.cnt,\n                    l.dwd\
    \ + r.dwd + r.pd * l.cnt};\n        }\n        // l and r is parallel\n      \
    \  static D merge_w(const D& l, const D& r) {\n            assert(!l.pd && !r.pd\
    \ && !l.dwd && !r.dwd);\n            return {l.cnt + r.cnt, 0, l.upd + r.upd,\
    \ 0};\n        }\n        // add parent for r(subtrees)\n        static D join(const\
    \ D& l, const D& r) {\n            assert(l.upd == l.dwd);\n            return\
    \ {l.cnt + r.cnt, l.pd, l.upd + r.upd + l.pd * r.cnt,\n                    l.dwd\
    \ + r.upd + l.pd * r.cnt};\n        }\n        D rev() { return D{cnt, pd, dwd,\
    \ upd}; }\n        D to_subs() { return D{cnt, 0, upd, 0}; }\n    };\n    D single\
    \ = D(), sub = D(), subs = D();\n\n    NP search(ll nw, ll f) {\n        // search\
    \ heavy\n        assert(sub.cnt >= nw);\n        push();\n        if (ch[0][1]\
    \ && ch[0][1]->sub.cnt >= nw) return ch[0][1]->search(nw, f);\n        if (ch[0][1])\
    \ nw -= ch[0][1]->sub.cnt;\n        if (single.cnt + (lt ? lt->subs.cnt : 0) >=\
    \ nw) {\n            if (!lt || lt->subs.cnt < f) return this;\n            auto\
    \ q = lt->search_light(f);\n            if (!q) return this;\n            return\
    \ q;\n        }\n        nw -= single.cnt;\n        if (lt) nw -= lt->subs.cnt;\n\
    \        assert(ch[0][0]);\n        return ch[0][0]->search(nw, f);\n    }\n \
    \   NP search_light(ll f) {\n        assert(subs.cnt >= f);\n        if (sub.cnt\
    \ >= f) {\n            return search(f, f);\n        }\n        push();\n    \
    \    if (ch[1][0] && ch[1][0]->subs.cnt >= f)\n            return ch[1][0]->search_light(f);\n\
    \        if (ch[1][1] && ch[1][1]->subs.cnt >= f)\n            return ch[1][1]->search_light(f);\n\
    \        expose();\n        return nullptr;\n    }\n    void init_node(ll cnt,\
    \ ll d) {\n        single.cnt = cnt;\n        single.pd = d;\n        single.upd\
    \ = single.dwd = cnt * d;\n        update();\n    }\n    void update_subs() {\n\
    \        subs = sub.to_subs();\n        if (ch[1][0]) subs = D::merge_w(ch[1][0]->subs,\
    \ subs);\n        if (ch[1][1]) subs = D::merge_w(subs, ch[1][1]->subs);\n   \
    \ }\n    void update() {\n        assert(!rev);\n        sub = single;\n     \
    \   if (lt) sub = D::join(single, lt->subs);\n        if (ch[0][0]) sub = D::merge_h(ch[0][0]->sub,\
    \ sub);\n        if (ch[0][1]) sub = D::merge_h(sub, ch[0][1]->sub);\n       \
    \ update_subs();\n    }\n    void revdata() {\n        rev ^= true;\n        swap(ch[0][0],\
    \ ch[0][1]);  // Important\n        sub = sub.rev();\n        update_subs();\n\
    \    }\n    void push() {\n        if (rev) {\n            if (ch[0][0]) ch[0][0]->revdata();\n\
    \            if (ch[0][1]) ch[0][1]->revdata();\n            rev = false;\n  \
    \      }\n    }\n    // optimize? : template<int ty>\n    int pos(int ty) {\n\
    \        if (p) {\n            if (p->ch[ty][0] == this) return 0;\n         \
    \   if (p->ch[ty][1] == this) return 1;\n        }\n        return -1;\n    }\n\
    \    static void con(NP p, NP& cp, NP ch) {\n        cp = ch;\n        if (ch)\
    \ ch->p = p;\n    }\n    void rot(int ty) {\n        int ps = pos(ty);\n     \
    \   NP _p = p, q = p->p;\n        if (ty == 0) {\n            ch[1] = _p->ch[1];\n\
    \            _p->ch[1].fill(nullptr);\n            for (auto& x : ch[1])\n   \
    \             if (x) x->p = this;\n        }\n        con(_p, _p->ch[ty][ps],\
    \ ch[ty][1 - ps]);\n        con(this, ch[ty][1 - ps], _p);\n        _p->update();\n\
    \        update();\n        p = q;\n        if (!q) return;\n        if (q->lt\
    \ == _p) q->lt = this;\n        for (auto& v : q->ch)\n            for (auto&\
    \ x : v)\n                if (x == _p) x = this;\n        q->update();\n    }\n\
    \    void splay(int ty) {\n        int ps;\n        while ((ps = pos(ty)) != -1)\
    \ {\n            int pps = p->pos(ty);\n            if (pps == -1) {\n       \
    \         rot(ty);\n            } else if (ps == pps) {\n                p->rot(ty);\n\
    \                rot(ty);\n            } else {\n                rot(ty);\n  \
    \              rot(ty);\n            }\n        }\n    }\n    void expose() {\n\
    \        supush();\n        splay(0);\n        splay(1);\n        if (NP z = ch[0][1])\
    \ {\n            z->push();\n            con(z, z->ch[1][1], lt);\n          \
    \  lt = z;\n            ch[0][1] = nullptr;\n            z->update();\n      \
    \      update();\n        }\n        NP u = p;\n        while (u) {\n        \
    \    u->splay(0);\n            u->splay(1);\n            NP ur = u->lt;\n    \
    \        if (auto r = u->ch[0][1]) {\n                // swap ur, r\n        \
    \        r->push();\n                r->ch[1] = ur->ch[1];\n                ur->ch[1].fill(nullptr);\n\
    \                for (auto& x : r->ch[1])\n                    if (x) x->p = r;\n\
    \                r->update();\n                u->lt = r;\n            } else\
    \ if (!ur->ch[1][0]) {\n                // use ur->ch[1][1]\n                con(u,\
    \ u->lt, ur->ch[1][1]);\n            } else {\n                // use prev(ur)\
    \ in light-tree\n                NP q = ur->ch[1][0];\n                con(u,\
    \ u->lt, q);\n                q->push();\n                while (q->ch[1][1])\
    \ {\n                    q = q->ch[1][1];\n                    q->push();\n  \
    \              }\n                q->splay(1);\n                con(q, q->ch[1][1],\
    \ ur->ch[1][1]);\n                q->update();\n            }\n            ur->ch[1].fill(nullptr);\n\
    \            ur->update();\n            u->ch[0][1] = ur;\n            u->update();\n\
    \            u = u->p;\n        }\n        splay(0);\n    }\n    void supush()\
    \ {\n        if (p) p->supush();\n        push();\n    }\n    void link(NP r)\
    \ {\n        evert();\n        r->expose();\n        assert(!r->ch[0][1]);\n \
    \       con(r, r->ch[0][1], this);\n        r->update();\n    }\n    void cut()\
    \ {\n        expose();\n        assert(ch[0][0]);\n        ch[0][0]->p = nullptr;\n\
    \        ch[0][0] = nullptr;\n        update();\n    }\n    void evert() {\n \
    \       expose();\n        revdata();\n        expose();\n    }\n};\n"
  code: "struct TTNode {\n    using NP = TTNode*;\n\n    bool rev = false;\n    array<array<NP,\
    \ 2>, 2> ch = {};  // tree, light-tree\n    NP p = nullptr, lt = nullptr;\n\n\
    \    struct D {\n        ll cnt = 0, pd = 0, upd = 0, dwd = 0;\n        // l is\
    \ parent of r\n        static D merge_h(const D& l, const D& r) {\n          \
    \  return {l.cnt + r.cnt, l.pd + r.pd, l.upd + r.upd + l.pd * r.cnt,\n       \
    \             l.dwd + r.dwd + r.pd * l.cnt};\n        }\n        // l and r is\
    \ parallel\n        static D merge_w(const D& l, const D& r) {\n            assert(!l.pd\
    \ && !r.pd && !l.dwd && !r.dwd);\n            return {l.cnt + r.cnt, 0, l.upd\
    \ + r.upd, 0};\n        }\n        // add parent for r(subtrees)\n        static\
    \ D join(const D& l, const D& r) {\n            assert(l.upd == l.dwd);\n    \
    \        return {l.cnt + r.cnt, l.pd, l.upd + r.upd + l.pd * r.cnt,\n        \
    \            l.dwd + r.upd + l.pd * r.cnt};\n        }\n        D rev() { return\
    \ D{cnt, pd, dwd, upd}; }\n        D to_subs() { return D{cnt, 0, upd, 0}; }\n\
    \    };\n    D single = D(), sub = D(), subs = D();\n\n    NP search(ll nw, ll\
    \ f) {\n        // search heavy\n        assert(sub.cnt >= nw);\n        push();\n\
    \        if (ch[0][1] && ch[0][1]->sub.cnt >= nw) return ch[0][1]->search(nw,\
    \ f);\n        if (ch[0][1]) nw -= ch[0][1]->sub.cnt;\n        if (single.cnt\
    \ + (lt ? lt->subs.cnt : 0) >= nw) {\n            if (!lt || lt->subs.cnt < f)\
    \ return this;\n            auto q = lt->search_light(f);\n            if (!q)\
    \ return this;\n            return q;\n        }\n        nw -= single.cnt;\n\
    \        if (lt) nw -= lt->subs.cnt;\n        assert(ch[0][0]);\n        return\
    \ ch[0][0]->search(nw, f);\n    }\n    NP search_light(ll f) {\n        assert(subs.cnt\
    \ >= f);\n        if (sub.cnt >= f) {\n            return search(f, f);\n    \
    \    }\n        push();\n        if (ch[1][0] && ch[1][0]->subs.cnt >= f)\n  \
    \          return ch[1][0]->search_light(f);\n        if (ch[1][1] && ch[1][1]->subs.cnt\
    \ >= f)\n            return ch[1][1]->search_light(f);\n        expose();\n  \
    \      return nullptr;\n    }\n    void init_node(ll cnt, ll d) {\n        single.cnt\
    \ = cnt;\n        single.pd = d;\n        single.upd = single.dwd = cnt * d;\n\
    \        update();\n    }\n    void update_subs() {\n        subs = sub.to_subs();\n\
    \        if (ch[1][0]) subs = D::merge_w(ch[1][0]->subs, subs);\n        if (ch[1][1])\
    \ subs = D::merge_w(subs, ch[1][1]->subs);\n    }\n    void update() {\n     \
    \   assert(!rev);\n        sub = single;\n        if (lt) sub = D::join(single,\
    \ lt->subs);\n        if (ch[0][0]) sub = D::merge_h(ch[0][0]->sub, sub);\n  \
    \      if (ch[0][1]) sub = D::merge_h(sub, ch[0][1]->sub);\n        update_subs();\n\
    \    }\n    void revdata() {\n        rev ^= true;\n        swap(ch[0][0], ch[0][1]);\
    \  // Important\n        sub = sub.rev();\n        update_subs();\n    }\n   \
    \ void push() {\n        if (rev) {\n            if (ch[0][0]) ch[0][0]->revdata();\n\
    \            if (ch[0][1]) ch[0][1]->revdata();\n            rev = false;\n  \
    \      }\n    }\n    // optimize? : template<int ty>\n    int pos(int ty) {\n\
    \        if (p) {\n            if (p->ch[ty][0] == this) return 0;\n         \
    \   if (p->ch[ty][1] == this) return 1;\n        }\n        return -1;\n    }\n\
    \    static void con(NP p, NP& cp, NP ch) {\n        cp = ch;\n        if (ch)\
    \ ch->p = p;\n    }\n    void rot(int ty) {\n        int ps = pos(ty);\n     \
    \   NP _p = p, q = p->p;\n        if (ty == 0) {\n            ch[1] = _p->ch[1];\n\
    \            _p->ch[1].fill(nullptr);\n            for (auto& x : ch[1])\n   \
    \             if (x) x->p = this;\n        }\n        con(_p, _p->ch[ty][ps],\
    \ ch[ty][1 - ps]);\n        con(this, ch[ty][1 - ps], _p);\n        _p->update();\n\
    \        update();\n        p = q;\n        if (!q) return;\n        if (q->lt\
    \ == _p) q->lt = this;\n        for (auto& v : q->ch)\n            for (auto&\
    \ x : v)\n                if (x == _p) x = this;\n        q->update();\n    }\n\
    \    void splay(int ty) {\n        int ps;\n        while ((ps = pos(ty)) != -1)\
    \ {\n            int pps = p->pos(ty);\n            if (pps == -1) {\n       \
    \         rot(ty);\n            } else if (ps == pps) {\n                p->rot(ty);\n\
    \                rot(ty);\n            } else {\n                rot(ty);\n  \
    \              rot(ty);\n            }\n        }\n    }\n    void expose() {\n\
    \        supush();\n        splay(0);\n        splay(1);\n        if (NP z = ch[0][1])\
    \ {\n            z->push();\n            con(z, z->ch[1][1], lt);\n          \
    \  lt = z;\n            ch[0][1] = nullptr;\n            z->update();\n      \
    \      update();\n        }\n        NP u = p;\n        while (u) {\n        \
    \    u->splay(0);\n            u->splay(1);\n            NP ur = u->lt;\n    \
    \        if (auto r = u->ch[0][1]) {\n                // swap ur, r\n        \
    \        r->push();\n                r->ch[1] = ur->ch[1];\n                ur->ch[1].fill(nullptr);\n\
    \                for (auto& x : r->ch[1])\n                    if (x) x->p = r;\n\
    \                r->update();\n                u->lt = r;\n            } else\
    \ if (!ur->ch[1][0]) {\n                // use ur->ch[1][1]\n                con(u,\
    \ u->lt, ur->ch[1][1]);\n            } else {\n                // use prev(ur)\
    \ in light-tree\n                NP q = ur->ch[1][0];\n                con(u,\
    \ u->lt, q);\n                q->push();\n                while (q->ch[1][1])\
    \ {\n                    q = q->ch[1][1];\n                    q->push();\n  \
    \              }\n                q->splay(1);\n                con(q, q->ch[1][1],\
    \ ur->ch[1][1]);\n                q->update();\n            }\n            ur->ch[1].fill(nullptr);\n\
    \            ur->update();\n            u->ch[0][1] = ur;\n            u->update();\n\
    \            u = u->p;\n        }\n        splay(0);\n    }\n    void supush()\
    \ {\n        if (p) p->supush();\n        push();\n    }\n    void link(NP r)\
    \ {\n        evert();\n        r->expose();\n        assert(!r->ch[0][1]);\n \
    \       con(r, r->ch[0][1], this);\n        r->update();\n    }\n    void cut()\
    \ {\n        expose();\n        assert(ch[0][0]);\n        ch[0][0]->p = nullptr;\n\
    \        ch[0][0] = nullptr;\n        update();\n    }\n    void evert() {\n \
    \       expose();\n        revdata();\n        expose();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/toptree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/toptree.hpp
layout: document
redirect_from:
- /library/src/datastructure/toptree.hpp
- /library/src/datastructure/toptree.hpp.html
title: src/datastructure/toptree.hpp
---
