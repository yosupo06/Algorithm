/**
 * データ構造をマージする一般的なテクによるUnionFindです。QuickFindと呼ばれているらしい？
 *
 * template引数のint Nは頂点の最大数
 *
 * See_Also: http://topcoder.g.hatena.ne.jp/iwiwi/20131226/1388062106
 */
template <int N>
struct UnionFind {
    int ig[N];
    vector<int> gi[N];
    int gn;
    /// UnionFindを頂点数nで初期化する
    void init(int n = N) {
        for (int i = 0; i < n; ++i) {
            ig[i] = i;
            gi[i] = {i};
        }
        gn = n;
    }

    /// 頂点aと頂点bをマージ
    void merge(int a, int b) {
        if (same(a, b)) return;
        gn--;
        int x = ig[a], y = ig[b];
        if (gi[x].size() < gi[y].size()) swap(x, y);
        for (int j: gi[y]) {
            ig[j] = x;
        }
        gi[x].insert(gi[x].end(), gi[y].begin(), gi[y].end());
        gi[y].clear();
    }
    /// 頂点aと頂点bが同じグループに所属してるかを調べる
    bool same(int a, int b) {
        return ig[a] == ig[b];
    }
    /// グループの数
    int group_num() {
        return gn;
    }
};

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
