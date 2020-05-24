#pragma once

#include "base.hpp"
#include "util/random.hpp"

// Reference: Lemire, Daniel., and Owen, Kaser. "Strongly Universal String Hashing Is Fast."
template <uint N = 4> struct Hasher {
    static ull offset;
    static array<ull, N> seed;

    static uint hash(uint x) { return (offset + x * seed[0]) >> 32; }
    static uint hash(ull x) {
        return (offset + uint(x) * seed[0] + (x >> 32) * seed[1]) >> 32;
    }
    static uint hash(int x) { return hash(uint(x)); }
    static uint hash(ll x) { return hash(ull(x)); }
};

template <uint N>
ull Hasher<N>::offset = global_runtime_gen().uniform(0ULL, ull(-1));

template <uint N>
array<ull, N> Hasher<N>::seed = []() {
    array<ull, N> seed;
    for (uint i = 0; i < N; i++) {
        seed[i] = global_runtime_gen().uniform(0ULL, ull(-1));
    }
    return seed;
}();
