---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: src/util/random.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#6433a1a19c7364347102f741d8b9cffd">src/util</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/util/random.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-24 19:01:57+09:00




## Required by

* :heavy_check_mark: <a href="../datastructure/hashmap.hpp.html">src/datastructure/hashmap.hpp</a>
* :heavy_check_mark: <a href="../datastructure/hashset.hpp.html">src/datastructure/hashset.hpp</a>
* :heavy_check_mark: <a href="../graph/treedecomp.hpp.html">src/graph/treedecomp.hpp</a>
* :heavy_check_mark: <a href="../math/poly.hpp.html">src/math/poly.hpp</a>
* :heavy_check_mark: <a href="../string/rollinghash.hpp.html">src/string/rollinghash.hpp</a>
* :heavy_check_mark: <a href="hash.hpp.html">src/util/hash.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/hashmap.test.cpp.html">src/hashmap.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hashmap_remove.test.cpp.html">src/hashmap_remove.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hashset.test.cpp.html">src/hashset.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hashset_hashmap.test.cpp.html">src/hashset_hashmap.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/inv_of_formal_power_series.test.cpp.html">src/inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/modint61.test.cpp.html">src/modint61.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/rollinghash_zalgo.test.cpp.html">src/rollinghash_zalgo.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/treedecomp_width2.test.cpp.html">src/treedecomp_width2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <numeric>
#include <random>
#include <set>
#include <vector>

struct Random {
  private:
    // Use xoshiro256**
    // Refereces: http://xoshiro.di.unimi.it/xoshiro256starstar.c
    static uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    std::array<uint64_t, 4> s;

    uint64_t next() {
        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;

        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;

        s[3] = rotl(s[3], 45);

        return result_starstar;
    }

    // random choice from [0, upper]
    uint64_t next(uint64_t upper) {
        if (!(upper & (upper + 1))) {
            // b = 00..0011..11
            return next() & upper;
        }
        int lg = 63 - __builtin_clzll(upper);
        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;
        while (true) {
            uint64_t r = next() & mask;
            if (r <= upper) return r;
        }
    }

  public:
    Random(uint64_t seed = 0) {
        // Use splitmix64
        // Reference: http://xoshiro.di.unimi.it/splitmix64.c
        for (int i = 0; i < 4; i++) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s[i] = z ^ (z >> 31);
        }
    }

    // random choice from [lower, upper]
    template <class T> T uniform(T lower, T upper) {
        assert(lower <= upper);
        return T(lower + next(uint64_t(upper - lower)));
    }

    bool uniform_bool() { return uniform(0, 1) == 1; }

    double uniform01() {
        uint64_t v = next(1ULL << 63);
        return double(v) / (1ULL << 63);
    }

    template <class T> std::pair<T, T> uniform_pair(T lower, T upper) {
        assert(upper - lower >= 1);
        T a, b;
        do {
            a = uniform(lower, upper);
            b = uniform(lower, upper);
        } while (a == b);
        if (a > b) std::swap(a, b);
        return {a, b};
    }

    // generate random lower string that length = n
    std::string lower_string(size_t n) {
        std::string res = "";
        for (size_t i = 0; i < n; i++) {
            res += uniform('a', 'z');
        }
        return res;
    }

    // random shuffle
    template <class Iter> void shuffle(Iter first, Iter last) {
        if (first == last) return;
        // Reference and edit:
        // cpprefjp - C++日本語リファレンス
        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)
        int len = 1;
        for (auto it = first + 1; it != last; it++) {
            len++;
            int j = uniform(0, len - 1);
            if (j != len - 1) iter_swap(it, first + j);
        }
    }

    // generate random permutation that length = n
    template <class T> std::vector<T> perm(size_t n) {
        std::vector<T> idx(n);
        std::iota(idx.begin(), idx.end(), T(0));
        shuffle(idx.begin(), idx.end());
        return idx;
    }

    template <class T> std::vector<T> choice(size_t n, T lower, T upper) {
        assert(n <= upper - lower + 1);
        std::set<T> res;
        while (res.size() < n) res.insert(uniform(lower, upper));
        return {res.begin(), res.end()};
    }
};
Random& global_gen() {
    static Random gen;
    return gen;
}
Random get_random_gen() {
    return Random(chrono::steady_clock::now().time_since_epoch().count());
}
Random& global_runtime_gen() {
    static Random gen = get_random_gen();
    return gen;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/util/random.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <numeric>
#include <random>
#include <set>
#include <vector>

struct Random {
  private:
    // Use xoshiro256**
    // Refereces: http://xoshiro.di.unimi.it/xoshiro256starstar.c
    static uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    std::array<uint64_t, 4> s;

    uint64_t next() {
        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;

        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;

        s[3] = rotl(s[3], 45);

        return result_starstar;
    }

    // random choice from [0, upper]
    uint64_t next(uint64_t upper) {
        if (!(upper & (upper + 1))) {
            // b = 00..0011..11
            return next() & upper;
        }
        int lg = 63 - __builtin_clzll(upper);
        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;
        while (true) {
            uint64_t r = next() & mask;
            if (r <= upper) return r;
        }
    }

  public:
    Random(uint64_t seed = 0) {
        // Use splitmix64
        // Reference: http://xoshiro.di.unimi.it/splitmix64.c
        for (int i = 0; i < 4; i++) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s[i] = z ^ (z >> 31);
        }
    }

    // random choice from [lower, upper]
    template <class T> T uniform(T lower, T upper) {
        assert(lower <= upper);
        return T(lower + next(uint64_t(upper - lower)));
    }

    bool uniform_bool() { return uniform(0, 1) == 1; }

    double uniform01() {
        uint64_t v = next(1ULL << 63);
        return double(v) / (1ULL << 63);
    }

    template <class T> std::pair<T, T> uniform_pair(T lower, T upper) {
        assert(upper - lower >= 1);
        T a, b;
        do {
            a = uniform(lower, upper);
            b = uniform(lower, upper);
        } while (a == b);
        if (a > b) std::swap(a, b);
        return {a, b};
    }

    // generate random lower string that length = n
    std::string lower_string(size_t n) {
        std::string res = "";
        for (size_t i = 0; i < n; i++) {
            res += uniform('a', 'z');
        }
        return res;
    }

    // random shuffle
    template <class Iter> void shuffle(Iter first, Iter last) {
        if (first == last) return;
        // Reference and edit:
        // cpprefjp - C++日本語リファレンス
        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)
        int len = 1;
        for (auto it = first + 1; it != last; it++) {
            len++;
            int j = uniform(0, len - 1);
            if (j != len - 1) iter_swap(it, first + j);
        }
    }

    // generate random permutation that length = n
    template <class T> std::vector<T> perm(size_t n) {
        std::vector<T> idx(n);
        std::iota(idx.begin(), idx.end(), T(0));
        shuffle(idx.begin(), idx.end());
        return idx;
    }

    template <class T> std::vector<T> choice(size_t n, T lower, T upper) {
        assert(n <= upper - lower + 1);
        std::set<T> res;
        while (res.size() < n) res.insert(uniform(lower, upper));
        return {res.begin(), res.end()};
    }
};
Random& global_gen() {
    static Random gen;
    return gen;
}
Random get_random_gen() {
    return Random(chrono::steady_clock::now().time_since_epoch().count());
}
Random& global_runtime_gen() {
    static Random gen = get_random_gen();
    return gen;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

