/**
 * Fenwick Tree 
 *
 * 0-indexed
 */
template <int N>
struct FenwickTree {
    using D = ll; /// 要素の型
    D seg[N+1];
    
    /// 要素を初期化する
    void init() {
        fill_n(seg, N+1, 0);
    }

    /// i番目の要素にxを追加する
    void add(int i, D x) {
        i++;
        while (i <= N) {
            seg[i] += x;
            i += i & -i;
        }
    }

    /// [0, i)のsum
    D sum(int i) {
        D s = 0;
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }

    /// [a, b)のsum
    D sum(int a, int b) {
        return sum(b) - sum(a);
    }
};
