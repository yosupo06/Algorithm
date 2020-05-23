#pragma once

#include "base.hpp"

template <class Mint>
V<Mint> powTable(int n, Mint x) {
    V<Mint> table(n + 1);
    table[0] = Mint(1);
    for (int i = 1; i <= n; i++) {
        table[i] = table[i - 1] * x;
    }
    return table;
}

template<class Mint>
struct Comb {
    int max_n;
    V<Mint> fact, ifact;
    Comb() {}
    Comb(int n) : max_n(n) {
        fact = ifact = V<Mint>(n + 1);
        fact[0] = Mint(1);
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    }

    Mint C(int n, int k) {
        if (n < k || n < 0) return Mint(0);
        assert(0 <= k && k <= n && n <= max_n);
        return fact[n] * ifact[k] * ifact[n - k];
    }

    // n個の区別出来ないボールをk個の箱に入れる入れ方
    Mint H(int n, int k) {
        if (n == 0 && k == 0) return Mint(1);
        return C(n + k - 1, n);
    }
};
