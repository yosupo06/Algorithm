#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

static inline uint64_t mix(uint64_t h) {
    h ^= h >> 23;
    h *= 0x2127599bf4325c37ULL;
    h ^= h >> 47;
    return h;
}

ull hash_f(ull x) {
    const uint64_t    m = 0x880355f21e6d1965ULL;
    return mix((m ^ mix(x)) * m);
}

struct fasthash {
    ull operator()(ll x) const { return hash_f(x); }
};


template <class K, class D>
using hashmap = gp_hash_table<K, D, fasthash>;
