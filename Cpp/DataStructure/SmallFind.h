template<int N>
struct SmallFind {
    int ig[N];
    SmallFind() {
        iota(ig, ig+N, 0);
    }
    SmallFind(ull hs) {
        for (int i = 0; i < N; i++) {
            ig[i] = hs & 0xf;
            hs >>= 4;
        }
    }

    void merge(int x, int y) {
        int xg = ig[x], yg = ig[y];
        for (int i = 0; i < N; i++) {
            if (ig[i] == yg) ig[i] = xg;
        }
    }

    bool same(int x, int y) {
        return ig[x] == ig[y];
    }

    ull uf2hash() {
        int b[N];
        memset(b, -1, sizeof(b));
        int c = 0;
        ull hs = 0;
        for (int i = N-1; i >= 0; i--) {
            hs <<= 4;
            if (b[ig[i]] == -1) {
                b[ig[i]] = c++;
            }
            hs += b[ig[i]];
        }
        return hs;
    }
};
