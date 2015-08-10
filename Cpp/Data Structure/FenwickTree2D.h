/**
 * Fenwick Tree 2D
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