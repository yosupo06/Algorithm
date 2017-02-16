template<class T>
struct Fenwick {
    int N, lg;
    V<T> seg;
    Fenwick(int N) : N(N) {
        seg.resize(N+1);
        lg = bsr(uint(N));
        fill(begin(seg), end(seg), T(0));
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
    /// sum[0, idx) >= xなる最小のidx
    int sum_lower_bound(T x) {
        if (x <= 0) return 0;
        int res = 0;
        for (int len = 1<<lg; len >= 1; len /= 2) {
            if (res + len <= N && seg[res + len] < x) {
                x -= seg[res+len];
                res += len;
            }
        }
        return res + 1;
    }
};
