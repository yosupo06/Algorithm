#pragma once

#include "base.h"

template <class T> struct Fenwick {
    int n;
    V<T> seg;
    Fenwick(int _n = 0) : n(_n), seg(n) {}
    /// i番目の要素にxを追加する
    void add(int i, T x) {
        i++;
        while (i <= n) {
            seg[i - 1] += x;
            i += i & -i;
        }
    }
    /// [0, i)のsum
    T sum(int i) {
        assert(0 <= i && i <= n);
        T s = 0;
        while (i > 0) {
            s += seg[i - 1];
            i -= i & -i;
        }
        return s;
    }
    /// [a, b)のsum
    T sum(int a, int b) {
        assert(0 <= a && a <= b && b <= n);
        return sum(b) - sum(a);
    }
    /// sum[0, idx) >= xなる最小のidx(sum[0, n) < x なら n+1)
    int sum_lower_bound(T x) {
        if (x <= 0) return 0;
        int res = 0, len = 1;
        while (2 * len <= n) len *= 2;
        for (; len >= 1; len /= 2) {
            if (res + len <= n && seg[res + len - 1] < x) {
                res += len;
                x -= seg[res - 1];
            }
        }
        return res + 1;
    }
};
