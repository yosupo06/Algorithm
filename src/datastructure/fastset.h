struct FastSet {
    int N, lg;
    VV<ull> seg;
    FastSet(int N) : N(N) {
        do {
            seg.push_back(V<ull>((N + 63) / 64));
            N = (N + 63) / 64;
        } while (N > 1);
        lg = seg.size();
    }
    bool test(int x) const {
        int D = x / 64, R = x % 64;
        return (seg[0][D] & (1ULL << R)) != 0;
    }
    void set(int x) {
        for (int i = 0; i < lg; i++) {
            int D = x / 64, R = x % 64;
            seg[i][D] |= (1ULL << R);
            x /= 64;
        }
    }
    void clear(int x) {
        for (int i = 0; i < lg; i++) {
            int D = x / 64, R = x % 64;
            seg[i][D] &= ~(1ULL << R);
            if (i && seg[i - 1][x] != 0) {
                seg[i][D] |= (1ULL << R);
            }
            x /= 64;
        }
    }
    // x以上最小の要素
    int next(int x) {
        for (int i = 0; i < lg; i++) {
            int D = x / 64, R = x % 64;
            if (D == seg[i].size()) break;
            ull B = seg[i][D] >> R;
            if (!B) {
                x = x / 64 + 1;
                continue;
            }
            // find
            x += bsf(B);
            for (int j = i - 1; j >= 0; j--) {
                x *= 64;
                int D = x / 64;
                x += bsf(seg[j][D]);
            }
            return x;
        }
        return N;
    }
    // x以下最大の要素
    int back(int x) {
        for (int i = 0; i < lg; i++) {
            if (x == -1) break;
            int D = x / 64, R = x % 64;
            ull B = seg[i][D] << (63 - R);
            if (!B) {
                x = x / 64 - 1;
                continue;
            }
            // find
            x += bsr(B) - 63;
            for (int j = i - 1; j >= 0; j--) {
                x *= 64;
                int D = x / 64;
                x += bsr(seg[j][D]);
            }
            return x;
        }
        return -1;
    }
};
