struct FastSet {
    static constexpr size_t B = 64;
    size_t n, lg;
    VV<ull> seg;
    FastSet(size_t _n) : n(_n) {
        do {
            seg.push_back(V<ull>((_n + B - 1) / B));
            _n = (_n + B - 1) / B;
        } while (_n > 1);
        lg = seg.size();
    }
    bool operator[](size_t i) const {
        return (seg[0][i / B] >> (i % B) & 1) != 0;
    }
    void set(size_t i) {
        for (size_t h = 0; h < lg; h++) {
            seg[h][i / B] |= 1ULL << (i % B);
            i /= B;
        }
    }
    void reset(size_t i) {
        for (size_t h = 0; h < lg; h++) {
            seg[h][i / B] &= ~(1ULL << (i % B));
            if (seg[h][i / B]) break;
            i /= B;
        }
    }
    // x以上最小の要素
    ssize_t next(size_t i) {
        for (ssize_t h = 0; h < ssize_t(lg); h++) {
            if (i / 64 == seg[h].size()) break;
            ull d = seg[h][i / B] >> (i % B);
            if (!d) {
                i = i / B + 1;
                continue;
            }
            // find
            i += bsf(d);
            for (ssize_t g = h - 1; g >= 0; g--) {
                i *= 64;
                i += bsf(seg[g][i / B]);
            }
            return i;
        }
        return n;
    }
    // x未満最大の要素
    ssize_t prev(ssize_t i) {
        i--;
        for (ssize_t h = 0; h < ssize_t(lg); h++) {
            if (i == -1) break;
            ull d = seg[h][i / B] << (63 - i % 64);
            if (!d) {
                i = i / 64 - 1;
                continue;
            }
            // find
            i += bsr(d) - 63;
            for (ssize_t g = h - 1; g >= 0; g--) {
                i *= 64;
                i += bsr(seg[g][i / 64]);
            }
            return i;
        }
        return -1;
    }
};
