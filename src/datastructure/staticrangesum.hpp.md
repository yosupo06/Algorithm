---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/staticrangesum_rectangle_sum.test.cpp
    title: src/staticrangesum_rectangle_sum.test.cpp
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
  code: "#pragma once\n\n#include \"base.hpp\"\n\ntemplate <class D, class I> struct\
    \ StaticRangeSum {\n    struct P {\n        I x, y;\n        D val;\n    };\n\n\
    \    StaticRangeSum(V<P> ps) {\n        if (!ps.size()) return;\n        sort(ps.begin(),\
    \ ps.end(), [&](P l, P r) { return l.x < r.x; });\n        for (auto p : ps) {\n\
    \            xs.push_back(p.x);\n            ys.push_back(p.y);\n        }\n \
    \       sort(ys.begin(), ys.end());\n        ys.erase(unique(ys.begin(), ys.end()),\
    \ ys.end());\n\n        int n = int(xs.size());\n        int m = int(ys.size());\n\
    \n        lg = 1;\n        while ((1 << lg) < m) lg++;\n\n        mid = V<int>(lg);\n\
    \        bits = VV<int>(lg, V<int>(n + 1));\n        sums = VV<D>(lg + 1, V<D>(n\
    \ + 1));\n\n        struct Q {\n            int y;\n            D val;\n     \
    \   };\n        V<Q> v;\n        for (auto p : ps) {\n            int y = int(lower_bound(ys.begin(),\
    \ ys.end(), p.y) - ys.begin());\n            v.push_back({y, p.val});\n      \
    \  }\n        for (int i = 0; i < n; i++) {\n            Q q = v[i];\n       \
    \     sums[lg][i + 1] = sums[lg][i] + q.val;\n        }\n        for (int lv =\
    \ lg - 1; lv >= 0; lv--) {\n            array<V<Q>, 2> nx;\n            for (int\
    \ i = 0; i < n; i++) {\n                Q q = v[i];\n                bool f =\
    \ (q.y >> lv) & 1;\n                bits[lv][i + 1] = bits[lv][i] + (f ? 0 : 1);\n\
    \                nx[f].push_back(q);\n            }\n            mid[lv] = int(nx[0].size());\n\
    \            v.clear();\n            v.insert(v.end(), nx[0].begin(), nx[0].end());\n\
    \            v.insert(v.end(), nx[1].begin(), nx[1].end());\n            for (int\
    \ i = 0; i < n; i++) {\n                Q q = v[i];\n                sums[lv][i\
    \ + 1] = sums[lv][i] + q.val;\n            }\n        }\n    }\n    // (low_x\
    \ <= x < up_x), (low_y <= y < up_y)\u306A\u308B\u70B9\u306E\u91CD\u307F\u306E\u7DCF\
    \u548C\n    D sum(I low_x, I low_y, I up_x, I up_y) {\n        int _lx = int(lower_bound(xs.begin(),\
    \ xs.end(), low_x) - xs.begin());\n        int _ux = int(lower_bound(xs.begin(),\
    \ xs.end(), up_x) - xs.begin());\n        int _ly = int(lower_bound(ys.begin(),\
    \ ys.end(), low_y) - ys.begin());\n        int _uy = int(lower_bound(ys.begin(),\
    \ ys.end(), up_y) - ys.begin());\n        if (_lx >= _ux || _ly >= _uy) return\
    \ D(0);\n        return sum(_lx, _ux, _uy) - sum(_lx, _ux, _ly);\n    }\n\n  private:\n\
    \    int lg;\n    V<I> xs, ys;\n\n    V<int> mid;\n    VV<int> bits;\n    VV<D>\
    \ sums;\n    D sum(int l, int r, int u) {\n        if (u == (1 << lg)) return\
    \ sums[lg][r] - sums[lg][l];\n        D ans = 0;\n        for (int lv = lg - 1;\
    \ lv >= 0; lv--) {\n            bool f = (u >> lv) & 1;\n            int l0 =\
    \ bits[lv][l], r0 = bits[lv][r];\n            if (f) {\n                ans +=\
    \ sums[lv][r0] - sums[lv][l0];\n                l = l - l0 + mid[lv];\n      \
    \          r = r - r0 + mid[lv];\n            } else {\n                l = l0;\n\
    \                r = r0;\n            }\n        }\n        return ans;\n    }\n\
    };\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/datastructure/staticrangesum.hpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/staticrangesum_rectangle_sum.test.cpp
documentation_of: src/datastructure/staticrangesum.hpp
layout: document
redirect_from:
- /library/src/datastructure/staticrangesum.hpp
- /library/src/datastructure/staticrangesum.hpp.html
title: src/datastructure/staticrangesum.hpp
---
