#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

uint64_t mix(uint64_t h) {
    h ^= h >> 23;
    h *= 0x2127599bf4325c37ULL;
    h ^= h >> 47;
    return h;
}

uint64_t hash_f(ull x) {
    const uint64_t m = 0x880355f21e6d1965ULL;
    return mix((m ^ mix(x)) * m);
}

template <class T> struct fasthash {};

template <> struct fasthash<int> {
    size_t operator()(int x) const { return hash_f(x); }
};
template <> struct fasthash<uint> {
    size_t operator()(uint x) const { return hash_f(x); }
};
template <> struct fasthash<ll> {
    size_t operator()(ll x) const { return hash_f(x); }
};
template <> struct fasthash<ull> {
    size_t operator()(ull x) const { return hash_f(x); }
};

template <class K, class D> using hashmap = gp_hash_table<K, D, fasthash<K>>;
