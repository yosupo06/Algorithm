---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/hl_vertex_add_path_sum.test.cpp
    title: src/hl_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hl_vertex_add_subtree_sum.test.cpp
    title: src/hl_vertex_add_subtree_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n\ntemplate <class D, class Op> struct\
    \ SimpleSeg {\n    D e;\n    Op op;\n    int n, sz, lg;  // size(extended to 2^i),\
    \ lg\n    V<D> d;\n\n    SimpleSeg(const V<D>& v, D _e, Op _op) : e(_e), op(_op)\
    \ {\n        n = int(v.size());\n        lg = 1;\n        while ((1 << lg) < n)\
    \ lg++;\n        sz = 1 << lg;\n        d = V<D>(2 * sz, e);\n        for (int\
    \ i = 0; i < n; i++) d[sz + i] = v[i];\n        for (int i = sz - 1; i >= 0; i--)\
    \ {\n            update(i);\n        }\n    }\n\n    void update(int k) { d[k]\
    \ = op(d[2 * k], d[2 * k + 1]); }\n\n    void set(int p, D x) {\n        assert(0\
    \ <= p && p < n);\n        p += sz;\n        d[p] = x;\n        for (int i = 1;\
    \ i <= lg; i++) update(p >> i);\n    }\n\n    D single(int p) const {\n      \
    \  assert(0 <= p && p < n);\n        return d[p + sz];\n    }\n\n    D sum(int\
    \ a, int b) const {\n        assert(a <= b);\n        D sml = e, smr = e;\n  \
    \      a += sz;\n        b += sz;\n\n        while (a < b) {\n            if (a\
    \ & 1) sml = op(sml, d[a++]);\n            if (b & 1) smr = op(d[--b], smr);\n\
    \            a >>= 1;\n            b >>= 1;\n        }\n        return op(sml,\
    \ smr);\n    }\n\n    D all_sum() const {\n        return d[1];\n    }\n\n   \
    \ // min i s.t. f(d[a] + d[a+1] + ... d[i]) == true (or return n + 1)\n    template\
    \ <class Comp> int search_left(int a, Comp f) {\n        a += sz;\n        D sm\
    \ = e;\n        if (f(e)) return a;\n        while (true) {\n            if (f(op(sm,\
    \ d[a]))) {\n                while (a < sz) {\n                    a *= 2;\n \
    \                   if (!f(op(sm, d[a]))) {\n                        sm = op(sm,\
    \ d[a]);\n                        a++;\n                    }\n              \
    \  }\n                a = a + 1 - sz;\n                return a;\n           \
    \ }\n            if (a & 1) {\n                sm = op(sm, d[a]);\n          \
    \      a++;\n                if ((a & -a) == a) break;\n            }\n      \
    \      a >>= 1;\n        }\n        return n + 1;\n    }\n};\n\ntemplate <class\
    \ D, class Op>\nSimpleSeg<D, Op> get_simple_seg(V<D> v, D e, Op op) {\n    return\
    \ SimpleSeg<D, Op>(v, e, op);\n}\n\ntemplate <class D, class L, class OpDD, class\
    \ OpDL, class OpLL> struct SegTree {\n    D e_d;\n    L e_l;\n    OpDD op_dd;\n\
    \    OpDL op_dl;\n    OpLL op_ll;\n    int sz, lg;  //(2^lg\u306B\u62E1\u5F35\u5F8C\
    \u306E)\u30B5\u30A4\u30BA, lg\n    V<D> d;\n    V<L> lz;\n\n    SegTree(const\
    \ V<D>& v,\n            D _e_d,\n            L _e_l,\n            OpDD _op_dd,\n\
    \            OpDL _op_dl,\n            OpLL _op_ll)\n        : e_d(_e_d), e_l(_e_l),\
    \ op_dd(_op_dd), op_dl(_op_dl), op_ll(_op_ll) {\n        int n = int(v.size());\n\
    \        lg = 1;\n        while ((1 << lg) < n) lg++;\n        sz = 1 << lg;\n\
    \        d = V<D>(2 * sz, e_d);\n        lz = V<L>(2 * sz, e_l);\n        for\
    \ (int i = 0; i < n; i++) d[sz + i] = v[i];\n        for (int i = sz - 1; i >=\
    \ 0; i--) {\n            update(i);\n        }\n    }\n\n    void all_add(int\
    \ k, L x) {\n        d[k] = op_dl(d[k], x);\n        if (k < sz) lz[k] = op_ll(lz[k],\
    \ x);\n    }\n    void push(int k) {\n        all_add(2 * k, lz[k]);\n       \
    \ all_add(2 * k + 1, lz[k]);\n        lz[k] = e_l;\n    }\n    void update(int\
    \ k) { d[k] = op_dd(d[2 * k], d[2 * k + 1]); }\n\n    void set(int p, D x) {\n\
    \        p += sz;\n        for (int i = lg; i >= 1; i--) push(p >> i);\n     \
    \   d[p] = x;\n        for (int i = 1; i <= lg; i++) update(p >> i);\n    }\n\n\
    \    void add(int a, int b, L x, int l, int r, int k) {\n        if (b <= l ||\
    \ r <= a) return;\n        if (a <= l && r <= b) {\n            all_add(k, x);\n\
    \            return;\n        }\n        push(k);\n        int mid = (l + r) /\
    \ 2;\n        add(a, b, x, l, mid, 2 * k);\n        add(a, b, x, mid, r, 2 * k\
    \ + 1);\n        update(k);\n    }\n    void add(int a, int b, L x) {\n      \
    \  a += sz;\n        b += sz;\n\n        for (int i = lg; i >= 1; i--) {\n   \
    \         if (((a >> i) << i) != a) push(a >> i);\n            if (((b >> i) <<\
    \ i) != b) push((b - 1) >> i);\n        }\n\n        {\n            int a2 = a,\
    \ b2 = b;\n            while (a < b) {\n                if (a & 1) all_add(a++,\
    \ x);\n                if (b & 1) all_add(--b, x);\n                a >>= 1;\n\
    \                b >>= 1;\n            }\n            a = a2;\n            b =\
    \ b2;\n        }\n\n        for (int i = 1; i <= lg; i++) {\n            if (((a\
    \ >> i) << i) != a) update(a >> i);\n            if (((b >> i) << i) != b) update((b\
    \ - 1) >> i);\n        }\n    }\n\n    D single(int p) {\n        p += sz;\n \
    \       for (int i = lg; i >= 1; i--) push(p >> i);\n        return d[p];\n  \
    \  }\n\n    D sum(int a, int b, int l, int r, int k) {\n        if (b <= l ||\
    \ r <= a) return e_d;\n        if (a <= l && r <= b) return d[k];\n        push(k);\n\
    \        int mid = (l + r) / 2;\n        return op_dd(sum(a, b, l, mid, 2 * k),\
    \ sum(a, b, mid, r, 2 * k + 1));\n    }\n    D sum(int a, int b) {\n        if\
    \ (a == b) return e_d;\n        a += sz;\n        b += sz;\n\n        for (int\
    \ i = lg; i >= 1; i--) {\n            if (((a >> i) << i) != a) push(a >> i);\n\
    \            if (((b >> i) << i) != b) push((b - 1) >> i);\n        }\n\n    \
    \    D sml = e_d, smr = e_d;\n        while (a < b) {\n            if (a & 1)\
    \ sml = op_dd(sml, d[a++]);\n            if (b & 1) smr = op_dd(d[--b], smr);\n\
    \            a >>= 1;\n            b >>= 1;\n        }\n\n        return op_dd(sml,\
    \ smr);\n    }\n\n    D all_sum() const { return d[1]; }\n};\n\ntemplate <class\
    \ D, class L, class OpDD, class OpDL, class OpLL>\nSegTree<D, L, OpDD, OpDL, OpLL>\
    \ get_seg(V<D> v,\n                                        D e_d,\n          \
    \                              L e_l,\n                                      \
    \  OpDD op_dd,\n                                        OpDL op_dl,\n        \
    \                                OpLL op_ll) {\n    return SegTree<D, L, OpDD,\
    \ OpDL, OpLL>(v, e_d, e_l, op_dd, op_dl, op_ll);\n}\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/datastructure/segtree.hpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/hl_vertex_add_path_sum.test.cpp
  - src/hl_vertex_add_subtree_sum.test.cpp
documentation_of: src/datastructure/segtree.hpp
layout: document
redirect_from:
- /library/src/datastructure/segtree.hpp
- /library/src/datastructure/segtree.hpp.html
title: src/datastructure/segtree.hpp
---
