/**
 * hash化が可能なUnionFind 要素数を16より多くするとオワコンする
 */
template<int N>
struct SUnionFind {
    int i2g[N];
    SUnionFind() {
        for (int i = 0; i < N; i++) {
            i2g[i] = i;
        }
    }
    SUnionFind(ull hs) {
        for (int i = 0; i < N; i++) {
            i2g[i] = hs & 0xf;
            hs >>= 4;
        }
    }

    void merge(int x, int y) {
        int xg = i2g[x], yg = i2g[y];
        for (int i = 0; i < N; i++) {
            if (i2g[i] == yg) i2g[i] = xg;
        }
    }

    bool same(int x, int y) {
        return i2g[x] == i2g[y];
    }

    ull uf2hash() {
        int b[N];
        memset(b, -1, sizeof(b));
        int c = 0;
        ull hs = 0;
        for (int i = N-1; i >= 0; i--) {
            hs <<= 4;
            if (b[i2g[i]] == -1) {
                b[i2g[i]] = c;
                c++;
            }
            hs += b[i2g[i]];
        }
        return hs;
    }
};
