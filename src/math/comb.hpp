#pragma once

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
};
