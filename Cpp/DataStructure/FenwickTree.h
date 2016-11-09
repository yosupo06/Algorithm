/**
 * Fenwick Tree (0-indexed)
 */
template<class T>
struct Fenwick {
    int N;
    vector<T> seg;
    Fenwick(int N) : N(N) {
        seg.resize(N+1);
        fill_n(begin(seg), N+1, 0);
    }
    /// i番目の要素にxを追加する
    void add(int i, T x) {
        i++;
        while (i <= N) {
            seg[i] += x;
            i += i & -i;
        }
    }
    /// [0, i)のsum
    T sum(int i) {
        T s{0};
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }
    /// [a, b)のsum
    T sum(int a, int b) {
        return sum(b) - sum(a);
    }
};
