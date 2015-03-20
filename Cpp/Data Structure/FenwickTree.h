/**
 * Fenwick Treeと呼ばれる値の変更と区間のsumがO(logN)で行えるデータ構造
 *
 * template引数のint Nは要素数
 *
 * また、一般的なFenwick Treeと違い0-indexedとなるようにオフセットがかかっている
 */
template <int N>
struct FenwickTree {
    using D = ll; ///要素の型
    D seg[N+1];
    
    /// 要素を初期化する
    void init() {
        for (int i = 0; i <= N; i++) {
            seg[i] = 0;
        }
    }

    /// i番目の要素にxを追加する
    void add(int i, D x) {
        i++;
        while (i <= N) {
            seg[i] += x;
            i += i & -i;
        }
    }

    /// [0, i)のsumを求める
    D sum(int i) {
        D s = 0;
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }

    /// [a, b)のsumを求める
    D sum(int a, int b) {
        return sum(b) - sum(a);
    }
};

/**
 * Fenwick Treeの2次元版、要素の変更と長方形区間のsumがO(log^2N)で行える
 *
 * template引数のint Nは要素数
 */
template <int N>
struct FenwickTree2D {
    using D = ll;
    FenwickTree<N> seg[N+1];
    
    void init() {
        for (int i = 0; i <= N; i++) {
            seg[i].init();
        }
    }

    /// 要素(x, y)にdを加算する
    void add(int x, int y, D d) {
        x++;
        while (x <= N) {
            seg[x].add(y, d);
            x += x & -x;
        }
    }

    /// x座標が[0, x) y座標が[0, y)の長方形区間のsum
    D sum(int x, int y) {
        D s = 0;
        while (x > 0) {
            s += seg[x].sum(y);
            x -= x & -x;
        }
        return s;
    }

    /// x座標が[lx, hx) y座標が[ly, hy)の長方形区間のsum
    D sum(int lx, int ly, int hx, int hy) {
        return (sum(hx, hy) + sum(lx, ly))
             - (sum(lx, hy) + sum(hx, ly));
    }
};