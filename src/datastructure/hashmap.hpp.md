---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/hash.hpp
    title: src/util/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/graph/balancedseparator.hpp
    title: src/graph/balancedseparator.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/treedecomp.hpp
    title: src/graph/treedecomp.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/hashmap.test.cpp
    title: src/hashmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hashmap_remove.test.cpp
    title: src/hashmap_remove.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hashset_hashmap.test.cpp
    title: src/hashset_hashmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: util/hash.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n#include \"util/hash.hpp\"\n\ntemplate <class K, class D,\
    \ class H = Hasher<>> struct HashMap {\n    using P = pair<unsigned char, K>;\n\
    \    uint s, mask, filled;  // data.size() == 1 << s\n    P* key;\n    D* val;\n\
    \n    HashMap(uint _s = 2) : s(_s), mask((1U << s) - 1), filled(0) {\n       \
    \ key = new P[1 << s];\n        val = new D[1 << s];\n    }\n\n    void rehash()\
    \ {\n        uint pmask = mask;\n        P* pkey = key;\n        D* pval = val;\n\
    \        s++;\n        mask = (1U << s) - 1;\n        filled = 0;\n        key\
    \ = new P[1 << s];\n        val = new D[1 << s];\n        for (uint i = 0; i <=\
    \ pmask; i++) {\n            if (pkey[i].first == 1) {\n                set(pkey[i].second,\
    \ pval[i]);\n            }\n        }\n        delete[] pkey;\n        delete[]\
    \ pval;\n    }\n\n    D get(K k) {\n        uint id = H::hash(k) & mask;\n   \
    \     int gc = 0;\n        while (key[id].first && key[id].second != k) {\n  \
    \          gc++;\n            id = (id + 1) & mask;\n        }\n        if (key[id].first\
    \ != 1 || key[id].second != k) return D();\n        return val[id];\n    }\n\n\
    \    void set(K k, D x) {\n        uint id = H::hash(k) & mask;\n        while\
    \ (key[id].first && key[id].second != k) id = (id + 1) & mask;\n        if (key[id].first\
    \ == 0) {\n            filled++;\n            if (filled * 2 > mask) {\n     \
    \           rehash();\n                set(k, x);\n                return;\n \
    \           }\n        }\n        key[id] = {1, k};\n        val[id] = x;\n  \
    \  }\n\n    bool remove(K k) {\n        uint id = H::hash(k) & mask;\n       \
    \ while (key[id].first && key[id].second != k) id = (id + 1) & mask;\n       \
    \ if (key[id].first != 1) return false;\n        key[id].first = 2;\n        return\
    \ true;\n    }\n};\n"
  dependsOn:
  - src/util/hash.hpp
  - src/base.hpp
  - src/util/random.hpp
  isVerificationFile: false
  path: src/datastructure/hashmap.hpp
  requiredBy:
  - src/graph/treedecomp.hpp
  - src/graph/balancedseparator.hpp
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/hashmap_remove.test.cpp
  - src/treedecomp_width2.test.cpp
  - src/hashset_hashmap.test.cpp
  - src/hashmap.test.cpp
documentation_of: src/datastructure/hashmap.hpp
layout: document
redirect_from:
- /library/src/datastructure/hashmap.hpp
- /library/src/datastructure/hashmap.hpp.html
title: src/datastructure/hashmap.hpp
---
