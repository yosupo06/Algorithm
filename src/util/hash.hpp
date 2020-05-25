#pragma once

#include "base.hpp"
#include "util/random.hpp"

// Reference: Lemire, Daniel., and Owen, Kaser. "Strongly Universal String Hashing Is Fast."
template <uint N = 4> struct Hasher {
  private:
    static ull offset;
    static array<ull, N> seed;

    template <uint I = 0>
    struct Encoder {
        ull now = offset;
        Encoder<I + 1> update(uint x) {
            return Encoder<I + 1>{now + x * seed[I]};
        }
        Encoder<I + 1> update(int x) {
            return update(uint(x));
        }
        Encoder<I + 2> update(ull x) {
            return Encoder<I + 2>{now + uint(x) * seed[I] + (x >> 32) * seed[I + 1]};
        }
        Encoder<I + 2> update(ll x) {
            return update(ll(x));
        }
        uint digest() const {
            static_assert(I <= N);
            return uint(now >> 32);
        }
    };

  public:
    static uint hash(uint x) { return Encoder<>{}.update(x).digest(); }
    static uint hash(ull x) { return Encoder<>{}.update(x).digest(); }
    static uint hash(int x) { return hash(uint(x)); }
    static uint hash(ll x) { return hash(ull(x)); }
    template <class T, class U> static uint hash(const pair<T, U>& p) {
        return Encoder<>{}.update(p.first).update(p.second).digest();
    }
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
