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
  bundledCode: "#line 1 \"src/datastructure/Develop/SplayTMSet.hpp\"\nstruct Tree\
    \ {\n    using D = int;\n    struct Node;\n    using NP = Node*;\n    static Node\
    \ last_d;\n    static NP last, la;\n    struct Node {\n        NP p, l, r;\n \
    \       int sz;\n        D v;\n        Node(D v) :p(nullptr), l(last), r(last),\
    \ sz(1), v(v) {}\n        Node(NP p, NP l, NP r, int sz = 0) : p(p), l(l), r(r),\
    \ sz(sz) {}\n        bool is_root() {\n            return p == nullptr;\n    \
    \    }\n        void rotr() {\n            NP q = p, qq = q->p;\n            q->l\
    \ = r; r->p = q;\n            r = q; q->p = this;\n            q->update(); update();\n\
    \            if ((p = qq)) {\n                if (qq->l == q) qq->l = this;\n\
    \                if (qq->r == q) qq->r = this;\n                qq->update();\n\
    \            }\n        }\n        void rotl() {\n            NP q = p, qq = q->p;\n\
    \            q->r = l; l->p = q;\n            l = q; q->p = this;\n          \
    \  q->update(); update();\n            if ((p = qq)) {\n                if (qq->l\
    \ == q) qq->l = this;\n                if (qq->r == q) qq->r = this;\n       \
    \         qq->update();\n            }\n        }\n        void splay() {\n  \
    \          assert(this != last);\n            while (!is_root()) {\n         \
    \       NP q = p;\n                if (q->is_root()) {\n                    if\
    \ (q->l == this) rotr();\n                    else rotl();\n                 \
    \   continue;\n                }\n                NP r = q->p;\n             \
    \   if (r->l == q) {\n                    if (q->l == this) {q->rotr(); rotr();}\n\
    \                    else {rotl(); rotr();}\n                } else {\n      \
    \              if (q->r == this) {q->rotl(); rotl();}\n                    else\
    \ {rotr(); rotl();}\n                }\n            }\n        }\n        void\
    \ push() {\n \n        }\n        NP update() {\n            if (this == last)\
    \ return this;\n            sz = 1+l->sz+r->sz;\n            return this;\n  \
    \      }\n    } *n;\n    static NP merge(NP l, NP r) {\n        if (l == last)\
    \ {\n            return r;\n        }\n        while (l->r != last) {\n      \
    \      l = l->r;\n        }\n        l->splay();\n        l->r = r;\n        r->p\
    \ = l;\n        return l->update();\n    }\n    static pair<NP, NP> split(NP x,\
    \ int k) {\n        assert(0 <= k && k <= x->sz);\n        if (k == x->sz) {\n\
    \            return {x, last};\n        }\n        while (k != x->l->sz) {\n \
    \           if (k < x->l->sz) {\n                x = x->l;\n            } else\
    \ {\n                k -= x->l->sz+1;\n                x = x->r;\n           \
    \ }\n        }\n\n        x->splay();\n        NP l = x->l;\n        l->p = NULL;\n\
    \        x->l = last;\n        return {l, x->update()};\n    }\n \n    Tree()\
    \ : n(last) {}\n    Tree(NP n) : n(n) {}\n    int sz() {\n        return n->sz;\n\
    \    }\n    void insert(int k, D v) {\n        auto u = split(n, k);\n       \
    \ n = merge(merge(u.first, new Node(v)), u.second);\n    }\n    void erase(int\
    \ k) {\n        auto u = split(n, k);\n        n = merge(u.first, split(u.second,\
    \ 1).second);\n    }\n    int getc(int k) {\n        auto u = split(n, k);\n \
    \       int res = u.second->v;\n        n = merge(u.first, u.second);\n      \
    \  return res;\n    }\n};\nTree::Node Tree::last_d = Tree::Node(NULL, NULL, NULL,\
    \ 0);\nTree::NP Tree::last = &last_d;\nTree::NP Tree::la;\n"
  code: "struct Tree {\n    using D = int;\n    struct Node;\n    using NP = Node*;\n\
    \    static Node last_d;\n    static NP last, la;\n    struct Node {\n       \
    \ NP p, l, r;\n        int sz;\n        D v;\n        Node(D v) :p(nullptr), l(last),\
    \ r(last), sz(1), v(v) {}\n        Node(NP p, NP l, NP r, int sz = 0) : p(p),\
    \ l(l), r(r), sz(sz) {}\n        bool is_root() {\n            return p == nullptr;\n\
    \        }\n        void rotr() {\n            NP q = p, qq = q->p;\n        \
    \    q->l = r; r->p = q;\n            r = q; q->p = this;\n            q->update();\
    \ update();\n            if ((p = qq)) {\n                if (qq->l == q) qq->l\
    \ = this;\n                if (qq->r == q) qq->r = this;\n                qq->update();\n\
    \            }\n        }\n        void rotl() {\n            NP q = p, qq = q->p;\n\
    \            q->r = l; l->p = q;\n            l = q; q->p = this;\n          \
    \  q->update(); update();\n            if ((p = qq)) {\n                if (qq->l\
    \ == q) qq->l = this;\n                if (qq->r == q) qq->r = this;\n       \
    \         qq->update();\n            }\n        }\n        void splay() {\n  \
    \          assert(this != last);\n            while (!is_root()) {\n         \
    \       NP q = p;\n                if (q->is_root()) {\n                    if\
    \ (q->l == this) rotr();\n                    else rotl();\n                 \
    \   continue;\n                }\n                NP r = q->p;\n             \
    \   if (r->l == q) {\n                    if (q->l == this) {q->rotr(); rotr();}\n\
    \                    else {rotl(); rotr();}\n                } else {\n      \
    \              if (q->r == this) {q->rotl(); rotl();}\n                    else\
    \ {rotr(); rotl();}\n                }\n            }\n        }\n        void\
    \ push() {\n \n        }\n        NP update() {\n            if (this == last)\
    \ return this;\n            sz = 1+l->sz+r->sz;\n            return this;\n  \
    \      }\n    } *n;\n    static NP merge(NP l, NP r) {\n        if (l == last)\
    \ {\n            return r;\n        }\n        while (l->r != last) {\n      \
    \      l = l->r;\n        }\n        l->splay();\n        l->r = r;\n        r->p\
    \ = l;\n        return l->update();\n    }\n    static pair<NP, NP> split(NP x,\
    \ int k) {\n        assert(0 <= k && k <= x->sz);\n        if (k == x->sz) {\n\
    \            return {x, last};\n        }\n        while (k != x->l->sz) {\n \
    \           if (k < x->l->sz) {\n                x = x->l;\n            } else\
    \ {\n                k -= x->l->sz+1;\n                x = x->r;\n           \
    \ }\n        }\n\n        x->splay();\n        NP l = x->l;\n        l->p = NULL;\n\
    \        x->l = last;\n        return {l, x->update()};\n    }\n \n    Tree()\
    \ : n(last) {}\n    Tree(NP n) : n(n) {}\n    int sz() {\n        return n->sz;\n\
    \    }\n    void insert(int k, D v) {\n        auto u = split(n, k);\n       \
    \ n = merge(merge(u.first, new Node(v)), u.second);\n    }\n    void erase(int\
    \ k) {\n        auto u = split(n, k);\n        n = merge(u.first, split(u.second,\
    \ 1).second);\n    }\n    int getc(int k) {\n        auto u = split(n, k);\n \
    \       int res = u.second->v;\n        n = merge(u.first, u.second);\n      \
    \  return res;\n    }\n};\nTree::Node Tree::last_d = Tree::Node(NULL, NULL, NULL,\
    \ 0);\nTree::NP Tree::last = &last_d;\nTree::NP Tree::la;\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/SplayTMSet.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/SplayTMSet.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/SplayTMSet.hpp
- /library/src/datastructure/Develop/SplayTMSet.hpp.html
title: src/datastructure/Develop/SplayTMSet.hpp
---
