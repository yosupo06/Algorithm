#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "src/base.h"
#include "src/math/modint.h"
#include "src/util/random.h"
#include "src/math/nft.h"
#include "src/math/poly.h"

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
