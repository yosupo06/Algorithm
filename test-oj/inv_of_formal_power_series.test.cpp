#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "base.h"
#include "util/fast_io.h"
#include "math/modint.h"
#include "util/random.h"
#include "math/nft.h"
#include "math/poly.h"

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
