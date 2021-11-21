---
data:
  _extendedDependsOn: []
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
  - icon: ':heavy_check_mark:'
    path: src/math/poly.hpp
    title: src/math/poly.hpp
  - icon: ':heavy_check_mark:'
    path: src/string/rollinghash.hpp
    title: src/string/rollinghash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/hash.hpp
    title: src/util/hash.hpp
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
    path: src/inv_of_formal_power_series.test.cpp
    title: src/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/modint61.test.cpp
    title: src/modint61.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/rollinghash_zalgo.test.cpp
    title: src/rollinghash_zalgo.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://xoshiro.di.unimi.it/splitmix64.c
    - http://xoshiro.di.unimi.it/xoshiro256starstar.c
    - https://cpprefjp.github.io/reference/algorithm/shuffle.html)
  bundledCode: "#line 2 \"src/util/random.hpp\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include\
    \ <numeric>\n#include <random>\n#include <set>\n#include <vector>\n\nstruct Random\
    \ {\n  private:\n    // Use xoshiro256**\n    // Refereces: http://xoshiro.di.unimi.it/xoshiro256starstar.c\n\
    \    static uint64_t rotl(const uint64_t x, int k) {\n        return (x << k)\
    \ | (x >> (64 - k));\n    }\n\n    std::array<uint64_t, 4> s;\n\n    uint64_t\
    \ next() {\n        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;\n\n\
    \        const uint64_t t = s[1] << 17;\n\n        s[2] ^= s[0];\n        s[3]\
    \ ^= s[1];\n        s[1] ^= s[2];\n        s[0] ^= s[3];\n\n        s[2] ^= t;\n\
    \n        s[3] = rotl(s[3], 45);\n\n        return result_starstar;\n    }\n\n\
    \    // random choice from [0, upper]\n    uint64_t next(uint64_t upper) {\n \
    \       if (!(upper & (upper + 1))) {\n            // b = 00..0011..11\n     \
    \       return next() & upper;\n        }\n        int lg = 63 - __builtin_clzll(upper);\n\
    \        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;\n      \
    \  while (true) {\n            uint64_t r = next() & mask;\n            if (r\
    \ <= upper) return r;\n        }\n    }\n\n  public:\n    Random(uint64_t seed\
    \ = 0) {\n        // Use splitmix64\n        // Reference: http://xoshiro.di.unimi.it/splitmix64.c\n\
    \        for (int i = 0; i < 4; i++) {\n            uint64_t z = (seed += 0x9e3779b97f4a7c15);\n\
    \            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z = (z ^ (z\
    \ >> 27)) * 0x94d049bb133111eb;\n            s[i] = z ^ (z >> 31);\n        }\n\
    \    }\n\n    // random choice from [lower, upper]\n    template <class T> T uniform(T\
    \ lower, T upper) {\n        assert(lower <= upper);\n        return T(lower +\
    \ next(uint64_t(upper - lower)));\n    }\n\n    bool uniform_bool() { return uniform(0,\
    \ 1) == 1; }\n\n    double uniform01() {\n        uint64_t v = next(1ULL << 63);\n\
    \        return double(v) / (1ULL << 63);\n    }\n\n    template <class T> std::pair<T,\
    \ T> uniform_pair(T lower, T upper) {\n        assert(upper - lower >= 1);\n \
    \       T a, b;\n        do {\n            a = uniform(lower, upper);\n      \
    \      b = uniform(lower, upper);\n        } while (a == b);\n        if (a >\
    \ b) std::swap(a, b);\n        return {a, b};\n    }\n\n    // generate random\
    \ lower string that length = n\n    std::string lower_string(size_t n) {\n   \
    \     std::string res = \"\";\n        for (size_t i = 0; i < n; i++) {\n    \
    \        res += uniform('a', 'z');\n        }\n        return res;\n    }\n\n\
    \    // random shuffle\n    template <class Iter> void shuffle(Iter first, Iter\
    \ last) {\n        if (first == last) return;\n        // Reference and edit:\n\
    \        // cpprefjp - C++\u65E5\u672C\u8A9E\u30EA\u30D5\u30A1\u30EC\u30F3\u30B9\
    \n        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)\n \
    \       int len = 1;\n        for (auto it = first + 1; it != last; it++) {\n\
    \            len++;\n            int j = uniform(0, len - 1);\n            if\
    \ (j != len - 1) iter_swap(it, first + j);\n        }\n    }\n\n    // generate\
    \ random permutation that length = n\n    template <class T> std::vector<T> perm(size_t\
    \ n) {\n        std::vector<T> idx(n);\n        std::iota(idx.begin(), idx.end(),\
    \ T(0));\n        shuffle(idx.begin(), idx.end());\n        return idx;\n    }\n\
    \n    template <class T> std::vector<T> choice(size_t n, T lower, T upper) {\n\
    \        assert(n <= upper - lower + 1);\n        std::set<T> res;\n        while\
    \ (res.size() < n) res.insert(uniform(lower, upper));\n        return {res.begin(),\
    \ res.end()};\n    }\n};\nRandom& global_gen() {\n    static Random gen;\n   \
    \ return gen;\n}\nRandom get_random_gen() {\n    return Random(chrono::steady_clock::now().time_since_epoch().count());\n\
    }\nRandom& global_runtime_gen() {\n    static Random gen = get_random_gen();\n\
    \    return gen;\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <chrono>\n#include <cstdint>\n#include <numeric>\n#include <random>\n\
    #include <set>\n#include <vector>\n\nstruct Random {\n  private:\n    // Use xoshiro256**\n\
    \    // Refereces: http://xoshiro.di.unimi.it/xoshiro256starstar.c\n    static\
    \ uint64_t rotl(const uint64_t x, int k) {\n        return (x << k) | (x >> (64\
    \ - k));\n    }\n\n    std::array<uint64_t, 4> s;\n\n    uint64_t next() {\n \
    \       const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;\n\n        const\
    \ uint64_t t = s[1] << 17;\n\n        s[2] ^= s[0];\n        s[3] ^= s[1];\n \
    \       s[1] ^= s[2];\n        s[0] ^= s[3];\n\n        s[2] ^= t;\n\n       \
    \ s[3] = rotl(s[3], 45);\n\n        return result_starstar;\n    }\n\n    // random\
    \ choice from [0, upper]\n    uint64_t next(uint64_t upper) {\n        if (!(upper\
    \ & (upper + 1))) {\n            // b = 00..0011..11\n            return next()\
    \ & upper;\n        }\n        int lg = 63 - __builtin_clzll(upper);\n       \
    \ uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;\n        while\
    \ (true) {\n            uint64_t r = next() & mask;\n            if (r <= upper)\
    \ return r;\n        }\n    }\n\n  public:\n    Random(uint64_t seed = 0) {\n\
    \        // Use splitmix64\n        // Reference: http://xoshiro.di.unimi.it/splitmix64.c\n\
    \        for (int i = 0; i < 4; i++) {\n            uint64_t z = (seed += 0x9e3779b97f4a7c15);\n\
    \            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z = (z ^ (z\
    \ >> 27)) * 0x94d049bb133111eb;\n            s[i] = z ^ (z >> 31);\n        }\n\
    \    }\n\n    // random choice from [lower, upper]\n    template <class T> T uniform(T\
    \ lower, T upper) {\n        assert(lower <= upper);\n        return T(lower +\
    \ next(uint64_t(upper - lower)));\n    }\n\n    bool uniform_bool() { return uniform(0,\
    \ 1) == 1; }\n\n    double uniform01() {\n        uint64_t v = next(1ULL << 63);\n\
    \        return double(v) / (1ULL << 63);\n    }\n\n    template <class T> std::pair<T,\
    \ T> uniform_pair(T lower, T upper) {\n        assert(upper - lower >= 1);\n \
    \       T a, b;\n        do {\n            a = uniform(lower, upper);\n      \
    \      b = uniform(lower, upper);\n        } while (a == b);\n        if (a >\
    \ b) std::swap(a, b);\n        return {a, b};\n    }\n\n    // generate random\
    \ lower string that length = n\n    std::string lower_string(size_t n) {\n   \
    \     std::string res = \"\";\n        for (size_t i = 0; i < n; i++) {\n    \
    \        res += uniform('a', 'z');\n        }\n        return res;\n    }\n\n\
    \    // random shuffle\n    template <class Iter> void shuffle(Iter first, Iter\
    \ last) {\n        if (first == last) return;\n        // Reference and edit:\n\
    \        // cpprefjp - C++\u65E5\u672C\u8A9E\u30EA\u30D5\u30A1\u30EC\u30F3\u30B9\
    \n        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)\n \
    \       int len = 1;\n        for (auto it = first + 1; it != last; it++) {\n\
    \            len++;\n            int j = uniform(0, len - 1);\n            if\
    \ (j != len - 1) iter_swap(it, first + j);\n        }\n    }\n\n    // generate\
    \ random permutation that length = n\n    template <class T> std::vector<T> perm(size_t\
    \ n) {\n        std::vector<T> idx(n);\n        std::iota(idx.begin(), idx.end(),\
    \ T(0));\n        shuffle(idx.begin(), idx.end());\n        return idx;\n    }\n\
    \n    template <class T> std::vector<T> choice(size_t n, T lower, T upper) {\n\
    \        assert(n <= upper - lower + 1);\n        std::set<T> res;\n        while\
    \ (res.size() < n) res.insert(uniform(lower, upper));\n        return {res.begin(),\
    \ res.end()};\n    }\n};\nRandom& global_gen() {\n    static Random gen;\n   \
    \ return gen;\n}\nRandom get_random_gen() {\n    return Random(chrono::steady_clock::now().time_since_epoch().count());\n\
    }\nRandom& global_runtime_gen() {\n    static Random gen = get_random_gen();\n\
    \    return gen;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/util/random.hpp
  requiredBy:
  - src/math/poly.hpp
  - src/util/hash.hpp
  - src/string/rollinghash.hpp
  - src/graph/balancedseparator.hpp
  - src/graph/treedecomp.hpp
  - src/datastructure/hashset.hpp
  - src/datastructure/hashmap.hpp
  timestamp: '2020-05-24 19:01:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/treedecomp_width2.test.cpp
  - src/rollinghash_zalgo.test.cpp
  - src/hashset.test.cpp
  - src/modint61.test.cpp
  - src/hashmap.test.cpp
  - src/inv_of_formal_power_series.test.cpp
  - src/hashset_hashmap.test.cpp
  - src/hashmap_remove.test.cpp
documentation_of: src/util/random.hpp
layout: document
redirect_from:
- /library/src/util/random.hpp
- /library/src/util/random.hpp.html
title: src/util/random.hpp
---
