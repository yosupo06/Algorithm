#pragma once

#include "util/hash.hpp"

template <class K, class H = Hasher<>> struct HashSet {
    using P = pair<unsigned char, K>;
    uint s, mask, filled, sz;  // data.size() == 1 << s
    P* key;

    HashSet(uint _s = 2) : s(_s), mask((1U << s) - 1), filled(0), sz(0) {
        key = new P[1 << s];
    }

    void rehash() {
        uint pmask = mask;
        P* pkey = key;
        s++;
        mask = (1U << s) - 1;
        filled = 0;
        sz = 0;
        key = new P[1 << s];
        for (uint i = 0; i <= pmask; i++) {
            if (pkey[i].first == 1) {
                insert(pkey[i].second);
            }
        }
        delete[] pkey;
    }

    bool count(K k) {
        uint id = H::hash(k) & mask;
        int gc = 0;
        while (key[id].first && key[id].second != k) {
            gc++;
            id = (id + 1) & mask;
        }
        if (key[id].first != 1 || key[id].second != k) return false;
        return true;
    }

    void insert(K k) {
        uint id = H::hash(k) & mask;
        while (key[id].first && key[id].second != k) id = (id + 1) & mask;
        if (key[id].first == 0) {
            filled++;
            if (filled * 2 > mask) {
                rehash();
                insert(k);
                return;
            }
        }
        if (key[id].first != 1) sz++;
        key[id] = {1, k};
    }

    bool erase(K k) {
        uint id = H::hash(k) & mask;
        while (key[id].first && key[id].second != k) id = (id + 1) & mask;
        if (key[id].first != 1) return false;
        sz--;
        key[id].first = 2;
        return true;
    }

    size_t size() const {
        return sz;
    }

    V<int> to_vec() const {
        V<int> result;
        for (uint i = 0; i <= mask; i++) {
            if (key[i].first == 1) {
                result.push_back(key[i].second);
            }
        }
        return result;
    }
};
