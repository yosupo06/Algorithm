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
  bundledCode: "#line 1 \"src/datastructure/Develop/AASST.hpp\"\n/*\nAA Tree\u306B\
    \u3088\u308A\u66F8\u304B\u308C\u305FStarry Sky Tree\nmerge/split\u306F\u305D\u3093\
    \u306A\u306B\u901F\u304F\u306A\u3044\u305F\u3081\u3042\u3093\u307E\u308A\u5229\
    \u7528\u4FA1\u5024\u306F\u306A\u3044\u304B\u3082\n*/\n\ntemplate<class D, class\
    \ C = less<D>>\nstruct AASSTree {\n    struct Node;\n    typedef Node* NP;\n \
    \   static Node last_d;\n    static NP last;\n    struct Node {\n        NP l,\
    \ r;\n        int level, sz;\n        D v, mi, lz;\n        Node(): l(nullptr),\
    \ r(nullptr), level(0), sz(0) {}\n        Node(D vv): l(last), r(last), level(1),\
    \ sz(1) {\n            v = vv;\n            mi = vv;\n            lz = 0;\n  \
    \      }\n        //\u30E1\u30E2\u30EA\u30D7\u30FC\u30EB\u3092\u3057\u305F\u3044\
    \u6642\u306E\u305F\u3081\u306Bnew\u306B\u306F\u30E9\u30C3\u30D1\u3092\u7528\u610F\
    \u3057\u3066\u304A\u304F\n        static NP make() {\n            return new Node();\n\
    \        }\n        static NP make(D vv) {\n            return new Node(vv);\n\
    \        }\n\n        void update() {\n            sz = 1+l->sz+r->sz;\n     \
    \       mi = v;\n            if (l != last) {\n                mi = min(mi, l->mi);\n\
    \            }\n            if (r != last) {\n                mi = min(mi, r->mi);\n\
    \            }\n        }\n        void lzdata(D x) {\n            v += x;\n \
    \           mi += x;\n            lz += x;\n        }\n        void push() {\n\
    \            if (lz) {\n                if (l != last) {\n                   \
    \ l->lzdata(lz);\n                }\n                if (r != last) {\n      \
    \              r->lzdata(lz);\n                }\n                lz = 0;\n  \
    \          }\n        }\n    } *n;\n\n    static D at(NP n, int k) {\n       \
    \ if (k == n->l->sz) return n->v;\n        n->push();\n        if (k < n->l->sz)\
    \ {\n            return at(n->l, k);\n        } else {\n            return at(n->r,\
    \ k - (n->l->sz+1));\n        }\n    }\n    D at(int k) {\n        return at(n,\
    \ k);\n    }\n    static void add(NP n, int l, int r, D x) {\n        if (n ==\
    \ last || r <= 0 || n->sz <= l) return;\n        if (l <= 0 && n->sz <= r) {\n\
    \            n->lzdata(x);\n            return;\n        }\n        n->push();\n\
    \        add(n->l, l, r, x);\n        if (l <= n->l->sz && n->l->sz < r) {\n \
    \           n->v += x;\n        }\n        add(n->r, l - (n->l->sz+1), r - (n->l->sz+1),\
    \ x);\n        n->update();\n    }\n    void add(int l, int r, D x) {\n      \
    \  add(n, l, r, x);\n    }\n    static D get(NP n, int l, int r) {\n        if\
    \ (n == last || r <= 0 || n->sz <= l) return numeric_limits<D>::max();\n     \
    \   if (l <= 0 && n->sz <= r) return n->mi;\n        n->push();\n        D res\
    \ = numeric_limits<D>::max();\n        res = min(res, get(n->l, l, r));\n    \
    \    if (l <= n->l->sz && n->l->sz < r) {\n            res = min(res, n->v);\n\
    \        }\n        res = min(res, get(n->r, l - (n->l->sz+1), r - (n->l->sz+1)));\n\
    \        return res;\n    }\n    D get(int l, int r) {\n        return get(n,\
    \ l, r);\n    }\n    static int lb(NP n, D x) {\n        if (n == last) return\
    \ 0;\n        if (C()(n->v, x)) return n->l->sz + 1 + lb(n->r, x);\n        return\
    \ lb(n->l, x);\n    }\n    int lb(D v) {\n        return lb(n, v);\n    }\n  \
    \  static int ub(NP n, D x) {\n        if (n == last) return 0;\n        if (C()(x,\
    \ n->v)) return ub(n->l, x);\n        return n->l->sz + 1 + ub(n->r, x);\n   \
    \ }\n    int ub(D v) {\n        return ub(n, v);\n    }\n    void insert(D x)\
    \ {\n        n = insert(n, lb(x), x);\n    }\n    void erase(D x) {\n        n\
    \ = remove(n, lb(x));\n    }\n\n    static void tp(NP n) {\n        if (n == last)\
    \ return;\n        n->push();\n        tp(n->l);\n        cout << n->v << \" \"\
    ;\n        tp(n->r);\n    }\n    void tp() {\n        tp(n);\n        printf(\"\
    \\n\");\n    }\n    static void allpush(NP n) {\n        if (n == last) return;\n\
    \        n->push();\n        allpush(n->l);\n        allpush(n->r);\n    }\n \
    \   void allpush() {\n        allpush(n);\n        return;\n    }\n\n    static\
    \ NP built(int sz, D d[]) {\n        if (!sz) return last;\n        int md = (sz-1)/2;\n\
    \        NP n = Node::make(d[md]);\n        n->l = built(md, d);\n        n->r\
    \ = built(sz-(md+1), d+(md+1));\n        n->level = n->l->level+1;\n        n->update();\n\
    \        return n;\n    }\n    AASSTree() : n(last) {}\n    AASSTree(NP n) : n(n)\
    \ {}\n    //\u6728\u306E\u521D\u671F\u5316\u306Fn\u56DEinsert\u3088\u308A\u4E00\
    \u6C17\u306B\u4F5C\u308B\u65B9\u304C\u6709\u610F\u306B\u901F\u304F\u306A\u308B\
    \u4E8B\u304C\u591A\u3044\n    AASSTree(int sz, D d[]) {\n        n = built(sz,\
    \ d);\n    }\n\n\n    //\u57FA\u672C\u52D5\u4F5C\n    int sz() {\n        return\
    \ n->sz;\n    }\n    void merge(AASSTree r) {\n        n = merge(n, r.n);\n  \
    \  }\n    AASSTree split(int k) {\n        auto y = split(n, k);\n        n =\
    \ y.first;\n        return AASSTree(y.second);\n    }\n    void insert(int k,\
    \ D x) {\n        n = insert(n, k, x);\n    }\n    void remove(int k) {\n    \
    \    n = remove(n, k);\n    }\n\n    //AA\u6728\u306E\u57FA\u672C\u52D5\u4F5C\u3067\
    \u3042\u308Bskew/split split\u306F\u540D\u524D\u304C\u7D1B\u3089\u308F\u3057\u3044\
    \u305F\u3081pull\u306B\u5909\u66F4\u3057\u3066\u3042\u308B\n    static NP skew(NP\
    \ n) {\n        if (n->level == n->l->level) {\n            NP L = n->l;\n   \
    \         n->push(); L->push();\n            n->l = L->r;\n            L->r =\
    \ n;\n            n->update(); L->update();\n            return L;\n        }\n\
    \        return n;\n    }\n    static NP pull(NP n) {\n        if (n->level ==\
    \ n->r->level && n->r->level == n->r->r->level) {\n            NP R = n->r;\n\
    \            n->push(); R->push();\n            n->r = R->l;\n            R->l\
    \ = n;\n            R->level++;\n            n->update(); R->update();\n     \
    \       return R;\n        }\n        return n;\n    }\n\n    static NP leftdown(NP\
    \ n) {\n        assert(n->l->level < n->level);\n        if (n->l->level == n->level-1)\
    \ return n;\n        n->level--;\n        if (n->r->level == n->level) {\n   \
    \         n = pull(n);\n        } else {\n            n->r->level--;\n       \
    \     n->r = skew(n->r);\n            n->r->r = skew(n->r->r);\n            n\
    \ = pull(n);\n            n->r = pull(n->r);\n        }\n        return n;\n \
    \   }\n    static NP rightdown(NP n) {\n        assert(n->r->level <= n->level);\n\
    \        if (n->r->level >= n->level-1) return n;\n        n->level--;\n     \
    \   n = skew(n);\n        n->r = skew(n->r);\n        n = pull(n);\n        return\
    \ n;\n    }\n    static NP superleftdown(NP n) {\n        if (n->l->level == n->level-1)\
    \ return n;\n        if (n->level != n->r->level && n->r->level != n->r->r->level)\
    \ {\n            n->level--;\n            return superleftdown(n);\n        }\n\
    \        n = leftdown(n);\n        n->l = superleftdown(n->l);\n        n = leftdown(n);\n\
    \        return n;\n    }\n    static NP superrightdown(NP n) {\n        if (n->r->level\
    \ >= n->level-1) return n;\n        n = rightdown(n);\n        n->r = superrightdown(n->r);\n\
    \        n = rightdown(n);\n        return n;\n    }\n\n    static NP insert(NP\
    \ n, int k, D x) {\n        if (n == last) {\n            assert(k == 0);\n  \
    \          return Node::make(x);\n        }\n        n->push();\n        if (k\
    \ <= n->l->sz) {\n            n->l = insert(n->l, k, x);\n            n->update();\n\
    \        } else {\n            n->r = insert(n->r, k - (n->l->sz+1), x);\n   \
    \         n->update();\n        }\n        n = skew(n);\n        n = pull(n);\n\
    \        return n;\n    }\n    //pair<0\u756A\u76EE\u306E\u8981\u7D20,0\u756A\u76EE\
    \u306E\u8981\u7D20\u3092\u524A\u9664\u3057\u305F\u6728>\n    static pair<NP, NP>\
    \ at0_with_remove(NP n) {\n        n->push();\n        if (n->l == last) {\n \
    \           return {n, n->r};\n        }\n        auto x = at0_with_remove(n->l);\n\
    \        n->l = x.second;\n        n->update();\n        x.second = leftdown(n);\n\
    \        return x;\n    }\n    static NP remove(NP n, int k) {\n        assert(n\
    \ != last);\n        n->push();\n        if (k == n->l->sz) {\n            if\
    \ (n->level == 1) {\n                return n->r;\n            }\n           \
    \ auto x = at0_with_remove(n->r);\n            NP nn = x.first;\n            nn->push();\n\
    \            nn->l = n->l;\n            nn->r = x.second;\n            nn->level\
    \ = n->level;\n            nn->update();\n            return rightdown(nn);\n\
    \        }\n        if (k < n->l->sz) {\n            n->l = remove(n->l, k);\n\
    \            n->update();\n            return leftdown(n);\n        } else {\n\
    \            n->r = remove(n->r, k - (n->l->sz+1));\n            n->update();\n\
    \            return rightdown(n);\n        }\n    }\n    static NP merge(NP l,\
    \ NP r) {\n        if (l == last) return r;\n        if (r == last) return l;\n\
    \        if (l->level == r->level) {\n            auto x = at0_with_remove(r);\n\
    \            NP n = x.first;\n            n->push();\n            n->r = x.second;\n\
    \            n->l = l;\n            n->level = l->level+1;\n            n->update();\n\
    \            return rightdown(n);\n        }\n        NP n;\n        l->push();\
    \ r->push();\n        if (l->level > r->level) {\n            l->push();\n   \
    \         l->r = merge(l->r, r);\n            l->update();\n            n = l;\n\
    \        } else {\n            r->push();\n            r->l = merge(l, r->l);\n\
    \            r->update();\n            n = r;\n        }\n        n = skew(n);\n\
    \        n = pull(n);\n        return n;\n    }\n    static pair<NP, NP> split(NP\
    \ n, int k) {\n        if (n == last) return {last, last};\n        n->push();\n\
    \        if (k <= n->l->sz) {\n            auto y = split(n->l, k);\n        \
    \    n->l = y.second;\n            n->update();\n            n = superleftdown(n);\n\
    \            y.second = n;\n            return y;\n        } else {\n        \
    \    auto y = split(n->r, k- (n->l->sz+1));\n            n->r = y.first;\n   \
    \         n->update();\n            n = superrightdown(n);\n            y.first\
    \ = n;\n            return y;\n        }\n    }\n};\ntemplate<class D, class C>\n\
    typename AASSTree<D, C>::Node AASSTree<D, C>::last_d = AASSTree<D, C>::Node();\n\
    template<class D, class C>\ntypename AASSTree<D, C>::NP AASSTree<D, C>::last =\
    \ &AASSTree<D, C>::last_d;\n"
  code: "/*\nAA Tree\u306B\u3088\u308A\u66F8\u304B\u308C\u305FStarry Sky Tree\nmerge/split\u306F\
    \u305D\u3093\u306A\u306B\u901F\u304F\u306A\u3044\u305F\u3081\u3042\u3093\u307E\
    \u308A\u5229\u7528\u4FA1\u5024\u306F\u306A\u3044\u304B\u3082\n*/\n\ntemplate<class\
    \ D, class C = less<D>>\nstruct AASSTree {\n    struct Node;\n    typedef Node*\
    \ NP;\n    static Node last_d;\n    static NP last;\n    struct Node {\n     \
    \   NP l, r;\n        int level, sz;\n        D v, mi, lz;\n        Node(): l(nullptr),\
    \ r(nullptr), level(0), sz(0) {}\n        Node(D vv): l(last), r(last), level(1),\
    \ sz(1) {\n            v = vv;\n            mi = vv;\n            lz = 0;\n  \
    \      }\n        //\u30E1\u30E2\u30EA\u30D7\u30FC\u30EB\u3092\u3057\u305F\u3044\
    \u6642\u306E\u305F\u3081\u306Bnew\u306B\u306F\u30E9\u30C3\u30D1\u3092\u7528\u610F\
    \u3057\u3066\u304A\u304F\n        static NP make() {\n            return new Node();\n\
    \        }\n        static NP make(D vv) {\n            return new Node(vv);\n\
    \        }\n\n        void update() {\n            sz = 1+l->sz+r->sz;\n     \
    \       mi = v;\n            if (l != last) {\n                mi = min(mi, l->mi);\n\
    \            }\n            if (r != last) {\n                mi = min(mi, r->mi);\n\
    \            }\n        }\n        void lzdata(D x) {\n            v += x;\n \
    \           mi += x;\n            lz += x;\n        }\n        void push() {\n\
    \            if (lz) {\n                if (l != last) {\n                   \
    \ l->lzdata(lz);\n                }\n                if (r != last) {\n      \
    \              r->lzdata(lz);\n                }\n                lz = 0;\n  \
    \          }\n        }\n    } *n;\n\n    static D at(NP n, int k) {\n       \
    \ if (k == n->l->sz) return n->v;\n        n->push();\n        if (k < n->l->sz)\
    \ {\n            return at(n->l, k);\n        } else {\n            return at(n->r,\
    \ k - (n->l->sz+1));\n        }\n    }\n    D at(int k) {\n        return at(n,\
    \ k);\n    }\n    static void add(NP n, int l, int r, D x) {\n        if (n ==\
    \ last || r <= 0 || n->sz <= l) return;\n        if (l <= 0 && n->sz <= r) {\n\
    \            n->lzdata(x);\n            return;\n        }\n        n->push();\n\
    \        add(n->l, l, r, x);\n        if (l <= n->l->sz && n->l->sz < r) {\n \
    \           n->v += x;\n        }\n        add(n->r, l - (n->l->sz+1), r - (n->l->sz+1),\
    \ x);\n        n->update();\n    }\n    void add(int l, int r, D x) {\n      \
    \  add(n, l, r, x);\n    }\n    static D get(NP n, int l, int r) {\n        if\
    \ (n == last || r <= 0 || n->sz <= l) return numeric_limits<D>::max();\n     \
    \   if (l <= 0 && n->sz <= r) return n->mi;\n        n->push();\n        D res\
    \ = numeric_limits<D>::max();\n        res = min(res, get(n->l, l, r));\n    \
    \    if (l <= n->l->sz && n->l->sz < r) {\n            res = min(res, n->v);\n\
    \        }\n        res = min(res, get(n->r, l - (n->l->sz+1), r - (n->l->sz+1)));\n\
    \        return res;\n    }\n    D get(int l, int r) {\n        return get(n,\
    \ l, r);\n    }\n    static int lb(NP n, D x) {\n        if (n == last) return\
    \ 0;\n        if (C()(n->v, x)) return n->l->sz + 1 + lb(n->r, x);\n        return\
    \ lb(n->l, x);\n    }\n    int lb(D v) {\n        return lb(n, v);\n    }\n  \
    \  static int ub(NP n, D x) {\n        if (n == last) return 0;\n        if (C()(x,\
    \ n->v)) return ub(n->l, x);\n        return n->l->sz + 1 + ub(n->r, x);\n   \
    \ }\n    int ub(D v) {\n        return ub(n, v);\n    }\n    void insert(D x)\
    \ {\n        n = insert(n, lb(x), x);\n    }\n    void erase(D x) {\n        n\
    \ = remove(n, lb(x));\n    }\n\n    static void tp(NP n) {\n        if (n == last)\
    \ return;\n        n->push();\n        tp(n->l);\n        cout << n->v << \" \"\
    ;\n        tp(n->r);\n    }\n    void tp() {\n        tp(n);\n        printf(\"\
    \\n\");\n    }\n    static void allpush(NP n) {\n        if (n == last) return;\n\
    \        n->push();\n        allpush(n->l);\n        allpush(n->r);\n    }\n \
    \   void allpush() {\n        allpush(n);\n        return;\n    }\n\n    static\
    \ NP built(int sz, D d[]) {\n        if (!sz) return last;\n        int md = (sz-1)/2;\n\
    \        NP n = Node::make(d[md]);\n        n->l = built(md, d);\n        n->r\
    \ = built(sz-(md+1), d+(md+1));\n        n->level = n->l->level+1;\n        n->update();\n\
    \        return n;\n    }\n    AASSTree() : n(last) {}\n    AASSTree(NP n) : n(n)\
    \ {}\n    //\u6728\u306E\u521D\u671F\u5316\u306Fn\u56DEinsert\u3088\u308A\u4E00\
    \u6C17\u306B\u4F5C\u308B\u65B9\u304C\u6709\u610F\u306B\u901F\u304F\u306A\u308B\
    \u4E8B\u304C\u591A\u3044\n    AASSTree(int sz, D d[]) {\n        n = built(sz,\
    \ d);\n    }\n\n\n    //\u57FA\u672C\u52D5\u4F5C\n    int sz() {\n        return\
    \ n->sz;\n    }\n    void merge(AASSTree r) {\n        n = merge(n, r.n);\n  \
    \  }\n    AASSTree split(int k) {\n        auto y = split(n, k);\n        n =\
    \ y.first;\n        return AASSTree(y.second);\n    }\n    void insert(int k,\
    \ D x) {\n        n = insert(n, k, x);\n    }\n    void remove(int k) {\n    \
    \    n = remove(n, k);\n    }\n\n    //AA\u6728\u306E\u57FA\u672C\u52D5\u4F5C\u3067\
    \u3042\u308Bskew/split split\u306F\u540D\u524D\u304C\u7D1B\u3089\u308F\u3057\u3044\
    \u305F\u3081pull\u306B\u5909\u66F4\u3057\u3066\u3042\u308B\n    static NP skew(NP\
    \ n) {\n        if (n->level == n->l->level) {\n            NP L = n->l;\n   \
    \         n->push(); L->push();\n            n->l = L->r;\n            L->r =\
    \ n;\n            n->update(); L->update();\n            return L;\n        }\n\
    \        return n;\n    }\n    static NP pull(NP n) {\n        if (n->level ==\
    \ n->r->level && n->r->level == n->r->r->level) {\n            NP R = n->r;\n\
    \            n->push(); R->push();\n            n->r = R->l;\n            R->l\
    \ = n;\n            R->level++;\n            n->update(); R->update();\n     \
    \       return R;\n        }\n        return n;\n    }\n\n    static NP leftdown(NP\
    \ n) {\n        assert(n->l->level < n->level);\n        if (n->l->level == n->level-1)\
    \ return n;\n        n->level--;\n        if (n->r->level == n->level) {\n   \
    \         n = pull(n);\n        } else {\n            n->r->level--;\n       \
    \     n->r = skew(n->r);\n            n->r->r = skew(n->r->r);\n            n\
    \ = pull(n);\n            n->r = pull(n->r);\n        }\n        return n;\n \
    \   }\n    static NP rightdown(NP n) {\n        assert(n->r->level <= n->level);\n\
    \        if (n->r->level >= n->level-1) return n;\n        n->level--;\n     \
    \   n = skew(n);\n        n->r = skew(n->r);\n        n = pull(n);\n        return\
    \ n;\n    }\n    static NP superleftdown(NP n) {\n        if (n->l->level == n->level-1)\
    \ return n;\n        if (n->level != n->r->level && n->r->level != n->r->r->level)\
    \ {\n            n->level--;\n            return superleftdown(n);\n        }\n\
    \        n = leftdown(n);\n        n->l = superleftdown(n->l);\n        n = leftdown(n);\n\
    \        return n;\n    }\n    static NP superrightdown(NP n) {\n        if (n->r->level\
    \ >= n->level-1) return n;\n        n = rightdown(n);\n        n->r = superrightdown(n->r);\n\
    \        n = rightdown(n);\n        return n;\n    }\n\n    static NP insert(NP\
    \ n, int k, D x) {\n        if (n == last) {\n            assert(k == 0);\n  \
    \          return Node::make(x);\n        }\n        n->push();\n        if (k\
    \ <= n->l->sz) {\n            n->l = insert(n->l, k, x);\n            n->update();\n\
    \        } else {\n            n->r = insert(n->r, k - (n->l->sz+1), x);\n   \
    \         n->update();\n        }\n        n = skew(n);\n        n = pull(n);\n\
    \        return n;\n    }\n    //pair<0\u756A\u76EE\u306E\u8981\u7D20,0\u756A\u76EE\
    \u306E\u8981\u7D20\u3092\u524A\u9664\u3057\u305F\u6728>\n    static pair<NP, NP>\
    \ at0_with_remove(NP n) {\n        n->push();\n        if (n->l == last) {\n \
    \           return {n, n->r};\n        }\n        auto x = at0_with_remove(n->l);\n\
    \        n->l = x.second;\n        n->update();\n        x.second = leftdown(n);\n\
    \        return x;\n    }\n    static NP remove(NP n, int k) {\n        assert(n\
    \ != last);\n        n->push();\n        if (k == n->l->sz) {\n            if\
    \ (n->level == 1) {\n                return n->r;\n            }\n           \
    \ auto x = at0_with_remove(n->r);\n            NP nn = x.first;\n            nn->push();\n\
    \            nn->l = n->l;\n            nn->r = x.second;\n            nn->level\
    \ = n->level;\n            nn->update();\n            return rightdown(nn);\n\
    \        }\n        if (k < n->l->sz) {\n            n->l = remove(n->l, k);\n\
    \            n->update();\n            return leftdown(n);\n        } else {\n\
    \            n->r = remove(n->r, k - (n->l->sz+1));\n            n->update();\n\
    \            return rightdown(n);\n        }\n    }\n    static NP merge(NP l,\
    \ NP r) {\n        if (l == last) return r;\n        if (r == last) return l;\n\
    \        if (l->level == r->level) {\n            auto x = at0_with_remove(r);\n\
    \            NP n = x.first;\n            n->push();\n            n->r = x.second;\n\
    \            n->l = l;\n            n->level = l->level+1;\n            n->update();\n\
    \            return rightdown(n);\n        }\n        NP n;\n        l->push();\
    \ r->push();\n        if (l->level > r->level) {\n            l->push();\n   \
    \         l->r = merge(l->r, r);\n            l->update();\n            n = l;\n\
    \        } else {\n            r->push();\n            r->l = merge(l, r->l);\n\
    \            r->update();\n            n = r;\n        }\n        n = skew(n);\n\
    \        n = pull(n);\n        return n;\n    }\n    static pair<NP, NP> split(NP\
    \ n, int k) {\n        if (n == last) return {last, last};\n        n->push();\n\
    \        if (k <= n->l->sz) {\n            auto y = split(n->l, k);\n        \
    \    n->l = y.second;\n            n->update();\n            n = superleftdown(n);\n\
    \            y.second = n;\n            return y;\n        } else {\n        \
    \    auto y = split(n->r, k- (n->l->sz+1));\n            n->r = y.first;\n   \
    \         n->update();\n            n = superrightdown(n);\n            y.first\
    \ = n;\n            return y;\n        }\n    }\n};\ntemplate<class D, class C>\n\
    typename AASSTree<D, C>::Node AASSTree<D, C>::last_d = AASSTree<D, C>::Node();\n\
    template<class D, class C>\ntypename AASSTree<D, C>::NP AASSTree<D, C>::last =\
    \ &AASSTree<D, C>::last_d;\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/AASST.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/AASST.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/AASST.hpp
- /library/src/datastructure/Develop/AASST.hpp.html
title: src/datastructure/Develop/AASST.hpp
---
