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
    path: src/hashset.test.cpp
    title: src/hashset.test.cpp
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
  code: "#pragma once\n\n#include \"util/hash.hpp\"\n\ntemplate <class K, class H\
    \ = Hasher<>> struct HashSet {\n    using P = pair<unsigned char, K>;\n    uint\
    \ s, mask, filled, sz;  // data.size() == 1 << s\n    P* key;\n\n    HashSet(uint\
    \ _s = 2) : s(_s), mask((1U << s) - 1), filled(0), sz(0) {\n        key = new\
    \ P[1 << s];\n    }\n\n    void rehash() {\n        uint pmask = mask;\n     \
    \   P* pkey = key;\n        s++;\n        mask = (1U << s) - 1;\n        filled\
    \ = 0;\n        sz = 0;\n        key = new P[1 << s];\n        for (uint i = 0;\
    \ i <= pmask; i++) {\n            if (pkey[i].first == 1) {\n                insert(pkey[i].second);\n\
    \            }\n        }\n        delete[] pkey;\n    }\n\n    bool count(K k)\
    \ {\n        uint id = H::hash(k) & mask;\n        int gc = 0;\n        while\
    \ (key[id].first && key[id].second != k) {\n            gc++;\n            id\
    \ = (id + 1) & mask;\n        }\n        if (key[id].first != 1 || key[id].second\
    \ != k) return false;\n        return true;\n    }\n\n    void insert(K k) {\n\
    \        uint id = H::hash(k) & mask;\n        while (key[id].first && key[id].second\
    \ != k) id = (id + 1) & mask;\n        if (key[id].first == 0) {\n           \
    \ filled++;\n            if (filled * 2 > mask) {\n                rehash();\n\
    \                insert(k);\n                return;\n            }\n        }\n\
    \        if (key[id].first != 1) sz++;\n        key[id] = {1, k};\n    }\n\n \
    \   bool erase(K k) {\n        uint id = H::hash(k) & mask;\n        while (key[id].first\
    \ && key[id].second != k) id = (id + 1) & mask;\n        if (key[id].first !=\
    \ 1) return false;\n        sz--;\n        key[id].first = 2;\n        return\
    \ true;\n    }\n\n    size_t size() const {\n        return sz;\n    }\n\n   \
    \ V<int> to_vec() const {\n        V<int> result;\n        for (uint i = 0; i\
    \ <= mask; i++) {\n            if (key[i].first == 1) {\n                result.push_back(key[i].second);\n\
    \            }\n        }\n        return result;\n    }\n};\n"
  dependsOn:
  - src/util/hash.hpp
  - src/base.hpp
  - src/util/random.hpp
  isVerificationFile: false
  path: src/datastructure/hashset.hpp
  requiredBy:
  - src/graph/treedecomp.hpp
  - src/graph/balancedseparator.hpp
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/hashset.test.cpp
  - src/treedecomp_width2.test.cpp
  - src/hashset_hashmap.test.cpp
documentation_of: src/datastructure/hashset.hpp
layout: document
redirect_from:
- /library/src/datastructure/hashset.hpp
- /library/src/datastructure/hashset.hpp.html
title: src/datastructure/hashset.hpp
---
