#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <random>

struct Random {
  private:
    std::mt19937_64 mt;

    // random choice from [0, upper]
    uint64_t next(uint64_t upper) {
        if (!(upper & (upper + 1))) {
            // b = 00..0011..11
            return mt() & upper;
        }
        int lg = 63 - __builtin_clzll(upper);
        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;
        while (true) {
            uint64_t r = mt() & mask;
            if (r <= upper)
                return r;
        }
    }

  public:
    Random() : mt() {}

    // random choice from [lower, upper]
    template <class T>
    T uniform(T lower, T upper) {
        assert(lower <= upper);
        return T(lower + next(uint64_t(upper - lower)));
    }

    bool uniform_bool() { return uniform(0, 1) == 1; }

    double uniform01() {
        uint64_t v = next(1ULL << 63);
        return double(v) / (1ULL << 63);
    }

    // generate random lower string that length = n
    std::string lower_string(size_t n) {
        std::string s = "";
        for (size_t i = 0; i < n; i++) {
            s += uniform('a', 'z');
        }
        return s;
    }

    // random shuffle
    template <class Iter>
    void shuffle(Iter first, Iter last) {
        int len = 0;
        // Reference and edit:
        // cpprefjp - C++日本語リファレンス
        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)
        for (auto it = first + 1; it != last; it++) {
            len++;
            int j = uniform(0, len - 1);
            if (j != len - 1)
                iter_swap(it, first + j);
        }
    }

    // generate random permutation that length = n
    std::vector<int> perm(int n) {
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        return idx;
    }
};
