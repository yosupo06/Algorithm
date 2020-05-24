#pragma once

#include "util/hash.hpp"

template <class K, class D, class H = Hasher<>> struct HashMap {
    using P = pair<unsigned char, K>;
    uint s, mask, filled;  // data.size() == 1 << s
    P* key;
    D* val;

    HashMap(uint _s = 4) : s(_s), mask((1U << s) - 1), filled(0) {
        key = new P[1 << s];
        val = new D[1 << s];
    }

    void rehash() {
        uint pmask = mask;
        P* pkey = key;
        D* pval = val;
        s++;
        mask = (1U << s) - 1;
        filled = 0;
        key = new P[1 << s];
        val = new D[1 << s];
        for (uint i = 0; i <= pmask; i++) {
            if (pkey[i].first == 1) {
                set(pkey[i].second, pval[i]);
            }
        }
        delete[] key;
        delete[] val;
    }

    D get(K k) {
        uint id = H::hash(k) & mask;
        while (key[id].first && key[id].second != k) id = (id + 1) & mask;
        if (key[id].first != 1 || key[id].second != k) return D();
        return val[id];
    }

    void set(K k, D x) {
        uint id = H::hash(k) & mask;
        while (key[id].first && key[id].second != k) id = (id + 1) & mask;
        if (key[id].first == 0) {
            filled++;
            if (filled * 2 > mask) {
                rehash();
                set(k, x);
                return;
            }
        }
        key[id] = {1, k};
        val[id] = x;
    }
};
