---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashmap.hpp
    title: src/datastructure/hashmap.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashset.hpp
    title: src/datastructure/hashset.hpp
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
    path: src/hashset.test.cpp
    title: src/hashset.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hashset_hashmap.test.cpp
    title: src/hashset_hashmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
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
  code: "#pragma once\n\n#include \"base.hpp\"\n#include \"util/random.hpp\"\n\n//\
    \ Reference: Lemire, Daniel., and Owen, Kaser. \"Strongly Universal String Hashing\
    \ Is Fast.\"\ntemplate <uint N = 100> struct Hasher {\n  private:\n    static\
    \ ull offset;\n    static array<ull, N> seed;\n\n    template <uint I = 0>\n \
    \   struct Encoder {\n        ull now = offset;\n        Encoder<I + 1> update(uint\
    \ x) {\n            return Encoder<I + 1>{now + x * seed[I]};\n        }\n   \
    \     Encoder<I + 1> update(int x) {\n            return update(uint(x));\n  \
    \      }\n        Encoder<I + 2> update(ull x) {\n            return Encoder<I\
    \ + 2>{now + uint(x) * seed[I] + (x >> 32) * seed[I + 1]};\n        }\n      \
    \  Encoder<I + 2> update(ll x) {\n            return update(ll(x));\n        }\n\
    \        uint digest() const {\n            static_assert(I <= N);\n         \
    \   return uint(now >> 32);\n        }\n    };\n\n  public:\n    static uint hash(uint\
    \ x) { return Encoder<>{}.update(x).digest(); }\n    static uint hash(ull x) {\
    \ return Encoder<>{}.update(x).digest(); }\n    static uint hash(int x) { return\
    \ hash(uint(x)); }\n    static uint hash(ll x) { return hash(ull(x)); }\n    template\
    \ <class T, class U> static uint hash(const pair<T, U>& p) {\n        return Encoder<>{}.update(p.first).update(p.second).digest();\n\
    \    }\n};\n\ntemplate <uint N>\null Hasher<N>::offset = global_runtime_gen().uniform(0ULL,\
    \ ull(-1));\n\ntemplate <uint N>\narray<ull, N> Hasher<N>::seed = []() {\n   \
    \ array<ull, N> seed;\n    for (uint i = 0; i < N; i++) {\n        seed[i] = global_runtime_gen().uniform(0ULL,\
    \ ull(-1));\n    }\n    return seed;\n}();\n"
  dependsOn:
  - src/base.hpp
  - src/util/random.hpp
  isVerificationFile: false
  path: src/util/hash.hpp
  requiredBy:
  - src/graph/balancedseparator.hpp
  - src/graph/treedecomp.hpp
  - src/datastructure/hashmap.hpp
  - src/datastructure/hashset.hpp
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/treedecomp_width2.test.cpp
  - src/hashmap_remove.test.cpp
  - src/hashmap.test.cpp
  - src/hashset_hashmap.test.cpp
  - src/hashset.test.cpp
documentation_of: src/util/hash.hpp
layout: document
redirect_from:
- /library/src/util/hash.hpp
- /library/src/util/hash.hpp.html
title: src/util/hash.hpp
---
