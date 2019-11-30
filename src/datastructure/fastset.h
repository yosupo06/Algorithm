#pragma once

#include "bitop.h"
struct FastSet {
    static constexpr uint B = 64;
    int n, lg;
    VV<ull> seg;
    FastSet(int _n) : n(_n) {
        do {
            seg.push_back(V<ull>((_n + B - 1) / B));
            _n = (_n + B - 1) / B;
        } while (_n > 1);
        lg = seg.size();
    }
    bool operator[](int i) const {
        return (seg[0][i / B] >> (i % B) & 1) != 0;
    }
    void set(int i) {
        for (int h = 0; h < lg; h++) {
            seg[h][i / B] |= 1ULL << (i % B);
            i /= B;
        }
    }
    void reset(int i) {
        for (int h = 0; h < lg; h++) {
            seg[h][i / B] &= ~(1ULL << (i % B));
            if (seg[h][i / B]) break;
            i /= B;
        }
    }
    // x以上最小の要素
    int next(int i) {
        for (int h = 0; h < lg; h++) {
            if (i / B == seg[h].size()) break;
            ull d = seg[h][i / B] >> (i % B);
            if (!d) {
                i = i / B + 1;
                continue;
            }
            // find
            i += bsf(d);
            for (int g = h - 1; g >= 0; g--) {
                i *= B;
                i += bsf(seg[g][i / B]);
            }
            return i;
        }
        return n;
    }
    // x未満最大の要素
    int prev(int i) {
        i--;
        for (int h = 0; h < lg; h++) {
            if (i == -1) break;
            ull d = seg[h][i / B] << (63 - i % 64);
            if (!d) {
                i = i / B - 1;
                continue;
            }
            // find
            i += bsr(d) - (B - 1);
            for (int g = h - 1; g >= 0; g--) {
                i *= B;
                i += bsr(seg[g][i / B]);
            }
            return i;
        }
        return -1;
    }
};
