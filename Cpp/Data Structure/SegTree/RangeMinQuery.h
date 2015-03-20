/**
 * RangeMinQuery
 *
 * 区間系データ構造の中ではFenwick Treeの次あたりに有名？
 * 値の変更と区間の最小値がO(logn)で処理できる
 *
 * template引数のint Sは要素数が2^Sであることを示す
 */
template <int S>
struct RangeMinQuery {
    static const int N = 1<<S;
    typedef ll D;
    static const D INF = 1LL<<62;
    D seg[2*N];

    void init() {
        fill_n(seg, 2*N, INF);
    }

    void init(int n, D x[]) {
        init();
        for (int i = 0; i < n; i++) {
            seg[i+S] = x[i];
        }
        for (int i = N-1; i >= 1; i--) {
            seg[i] = min(seg[i*2], seg[i*2+1]);
        }
    }

    /// i番目の要素をxにする
    void set(int i, D x) {
        i += N;
        seg[i] = x;
        while (i) {
            i /= 2;
            seg[i] = min(seg[i*2], seg[i*2+1]);
        }
    }

    /// [a, b)での最小値を求める
    D get(int a, int b, int k = 1, int l = 0, int r = N) {
        if (r <= a || b <= l) return INF;
        if (a <= l && r <= b) return seg[k];
        int md = (l+r)/2;
        D dl = get(a, b, k*2, l, md);
        D dr = get(a, b, k*2+1, md, r);
        return min(dl, dr);
    }
};
