#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "math/modint.hpp"
#include "util/random.hpp"
#include "math/nft.hpp"
#include "math/poly.hpp"

using Mint = ModInt<998244353>;
template <> const Mint Mint::G = Mint(3);

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int n;
    sc.read(n);
    V<Mint> _a(n);
    for (int i = 0; i < n; i++) {
        int x;
        sc.read(x);
        _a[i] = Mint(x);
    }
    Poly<Mint> a = _a;
    auto b = a.inv(n);

    for (int i = 0; i < n; i++) {
        pr.write(b.freq(i).v);
        pr.write(' ');
    }
    pr.writeln();
    return 0;
}
