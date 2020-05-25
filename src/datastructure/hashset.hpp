#pragma once

#include "util/hash.hpp"

template <class K, class H = Hasher<>> struct HashSet {
    using P = pair<unsigned char, K>;
    uint s, mask, filled;  // data.size() == 1 << s
    P* key;

    HashSet(uint _s = 2) : s(_s), mask((1U << s) - 1), filled(0) {
        key = new P[1 << s];
    }

    void rehash() {
        uint pmask = mask;
        P* pkey = key;
        s++;
        mask = (1U << s) - 1;
        filled = 0;
        key = new P[1 << s];
        for (uint i = 0; i <= pmask; i++) {
            if (pkey[i].first == 1) {
                set(pkey[i].second);
            }
        }
        delete[] pkey;
    }

    bool get(K k) {
        uint id = H::hash(k) & mask;
        int gc = 0;
        while (key[id].first && key[id].second != k) {
            gc++;
            id = (id + 1) & mask;
        }
        if (key[id].first != 1 || key[id].second != k) return false;
        return true;
    }

    void set(K k) {
        uint id = H::hash(k) & mask;
        while (key[id].first && key[id].second != k) id = (id + 1) & mask;
        if (key[id].first == 0) {
            filled++;
            if (filled * 2 > mask) {
                rehash();
                set(k);
                return;
            }
        }
        key[id] = {1, k};
    }

    bool reset(K k) {
        uint id = H::hash(k) & mask;
        while (key[id].first && key[id].second != k) id = (id + 1) & mask;
        if (key[id].first != 1) return false;
        key[id].first = 2;
        return true;
    }
};
