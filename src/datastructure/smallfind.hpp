template <int N> struct SmallFind {
    array<int, N> id;
    SmallFind() {
        for (int i = 0; i < N; i++) id[i] = i;
    }

    SmallFind(ull hs) {
        for (int i = 0; i < N; i++) {
            id[i] = hs & 0xf;
            hs >>= 4;
        }
    }

    void merge(int x, int y) {
        int xg = id[x], yg = id[y];
        if (xg == yg) return;
        for (int i = 0; i < N; i++) {
            if (id[i] == yg) id[i] = xg;
        }
    }

    bool same(int x, int y) { return id[x] == id[y]; }

    ull uf2hash() {
        array<int, N> b;
        fill(b.begin(), b.end(), -1);
        int c = 0;
        ull hs = 0;
        for (int i = N - 1; i >= 0; i--) {
            hs <<= 4;
            if (b[id[i]] == -1) {
                b[id[i]] = c++;
            }
            hs += b[id[i]];
        }
        return hs;
    }
};
