---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bitop.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"bitop.hpp\"\nstruct FastSet {\n    static constexpr\
    \ uint B = 64;\n    int n, lg;\n    VV<ull> seg;\n    FastSet(int _n) : n(_n)\
    \ {\n        do {\n            seg.push_back(V<ull>((_n + B - 1) / B));\n    \
    \        _n = (_n + B - 1) / B;\n        } while (_n > 1);\n        lg = int(seg.size());\n\
    \    }\n    bool operator[](int i) const {\n        return (seg[0][i / B] >> (i\
    \ % B) & 1) != 0;\n    }\n    void set(int i) {\n        for (int h = 0; h < lg;\
    \ h++) {\n            seg[h][i / B] |= 1ULL << (i % B);\n            i /= B;\n\
    \        }\n    }\n    void reset(int i) {\n        for (int h = 0; h < lg; h++)\
    \ {\n            seg[h][i / B] &= ~(1ULL << (i % B));\n            if (seg[h][i\
    \ / B]) break;\n            i /= B;\n        }\n    }\n    // x\u4EE5\u4E0A\u6700\
    \u5C0F\u306E\u8981\u7D20\n    int next(int i) {\n        for (int h = 0; h < lg;\
    \ h++) {\n            if (i / B == seg[h].size()) break;\n            ull d =\
    \ seg[h][i / B] >> (i % B);\n            if (!d) {\n                i = i / B\
    \ + 1;\n                continue;\n            }\n            // find\n      \
    \      i += bsf(d);\n            for (int g = h - 1; g >= 0; g--) {\n        \
    \        i *= B;\n                i += bsf(seg[g][i / B]);\n            }\n  \
    \          return i;\n        }\n        return n;\n    }\n    // x\u672A\u6E80\
    \u6700\u5927\u306E\u8981\u7D20\n    int prev(int i) {\n        i--;\n        for\
    \ (int h = 0; h < lg; h++) {\n            if (i == -1) break;\n            ull\
    \ d = seg[h][i / B] << (63 - i % 64);\n            if (!d) {\n               \
    \ i = i / B - 1;\n                continue;\n            }\n            // find\n\
    \            i += bsr(d) - (B - 1);\n            for (int g = h - 1; g >= 0; g--)\
    \ {\n                i *= B;\n                i += bsr(seg[g][i / B]);\n     \
    \       }\n            return i;\n        }\n        return -1;\n    }\n};\n"
  dependsOn:
  - src/bitop.hpp
  isVerificationFile: false
  path: src/datastructure/fastset.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/fastset.hpp
layout: document
redirect_from:
- /library/src/datastructure/fastset.hpp
- /library/src/datastructure/fastset.hpp.html
title: src/datastructure/fastset.hpp
---
