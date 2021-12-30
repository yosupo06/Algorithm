---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/datastructure/bitvector.hpp
    title: src/datastructure/bitvector.hpp
  - icon: ':warning:'
    path: src/datastructure/fastset.hpp
    title: src/datastructure/fastset.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/dynamicmodint.hpp
    title: src/math/dynamicmodint.hpp
  - icon: ':warning:'
    path: src/math/frac.hpp
    title: src/math/frac.hpp
  - icon: ':warning:'
    path: src/math/matrix.hpp
    title: src/math/matrix.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/nft.hpp
    title: src/math/nft.hpp
  - icon: ':warning:'
    path: src/math/primitive.hpp
    title: src/math/primitive.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/comb.test.cpp
    title: src/comb.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/inv_of_formal_power_series.test.cpp
    title: src/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/modint.test.cpp
    title: src/modint.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/nft_convolution.test.cpp
    title: src/nft_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: '#line 2 "src/bitop.hpp"

    // bit op

    int popcnt(uint x) { return __builtin_popcount(x); }

    int popcnt(ull x) { return __builtin_popcountll(x); }

    int bsr(uint x) { return 31 - __builtin_clz(x); }

    int bsr(ull x) { return 63 - __builtin_clzll(x); }

    int bsf(uint x) { return __builtin_ctz(x); }

    int bsf(ull x) { return __builtin_ctzll(x); }

    '
  code: '#pragma once

    // bit op

    int popcnt(uint x) { return __builtin_popcount(x); }

    int popcnt(ull x) { return __builtin_popcountll(x); }

    int bsr(uint x) { return 31 - __builtin_clz(x); }

    int bsr(ull x) { return 63 - __builtin_clzll(x); }

    int bsf(uint x) { return __builtin_ctz(x); }

    int bsf(ull x) { return __builtin_ctzll(x); }

    '
  dependsOn: []
  isVerificationFile: false
  path: src/bitop.hpp
  requiredBy:
  - src/math/nft.hpp
  - src/math/primitive.hpp
  - src/math/matrix.hpp
  - src/math/dynamicmodint.hpp
  - src/math/frac.hpp
  - src/datastructure/bitvector.hpp
  - src/datastructure/fastset.hpp
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/inv_of_formal_power_series.test.cpp
  - src/modint.test.cpp
  - src/nft_convolution.test.cpp
  - src/comb.test.cpp
documentation_of: src/bitop.hpp
layout: document
redirect_from:
- /library/src/bitop.hpp
- /library/src/bitop.hpp.html
title: src/bitop.hpp
---
