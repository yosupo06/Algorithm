---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/fenwick.hpp
    title: src/datastructure/fenwick.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/fenwick_2d_rectangle_sum.test.cpp
    title: src/fenwick_2d_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n#include \"datastructure/fenwick.hpp\"\
    \n\ntemplate <class D, class I> struct Fenwick2D {\n    using P = pair<I, I>;\n\
    \    V<P> points;\n    VV<I> ys;\n    V<Fenwick<D>> fws;\n    int lg, sz;\n  \
    \  Fenwick2D(V<P> _points) : points(_points) {\n        sort(points.begin(), points.end());\n\
    \        points.erase(unique(points.begin(), points.end()), points.end());\n \
    \       int n = int(points.size());\n        lg = 1;\n        while ((1 << lg)\
    \ < n) lg++;\n        sz = 1 << lg;\n        ys = VV<I>(2 * sz);\n        for\
    \ (int i = 0; i < n; i++) ys[sz + i].push_back(points[i].second);\n        for\
    \ (int i = sz - 1; i >= 1; i--) {\n            ys[i] = V<I>(ys[2 * i].size() +\
    \ ys[2 * i + 1].size());\n            merge(ys[2 * i].begin(), ys[2 * i].end(),\
    \ ys[2 * i + 1].begin(),\n                  ys[2 * i + 1].end(), ys[i].begin());\n\
    \        }\n        fws = V<Fenwick<D>>(2 * sz);\n        for (int i = 1; i <\
    \ 2 * sz; i++) {\n            fws[i] = Fenwick<D>(int(ys[i].size()));\n      \
    \  }\n    }\n\n    void add(P p, D x) {\n        int k =\n            int(lower_bound(points.begin(),\
    \ points.end(), p) - points.begin());\n        k += sz;\n        while (k) {\n\
    \            int yid = int(lower_bound(ys[k].begin(), ys[k].end(), p.second) -\n\
    \                          ys[k].begin());\n            fws[k].add(yid, x);\n\
    \            k >>= 1;\n        }\n    }\n\n    D sum(int a, int b, I lw, I up,\
    \ int l, int r, int k) {\n        if (b <= l || r <= a) return D(0);\n       \
    \ if (a <= l && r <= b) {\n            int lid = int(lower_bound(ys[k].begin(),\
    \ ys[k].end(), lw) -\n                          ys[k].begin());\n            int\
    \ uid = int(lower_bound(ys[k].begin(), ys[k].end(), up) -\n                  \
    \        ys[k].begin());\n            return fws[k].sum(lid, uid);\n        }\n\
    \        int mid = (l + r) / 2;\n        return sum(a, b, lw, up, l, mid, 2 *\
    \ k) +\n               sum(a, b, lw, up, mid, r, 2 * k + 1);\n    }\n\n    D sum(P\
    \ lw, P up) {\n        int a = int(lower_bound(points.begin(), points.end(), lw.first,\n\
    \                                [&](P p, I x) { return p.first < x; }) -\n  \
    \                  points.begin());\n        int b = int(lower_bound(points.begin(),\
    \ points.end(), up.first,\n                                [&](P p, I x) { return\
    \ p.first < x; }) -\n                    points.begin());\n        return sum(a,\
    \ b, lw.second, up.second, 0, sz, 1);\n    }\n};\n"
  dependsOn:
  - src/base.hpp
  - src/datastructure/fenwick.hpp
  isVerificationFile: false
  path: src/datastructure/fenwick2d.hpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/fenwick_2d_rectangle_sum.test.cpp
documentation_of: src/datastructure/fenwick2d.hpp
layout: document
redirect_from:
- /library/src/datastructure/fenwick2d.hpp
- /library/src/datastructure/fenwick2d.hpp.html
title: src/datastructure/fenwick2d.hpp
---
