---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/string/zalgo.hpp
    title: src/string/zalgo.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/run.test.cpp
    title: src/run.test.cpp
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
  code: "#pragma once\n\n#include \"base.hpp\"\n#include \"string/zalgo.hpp\"\n\n\
    template<class Str>\nstruct RunExec {\n    VV<pair<int, int>> runs;\n\n    int\
    \ n;\n    Str a;\n\n    V<int> rev(V<int> l) {\n        reverse(l.begin(), l.end());\n\
    \        return l;\n    }\n\n    V<int> sub_a(int l, int r) { return {a.begin()\
    \ + l, a.begin() + r}; }\n    V<int> concat(V<int> l, const V<int>& r) {\n   \
    \     l.insert(l.end(), r.begin(), r.end());\n        return l;\n    }\n\n   \
    \ void run(int l, int r, int f) {\n        if (l + 1 == r) return;\n        int\
    \ md = (l + r + f) / 2;\n        run(l, md, f);\n        run(md, r, f);\n    \
    \    auto z1 = z_algo(rev(sub_a(l, md)));\n        auto z2 = z_algo(concat(sub_a(md,\
    \ r), sub_a(l, r)));\n        for (int i = md - 1; i >= l; i--) {\n          \
    \  int l1 = min(i - l, z1[md - i]);\n            int l2 = min(r - md, z2[(r -\
    \ l) - (md - i)]);\n            int le = i - l1, ri = md + l2, peri = md - i;\n\
    \            if (ri - le >= 2 * peri) runs[md - i].push_back({i - l1, md + l2});\n\
    \        }\n    }\n    \n    RunExec(Str _a) : a(_a) {\n        n = int(a.size());\n\
    \        runs.resize(n / 2 + 1);\n        reverse(a.begin(), a.end());\n     \
    \   run(0, n, 0);\n        for (auto& run : runs) {\n            for (auto& p\
    \ : run) {\n                tie(p.first, p.second) = make_pair(n - p.second, n\
    \ - p.first);\n            }\n        }\n        reverse(a.begin(), a.end());\n\
    \        run(0, n, 1);\n\n        set<pair<int, int>> vis;\n        for (int ph\
    \ = 1; ph <= n / 2; ph++) {\n            auto& run = runs[ph];\n            sort(run.begin(),\
    \ run.end(),\n                 [&](pair<int, int> lhs, pair<int, int> rhs) {\n\
    \                     if (lhs.first != rhs.first) return lhs.first < rhs.first;\n\
    \                     return lhs.second > rhs.second;\n                 });\n\
    \            V<pair<int, int>> res;\n            for (auto p : run) {\n      \
    \          if (!res.empty() && p.second <= res.back().second) continue;\n    \
    \            res.push_back(p);\n            }\n            run = res;\n      \
    \      res.clear();\n            for (auto p : run) {\n                if (vis.count(p))\
    \ continue;\n                vis.insert(p);\n                res.push_back(p);\n\
    \            }\n            run = res;\n        }\n    }\n};\n"
  dependsOn:
  - src/base.hpp
  - src/string/zalgo.hpp
  isVerificationFile: false
  path: src/string/run.hpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/run.test.cpp
documentation_of: src/string/run.hpp
layout: document
redirect_from:
- /library/src/string/run.hpp
- /library/src/string/run.hpp.html
title: src/string/run.hpp
---
